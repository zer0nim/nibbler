#include "LanClient.hpp"

LanClient::LanClient()
: _gameThreadIsRunning(false) {
}

LanClient::~LanClient() {
	if (_gameThreadIsRunning) {
		// waiting for the thread to finish
		pthread_join(_gameThread, nullptr);
		_gameThreadIsRunning = false;
	}
}

LanClient::LanClient(LanClient const &src) {
	*this = src;
}

LanClient &LanClient::operator=(LanClient const &rhs) {
	(void)rhs;
	return *this;
}

// looking for host and join him
void	LanClient::joinGame() {
	sockaddr_in	si_host;
	memset(&si_host, 0, sizeof(si_host));  // zero out si_host

	// looking for host
	_searchHost(si_host);

	// connect to host with its address
	_connectToHost(si_host.sin_addr);

	// start the game thread
	if (pthread_create(&_gameThread, nullptr, _clientGame, nullptr)) {
		throw LanClientException("failed to create client game thread");
	}
	_gameThreadIsRunning = true;
}

void	*LanClient::_clientGame(void *arg) {
	(void)arg;

	// main will not catch exceptions thrown from other threads
	try {
		while (true) {
			// TODO(zer0nim): send gui input to host and receive actions
			sleep(3);
		}
	}
	catch(LanClient::LanClientException const &e) {
		logErr(e.what());
		pthread_exit(nullptr);
	}

	// exit thread
	pthread_exit(nullptr);
}

void	LanClient::_connectToHost(struct in_addr sinAddr) const {
	// create a socket (IPv4, TCP)
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		throw LanClientException(std::string(
			"failed to create socket, errno: " + std::to_string(errno)).c_str());
	}

	// allow to connect even if the port is busy (in the TIME_WAIT state)
	int reuseAddrEnabled = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuseAddrEnabled, sizeof(int)) < 0) {
		close(sock);
		throw LanClientException(std::string(
			"setsockopt(SO_REUSEADDR) failed, errno: " + std::to_string(errno)).c_str());
	}

	// set sockaddr_in params:
	//    listen to :NIB_GAME_PORT on any address
	sockaddr_in si_host;
	memset(&si_host, 0, sizeof(si_host));  // zero out si_host
	si_host.sin_family = AF_INET;
	si_host.sin_port = htons(NIB_GAME_PORT);
	si_host.sin_addr = sinAddr;

	// try to connect to the server
	if (connect(sock, (struct sockaddr *)&si_host, sizeof(si_host)) < 0) {
		if (errno != EINPROGRESS) {
			throw LanClientException(std::string(
				"connection failed, errno: " + std::to_string(errno)).c_str());
		}
	}
	logInfo("[client] successfully connected to host: " << sock)

	// wait for server response
	char	buff[1024] = {0};
	ssize_t	bytesRead = read(sock, buff, 1024);
	if (bytesRead == -1) {
		throw LanClientException(std::string(
			"failed to read message, errno: " + std::to_string(errno)).c_str());
	}
	buff[bytesRead] = '\0';
	logInfo("[client] receive message from host: \"" << buff << '"' << sock)

	// answer with hello message
	std::string	msg = "thank's, hello from client";
	if (send(sock, msg.c_str(), msg.length(), 0) < 0) {
		throw LanClientException(std::string("send() failed, errno: " +
			std::to_string(errno)).c_str());
	}

	sleep(3);  // sleep 3s before closing the connection

	// close the connections
	close(sock);
}

void	LanClient::_searchHost(sockaddr_in &si_host) const {
	sockaddr_in si_me;

	logInfo("[client] searching host...");
	// create a socket (IPv4, UDP)
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1) {
		throw LanClientException(std::string(
			"failed to create socket, errno: " + std::to_string(errno)).c_str());
	}

	// allow to connect even if the port is busy (in the TIME_WAIT state)
	int reuseAddrEnabled = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuseAddrEnabled, sizeof(int)) < 0) {
		throw LanClientException(std::string(
			"setsockopt(SO_REUSEADDR) failed, errno: " + std::to_string(errno)).c_str());
	}
	// enable broadcast
	int broadcastEnable = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(int)) < 0) {
		throw LanClientException(std::string(
			"setsockopt(SO_BROADCAST) failed, errno: " + std::to_string(errno)).c_str());
	}

	// set sockaddr_in params:
	//    listen to :port on any address
	memset(&si_me, 0, sizeof(si_me));  // zero out si_me
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(NIB_BROAD_PORT);
	si_me.sin_addr.s_addr = INADDR_ANY;

	// assigns the address specified by addr to the socket
	if (bind(sock, (struct sockaddr*)&si_me, sizeof(sockaddr)) < 0) {
		throw LanClientException(std::string(
			"failed to bind to port: " + std::to_string(NIB_BROAD_PORT) + ", errno: "
				+ std::to_string(errno)).c_str());
	}

	// listen to :port on any address
	bool hostFounded = false;
	while (!hostFounded) {
		char	buff[100];
		uint32_t	slen = sizeof(sockaddr);

		// retrieve message
		ssize_t	bytesRead = recvfrom(sock, buff, sizeof(buff) - 1, 0,
			reinterpret_cast<sockaddr *>(&si_host), &slen);
		if (bytesRead == -1) {
			throw LanClientException(std::string(
				"failed to read message, errno: " + std::to_string(errno)).c_str());
		}
		buff[bytesRead] = '\0';

		// if message == RECOGNITION_MSG, we have found an host :)
		if (strncmp(buff, RECOGNITION_MSG, RECOGNITION_MSG_L) == 0) {
			hostFounded = true;
			logInfo("[client] host detected");
		}
	}

	// close the connections
	close(sock);
}

// -- exceptions ---------------------------------------------------------------
LanClient::LanClientException::LanClientException()
: std::runtime_error("[LanClientError]") {}

LanClient::LanClientException::LanClientException(const char* what_arg)
: std::runtime_error(std::string(std::string("[LanClientError] ") + what_arg).c_str()) {}

// -- statics initialisation ---------------------------------------------------
pthread_t	LanClient::_gameThread = pthread_t();
