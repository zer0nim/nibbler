#include "LanHost.hpp"

LanHost::LanHost() {
	// start a thread
	if (pthread_create(&_gameThread, NULL, _hostGame, nullptr)) {
		throw LanHostException("Fail to create host lan thread");
	}
}

LanHost::~LanHost() {
}

LanHost::LanHost(LanHost const &src) {
	*this = src;
}

LanHost &LanHost::operator=(LanHost const &rhs) {
	(void)rhs;
	return *this;
}

void	LanHost::hostGame() const {
	bool inLobby = true;

	// start a thread to broadcast message to make host detectable
	pthread_t threadT;
	if (pthread_create(&threadT, NULL, _broadcast, reinterpret_cast<void *>(&inLobby))) {
		throw LanHostException("Fail to create thread for broadcast");
	}

	logInfo("looking for player... (hit enter to stop searching)");
	logInfo("player in the lobby:");

	// quit lobby on enter
	std::cin.ignore();
	logInfo("quit lobby");
	inLobby = false;

	pthread_join(threadT, NULL);  // waiting for the thread to finish
}

void	*LanHost::_hostGame(void *inLobbyPtr) {
	(void)inLobbyPtr;
	std::cout << "-- hostGame --" << std::endl;

	// create a socket (IPv4, TCP)
	int listen_sd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sd == -1) {
		throw LanHostException(std::string(
			"failed to create socket, errno: " + std::to_string(errno)).c_str());
	}

	// allow to connect even if the port is busy (in the TIME_WAIT state)
	int reuseAddrEnabled = 1;
	if (setsockopt(listen_sd, SOL_SOCKET, SO_REUSEADDR, &reuseAddrEnabled, sizeof(int)) < 0) {
		close(listen_sd);
		throw LanHostException(std::string(
			"setsockopt(SO_REUSEADDR) failed, errno: " + std::to_string(errno)).c_str());
	}

	// set nonblocking socket, all child sockets will also be nonblocking since
	// they will inherit that state from the listening socket
	int nonblockingEnabled = 1;
	if (ioctl(listen_sd, FIONBIO, &nonblockingEnabled) < 0) {
		close(listen_sd);
		throw LanHostException("ioctl() failed");
	}

	// set sockaddr_in params:
	//    send to :port on broadcast address
	sockaddr_in si_me;
	memset(&si_me, 0, sizeof(si_me));  // zero out si_me
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(NIB_GAME_PORT);
	si_me.sin_addr.s_addr = INADDR_ANY;

	// assigns the address specified by addr to the socket
	if (bind(listen_sd, (struct sockaddr*)&si_me, sizeof(si_me)) < 0) {
		close(listen_sd);
		throw LanHostException(std::string(
			"failed to bind to port " + std::to_string(NIB_GAME_PORT) + ", errno: "
			+ std::to_string(errno)).c_str());
	}

	std::cout << "start listening" << std::endl;
	// start listening. Hold at most 32 connections in the queue
	if (listen(listen_sd, POLL_CLIENT_SIZE) < 0) {
		close(listen_sd);
		throw LanHostException(std::string(
			"failed to listen on socket, errno: " + std::to_string(errno)).c_str());
	}

	// -- manage multiples clients ---------------------------------------------
	int ret = 1;  // contain functions return code
	int	nbFd = 1;
	int	currentSize = 0;
	bool compressArray = false;
	bool runServer = true;
	int	listenSd = -1;
	int	newSd = -1;
	int	closeConn;
	int	len = 1;
	char	buffer[80];  // read msg buffer

	// init the pollfd structure
	struct pollfd	fds[POLL_CLIENT_SIZE];
	memset(fds, 0, sizeof(fds));  // zero out fds

	// setup initial listening socket
	fds[0].fd = listen_sd;
	fds[0].events = POLLIN;

	// on no activity over 10 minutes the program will end
	int	timeout = (10 * 60 * 1000);

	// wait for incoming connects/data on any of the connected sockets
	while (runServer) {
		// call poll with timeout on no response
		logInfo("Waiting on poll()...")
		if ((ret = poll(fds, nbFd, timeout)) < 0) {
			logErr("poll() failed");
			break;
		}

		// on timeout
		if (ret == 0) {
			logErr("poll() timed out");
			break;
		}

		// -- at least one fd are readable, let's determine which one ----------
		currentSize = nbFd;
		for (int i = 0; i < currentSize; ++i) {
			// on event
			if (fds[i].revents != 0) {
				// close the server if revents != POLLIN, unexpected result
				if (fds[i].revents != POLLIN) {
					throw LanHostException(std::string(
						"unexpected value, revents: " +
						std::to_string(fds[i].revents)).c_str());
					runServer = false;
					break;
				}

				// listening socket is readable
				if (fds[i].fd == listenSd) {
					logInfo("listening socket is readable");

					// accept all incoming connections that are queued up on the
					// listening socket before we loop back and call poll again
					do {
						// accept each incoming connection
						newSd = accept(listenSd, NULL, NULL);
						// on accept() fail
						if (newSd < 0) {
							// if any other failure than EWOULDBLOCK occurs
							if (errno != EWOULDBLOCK) {
								logErr("accept() failed");
								runServer = false;
							}
							break;
						}

						// add the new incoming connection to the pollfd structure
						logInfo("new incoming connection, " << newSd);
						fds[nbFd].fd = newSd;
						fds[nbFd].events = POLLIN;
						++nbFd;

					// loop back up and accept another incoming connection
					} while (newSd != -1);
				}
				// not a listening socket, therefore an existing connection must be readable
				else {
					logInfo("descriptor " << fds[i].fd << " is readable");

					closeConn = false;
					// receive all incoming data on this socket before we loop
					// back and call poll again
					while(true) {
						// receive data on this connection
						ret = recv(fds[i].fd, buffer, sizeof(buffer), 0);
						// on recv() fails
						if (ret < 0) {
							// if any other failure than EWOULDBLOCK occurs
							if (errno != EWOULDBLOCK) {
								logErr("recv() failed");
								closeConn = true;
							}
							break;
						}

						// connection has been closed by the client
						if (ret == 0) {
							printf("  Connection closed\n");
							closeConn = true;
							break;
						}

						// data was received
						len = ret;
						logInfo(len << " bytes received");

						// echo the data back to the client
						if (send(fds[i].fd, buffer, len, 0) < 0) {
							logErr("send() failed");
							closeConn = true;
							break;
						}
					}

					// on closeConn, we need to clean up this active connection
					if (closeConn) {
						close(fds[i].fd);
						fds[i].fd = -1;
						compressArray = true;
					}
				}
			}

			// on compressArray, squeeze the array and decrement nbFd
			// we do not need to move back the events and revents fields because the
			// events will always be POLLIN in this case, and revents is output.
			if (compressArray) {
				compressArray = false;
				for (int i = 0; i < nbFd; ++i) {
					if (fds[i].fd == -1) {
						for (int j = i; j < nbFd; ++j) {
							fds[j].fd = fds[j + 1].fd;
						}
						--i;
						--nbFd;
					}
				}
			}
		}
	}

	// clean up all open sockets
	for (int i = 0; i < nbFd; ++i) {
		if (fds[i].fd >= 0) {
			close(fds[i].fd);
		}
	}

	// exit thread
	pthread_exit(NULL);
}

