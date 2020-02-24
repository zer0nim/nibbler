#include "LanHost.hpp"

LanHost::LanHost() {
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

void	LanHost::broadcast() const {
	logInfo("-- broadcast --");
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

	while (true) {
		logInfo("sendto");
		// broadcast msg
		if (msgLen != sendto(sock, msg.c_str(), msgLen, 0,
			reinterpret_cast<struct sockaddr *>(&si), sizeof(si))) {
			throw LanHostException("sendto() sent different nbs of bytes than expected");
		}

		sleep(3);  // sleep 3s to avoid flooding the network
	}

	close(sock);
}

// -- exceptions ---------------------------------------------------------------
LanHost::LanHostException::LanHostException()
: std::runtime_error("[LanHostError]") {}

LanHost::LanHostException::LanHostException(const char* what_arg)
: std::runtime_error(std::string(std::string("[LanHostError] ") + what_arg).c_str()) {}
