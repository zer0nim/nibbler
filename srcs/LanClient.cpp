#include "LanClient.hpp"

LanClient::LanClient() {
}

LanClient::~LanClient() {
}

LanClient::LanClient(LanClient const &src) {
	*this = src;
}

LanClient &LanClient::operator=(LanClient const &rhs) {
	(void)rhs;
	return *this;
}

// looking for host and join him
void	LanClient::joinGame() const {
	sockaddr_in	si_host;
	memset(&si_host, 0, sizeof(si_host));  // zero out si_host

	// looking for host
	_searchHost(si_host);

	// change the port to NIB_GAME_PORT to establish a connection with the host
	si_host.sin_port = htons(NIB_GAME_PORT);
	_connectToHost(si_host);
}

void	LanClient::_connectToHost(sockaddr_in &si_host) const {
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

	// set nonblocking socket, all child sockets will also be nonblocking since
	// they will inherit that state from the listening socket
	int nonblockingEnabled = 1;
	if (ioctl(sock, FIONBIO, &nonblockingEnabled) < 0) {
		close(sock);
		throw LanClientException("ioctl() failed");
	}

	// assigns the address specified by addr to the socket
	if (bind(sock, (struct sockaddr*)&si_host, sizeof(si_host)) < 0) {
		close(sock);
		throw LanClientException(std::string(
			"failed to bind to port " + std::to_string(NIB_GAME_PORT) + ", errno: "
			+ std::to_string(errno)).c_str());
	}

	std::cout << "start listening" << std::endl;
	// start listening. Hold at most 32 connections in the queue
	if (listen(sock, POLL_CLIENT_SIZE) < 0) {
		close(sock);
		throw LanClientException(std::string(
			"failed to listen on socket, errno: " + std::to_string(errno)).c_str());
	}

	std::cout << "grab a connection from the queue" << std::endl;
	// grab a connection from the queue
	auto addrlen = sizeof(si_host);
	int connection = accept(sock, reinterpret_cast<struct sockaddr *>(&si_host),
		reinterpret_cast<socklen_t *>(&addrlen));
	if (connection < 0) {
		throw LanClientException(std::string(
			"failed to grab connection, errno: " + std::to_string(errno)).c_str());
	}

	std::cout << "read from the connection" << std::endl;
	// read from the connection
	char buffer[100];
	ssize_t	bytesRead = read(connection, buffer, 100);
	if (bytesRead == -1) {
		throw LanClientException(std::string(
			"failed to read message, errno: " + std::to_string(errno)).c_str());
	}
	buffer[bytesRead] = '\0';
	std::cout << "the message was: " << buffer << std::endl;

	// send a message to the connection
	std::string response = "good talking to you\n";
	send(connection, response.c_str(), response.size(), 0);

	// close the connections
	close(connection);
}

void	LanClient::_searchHost(sockaddr_in &si_host) const {
	sockaddr_in si_me;

	std::cout << "-- searchHost --" << std::endl;
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
			"Failed to bind to port " + std::to_string(NIB_BROAD_PORT) + ", errno: "
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
			std::cout << "host founded" << std::endl;
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
