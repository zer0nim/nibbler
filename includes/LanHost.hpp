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
#include <sys/poll.h>
#include <errno.h>
#include <sys/ioctl.h>  // for ioctl
#include <arpa/inet.h>  // for inet_aton
#include <sys/socket.h>  // for socket functions
#include <netinet/in.h>  // for sockaddr_in
#include <fcntl.h>  // for O_NONBLOCK
#include <unistd.h>  // for read
#include <cstring>
#include <cstdlib>  // for exit() and EXIT_FAILURE
#include <iostream>  // for cout
#include <string>
#include <stdexcept>


#include "Logging.hpp"

class LanHost {
	public:
		LanHost();
		virtual ~LanHost();
		LanHost(LanHost const &src);
		LanHost &operator=(LanHost const &rhs);

		void	hostGame() const;

		// -- exceptions -------------------------------------------------------
		class LanHostException : public std::runtime_error {
			public:
				LanHostException();
				explicit LanHostException(const char* what_arg);
		};

	private:
		static void	*_hostGame(void *inLobbyPtr);
		static void	*_broadcast(void *inLobbyPtr);

		pthread_t	_gameThread;
};

#endif  // LANHOST_HPP_
