#ifndef LANHOST_HPP_
#define LANHOST_HPP_

#define INET_ADDR_STRLEN 16
#define RECOGNITION_MSG "nibblerHost"
#define RECOGNITION_MSG_L 12
#define NIB_BROAD_PORT 6897
#define NIB_GAME_PORT 6842
#define POLL_CLIENT_SIZE 32

#include <pthread.h>
#include <poll.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>  // for sockaddr_in
#include <fcntl.h>  // for O_NONBLOCK
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <mutex>
#include <atomic>

#include "Logging.hpp"
#include "ANibblerGui.hpp"

struct HostInfo {
	GameInfo const	*gameInfo;
	Input const		*inputs;
};

class LanHost {
	public:
		LanHost();
		virtual ~LanHost();
		LanHost(LanHost const &src);
		LanHost &operator=(LanHost const &rhs);

		void	hostGame();
		bool	getInLobby() const;

		std::vector<std::string>	clientsInput;  // clients input
		std::mutex					mutexClientsInput;
		std::atomic<bool>			inputsReceived;

		// -- exceptions -------------------------------------------------------
		class LanHostException : public std::runtime_error {
			public:
				LanHostException();
				explicit LanHostException(const char* what_arg);
		};

	private:
		static void	*_hostGame(void *lanHostInstance);
		static void	*_broadcast(void *inLobbyPtr);

		static pthread_t			_gameThread;
		bool						_gameThreadIsRunning;
		bool						_inLobby;
};

#endif  // LANHOST_HPP_
