#ifndef LANCLIENT_HPP_
#define LANCLIENT_HPP_

#include "LanHost.hpp"

class LanClient {
	public:
		LanClient();
		virtual ~LanClient();
		LanClient(LanClient const &src);
		LanClient &operator=(LanClient const &rhs);

		void	joinGame() const;

		// -- exceptions -------------------------------------------------------
		class LanClientException : public std::runtime_error {
			public:
				LanClientException();
				explicit LanClientException(const char* what_arg);
		};

	private:
		void	_searchHost(sockaddr_in &si_host) const;
		void	_connectToHost(sockaddr_in &si_host) const;
};

#endif  // LANCLIENT_HPP_
