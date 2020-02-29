#ifndef LANCLIENT_HPP_
#define LANCLIENT_HPP_

#include "LanHost.hpp"

class LanClient {
	public:
		LanClient();
		virtual ~LanClient();
		LanClient(LanClient const &src);
		LanClient &operator=(LanClient const &rhs);

		void	joinGame();

		// -- exceptions -------------------------------------------------------
		class LanClientException : public std::runtime_error {
			public:
				LanClientException();
				explicit LanClientException(const char* what_arg);
		};

	private:
		void		_searchHost(sockaddr_in &si_host) const;
		void		_connectToHost(struct in_addr sinAddr) const;
		// take a struct `in_addr *` as argument
		static void	*_clientGame(void *arg);

		static pthread_t	_gameThread;
		bool				_gameThreadIsRunning;
		struct in_addr		_sinAddr;
};

#endif  // LANCLIENT_HPP_