void	*LanHost::_broadcast(void *inLobbyPtr) {
	bool const *inLobby = reinterpret_cast<bool *>(inLobbyPtr);

	// create a socket (IPv4, UDP)
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1) {
		throw LanHostException(std::string(
			"failed to create socket, errno: " + std::to_string(errno)).c_str());
	}

	// allow to connect even if the port is busy (in the TIME_WAIT state)
	int reuseAddrEnabled = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuseAddrEnabled, sizeof(int)) < 0) {
		throw LanHostException(std::string(
			"setsockopt(SO_REUSEADDR) failed, errno: " + std::to_string(errno)).c_str());
	}
	// enable broadcast
	int broadcastEnable = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(int)) < 0) {
		throw LanHostException(std::string(
			"setsockopt(SO_BROADCAST) failed, errno: " + std::to_string(errno)).c_str());
	}

	// declare sockaddr_in params
	std::string const ip = "255.255.255.255";
	std::string const msg = RECOGNITION_MSG;
	int		msgLen = msg.length();

	// set sockaddr_in params:
	//    send to :port on broadcast address
	sockaddr_in si;
	memset(&si, 0, sizeof(si));  // zero out si
	si.sin_family = AF_INET;
	si.sin_port = htons(NIB_BROAD_PORT);
	inet_aton(ip.c_str(), reinterpret_cast<struct in_addr *>(&si.sin_addr.s_addr));

	while (*inLobby) {
		logInfo("[broadcast] sendto");
		// broadcast msg
		if (msgLen != sendto(sock, msg.c_str(), msgLen, 0,
			reinterpret_cast<struct sockaddr *>(&si), sizeof(si))) {
			throw LanHostException("sendto() sent different nbs of bytes than expected");
		}

		sleep(3);  // sleep 3s to avoid flooding the network
	}

	close(sock);

	// exit thread
	pthread_exit(NULL);
}

// -- exceptions ---------------------------------------------------------------
LanHost::LanHostException::LanHostException()
: std::runtime_error("[LanHostError]") {}

LanHost::LanHostException::LanHostException(const char* what_arg)
: std::runtime_error(std::string(std::string("[LanHostError] ") + what_arg).c_str()) {}
