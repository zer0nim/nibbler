#include "LanHost.hpp"

LanHost::LanHost()
: _gameThreadIsRunning(false) {
}

LanHost::~LanHost() {
	if (_gameThreadIsRunning) {
		// waiting for the thread to finish
		pthread_join(_gameThread, nullptr);
		_gameThreadIsRunning = false;
	}
}

LanHost::LanHost(LanHost const &src) {
	*this = src;
}

LanHost &LanHost::operator=(LanHost const &rhs) {
	(void)rhs;
	return *this;
}

void	LanHost::hostGame() {
	bool inLobby = true;

	// start the game thread
	if (pthread_create(&_gameThread, nullptr, _hostGame, nullptr)) {
		throw LanHostException("failed to create host game thread");
	}
	_gameThreadIsRunning = true;

	// start a thread to broadcast message to make host detectable
	pthread_t lobbyThread;
	if (pthread_create(&lobbyThread, nullptr, _broadcast, reinterpret_cast<void *>(&inLobby))) {
		throw LanHostException("failed to create broadcast thread");
	}

	logInfo("[lobby] waiting for client...");
	logInfo("[lobby] (hit enter to close the lobby)");

	// quit lobby on enter
	std::cin.ignore();
	logInfo("[lobby] lobby closed, starting the game...");
	inLobby = false;

	pthread_join(lobbyThread, nullptr);  // waiting for the thread to finish
}

