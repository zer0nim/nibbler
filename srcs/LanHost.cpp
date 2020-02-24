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
	// create a socket (IPv4, TCP)
	int sock = socket(AF_INET, SOCK_STREAM, 0);
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

	// set sockaddr_in params:
	//    send to :port on broadcast address
	sockaddr_in si_me;
	memset(&si_me, 0, sizeof(si_me));  // zero out si_me
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(NIB_GAME_PORT);
	si_me.sin_addr.s_addr = INADDR_ANY;

	// assigns the address specified by addr to the socket
	if (bind(sock, (struct sockaddr*)&si_me, sizeof(si_me)) < 0) {
		throw LanHostException(std::string(
			"failed to bind to port " + std::to_string(NIB_GAME_PORT) + ", errno: "
			+ std::to_string(errno)).c_str());
	}

	std::cout << "start listening" << std::endl;
	// start listening. Hold at most 10 connections in the queue
	if (listen(sock, 10) < 0) {
		throw LanHostException(std::string(
			"failed to listen on socket, errno: " + std::to_string(errno)).c_str());
	}

	std::cout << "grab a connection from the queue" << std::endl;
	// grab a connection from the queue
	auto addrlen = sizeof(si_me);
	int connection = accept(sock, reinterpret_cast<struct sockaddr *>(&si_me),
		reinterpret_cast<socklen_t *>(&addrlen));
	if (connection < 0) {
		throw LanHostException(std::string(
			"failed to grab connection, errno: " + std::to_string(errno)).c_str());
	}

	std::cout << "read from the connection" << std::endl;
	// read from the connection
	char buffer[100];
	ssize_t	bytesRead = read(connection, buffer, 100);
	if (bytesRead == -1) {
		throw LanHostException(std::string(
			"failed to read message, errno: " + std::to_string(errno)).c_str());
	}
	buffer[bytesRead] = '\0';
	std::cout << "the message was: " << buffer << std::endl;

	// send a message to the connection
	std::string response = "good talking to you\n";
	send(connection, response.c_str(), response.size(), 0);

	// close the connections
	close(connection);
	close(sock);
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
	pthread_exit(NULL);
}

// -- exceptions ---------------------------------------------------------------
LanHost::LanHostException::LanHostException()
: std::runtime_error("[LanHostError]") {}

LanHost::LanHostException::LanHostException(const char* what_arg)
: std::runtime_error(std::string(std::string("[LanHostError] ") + what_arg).c_str()) {}