void	*LanHost::_hostGame(void *arg) {
	(void)arg;

	// main will not catch exceptions thrown from other threads
	try {
		// create a socket (IPv4, TCP)
		int listenSd = socket(AF_INET, SOCK_STREAM, 0);
		if (listenSd == -1) {
			throw LanHostException(std::string(
				"failed to create socket, errno: " + std::to_string(errno)).c_str());
		}

		// allow to connect even if the port is busy (in the TIME_WAIT state)
		int reuseAddrEnabled = 1;
		if (setsockopt(listenSd, SOL_SOCKET, SO_REUSEADDR, &reuseAddrEnabled, sizeof(int)) < 0) {
			close(listenSd);
			throw LanHostException(std::string(
				"setsockopt(SO_REUSEADDR) failed, errno: " + std::to_string(errno)).c_str());
		}

		// set nonblocking socket, all child sockets will also be nonblocking since
		// they will inherit that state from the listening socket
		if (fcntl(listenSd, F_SETFL, fcntl(listenSd, F_GETFL, 0) | O_NONBLOCK) < 0) {
			close(listenSd);
			throw LanHostException(std::string(
				"fcntl() failed, errno: " + std::to_string(errno)).c_str());
		}

		// set sockaddr_in params:
		//    listen to :NIB_GAME_PORT on any address
		sockaddr_in si_me;
		memset(&si_me, 0, sizeof(si_me));  // zero out si_me
		si_me.sin_family = AF_INET;
		si_me.sin_port = htons(NIB_GAME_PORT);
		si_me.sin_addr.s_addr = INADDR_ANY;

		// assigns the address specified by addr to the socket
		if (bind(listenSd, (struct sockaddr*)&si_me, sizeof(si_me)) < 0) {
			close(listenSd);
			throw LanHostException(std::string(
				"failed to bind to port " + std::to_string(NIB_GAME_PORT) + ", errno: "
				+ std::to_string(errno)).c_str());
		}

		// logDebug("[host] listening...");
		// start listening. Hold at most 32 connections in the queue
		if (listen(listenSd, POLL_CLIENT_SIZE) < 0) {
			close(listenSd);
			throw LanHostException(std::string(
				"failed to listen on socket, errno: " + std::to_string(errno)).c_str());
		}

		// -- manage multiples clients -----------------------------------------
		int ret = 1;  // contain functions return code
		nfds_t	nbFd = 1;
		int	currentSize = 0;
		bool compressArray = false;
		bool runServer = true;
		int	newSd = -1;
		int	closeConn;
		char	buff[80];  // read msg buff

		// init the pollfd structure
		struct pollfd	fds[POLL_CLIENT_SIZE];
		memset(fds, 0, sizeof(fds));  // zero out fds

		// setup initial listening socket
		fds[0].fd = listenSd;
		fds[0].events = POLLIN;
		fds[0].revents = POLLIN;

		// on no activity over 10 minutes the program will end
		int	timeout = (10 * 60 * 1000);

		// wait for incoming connects/data on any of the connected sockets
		while (runServer) {
			// call poll with timeout on no response
			// logDebug("[host] Waiting on poll()...")
			if ((ret = poll(fds, nbFd, timeout)) < 0) {
				logErr("[host] poll() failed");
				break;
			}

			// on timeout
			if (ret == 0) {
				logErr("[host] poll() timed out");
				break;
			}

			// -- at least one fd are readable, let's determine which one ------
			currentSize = nbFd;
			for (int i = 0; i < currentSize; ++i) {
				// on event
				if (fds[i].revents != 0) {
					// close the server if revents != POLLIN, unexpected result
					if (fds[i].revents != POLLIN) {
						// on main fd error stop the server
						if (fds[i].fd == listenSd) {
							logErr("[host] unexpected event from main socket, "
							"stoping the server");
							runServer = false;
							break;
						}
						// on connection fd error close the connection
						logWarn("[host] client: " << fds[i].fd <<
							", unexpected event, closing the connection");
						closeConn = true;
					}

					// listening socket is readable
					if (fds[i].fd == listenSd) {
						// logDebug("[host] listening socket is readable");

						// accept all incoming connections that are queued up on the
						// listening socket before we loop back and call poll again
						do {
							// accept each incoming connection
							newSd = accept(listenSd, nullptr, nullptr);
							// on accept() fail
							if (newSd < 0) {
								// if any other failure than EWOULDBLOCK occurs
								if (errno != EWOULDBLOCK) {
									logErr("[host] accept() failed");
									runServer = false;
								}
								break;
							}

							// add the new incoming connection to the pollfd structure
							logInfo("[host] client: " << newSd << ", joined");
							fds[nbFd].fd = newSd;
							fds[nbFd].events = POLLIN;
							++nbFd;

							// send welcome msg to the client
							std::string	msg = "welcome to my server, have fun :)";
							if (send(newSd, msg.c_str(), msg.length(), 0) < 0) {
								logErr("[host] send() failed, errno: " <<
									std::to_string(errno));
								break;
							}

						// loop back up and accept another incoming connection
						} while (newSd != -1);
					}
					// not a listening socket, therefore an existing connection must be readable
					else {
						// logDebug("[host] client: " << fds[i].fd << " fd is readable");
						// reset closeConn flag if the revents is valid
						if (fds[i].revents == POLLIN) {
							closeConn = false;
						}
						// receive all incoming data on this socket before we loop
						// back and call poll again
						while (!closeConn) {
							// receive data on this connection
							ret = recv(fds[i].fd, buff, sizeof(buff), 0);
							// on recv() fails
							if (ret < 0) {
								// if any other failure than EWOULDBLOCK/EAGAIN/ECONNRESET occurs
								if (errno != EWOULDBLOCK && errno != EAGAIN && errno != ECONNRESET) {
									logErr(std::string("[host] recv() failed, errno: " +
										std::to_string(errno)).c_str());
									closeConn = true;
								}
								break;
							}

							// connection has been closed by the client
							if (ret == 0) {
								logErr("[host] connection closed");
								closeConn = true;
								break;
							}

							// data was received
							int len = ret;
							buff[len] = '\0';
							logInfo("[host] client: " << fds[i].fd << ", received "
								<< len << " bytes: \"" << buff << '"');
						}

						// on closeConn, we need to clean up this active connection
						if (closeConn) {
							logInfo("[host] client: " << fds[i].fd << ", successfully disconected");
							close(fds[i].fd);
							fds[i].fd = -1;
							compressArray = true;
						}
					}
				}

				// on compressArray, squeeze the array and decrement nbFd, we do
				// not need to move back the events and revents fields because the
				// events will always be POLLIN in this case, and revents is output.
				if (compressArray) {
					compressArray = false;
					for (nfds_t i = 0; i < nbFd; ++i) {
						if (fds[i].fd == -1) {
							for (nfds_t j = i; j < nbFd; ++j) {
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
		for (nfds_t i = 0; i < nbFd; ++i) {
			if (fds[i].fd >= 0) {
				close(fds[i].fd);
			}
		}
	}
	catch(LanHost::LanHostException const &e) {
		logErr(e.what());
		pthread_exit(nullptr);
	}

	// exit thread
	pthread_exit(nullptr);
}

void	*LanHost::_broadcast(void *inLobbyPtr) {
	// main will not catch exceptions thrown from other threads
	try {
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
		//    send to :NIB_BROAD_PORT on broadcast address
		sockaddr_in si;
		memset(&si, 0, sizeof(si));  // zero out si
		si.sin_family = AF_INET;
		si.sin_port = htons(NIB_BROAD_PORT);
		inet_aton(ip.c_str(), reinterpret_cast<struct in_addr *>(&si.sin_addr.s_addr));

		while (*inLobby) {
			// logDebug("[broadcast]");
			// broadcast msg
			if (msgLen != sendto(sock, msg.c_str(), msgLen, 0,
				reinterpret_cast<struct sockaddr *>(&si), sizeof(si))) {
				throw LanHostException("sendto() sent different nbs of bytes than expected");
			}

			sleep(3);  // sleep 3s to avoid flooding the network
		}

		close(sock);
	}
	catch(LanHost::LanHostException const &e) {
		logErr(e.what());
		pthread_exit(nullptr);
	}

	// exit thread
	pthread_exit(nullptr);
}

// -- exceptions ---------------------------------------------------------------
LanHost::LanHostException::LanHostException()
: std::runtime_error("[LanHostError]") {}

LanHost::LanHostException::LanHostException(const char* what_arg)
: std::runtime_error(std::string(std::string("[LanHostError] ") + what_arg).c_str()) {}

// -- statics initialisation ---------------------------------------------------
pthread_t	LanHost::_gameThread = pthread_t();
