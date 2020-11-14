#include "server.h"

#if SERVER_IMPLEMENTED_DEFAULT && _WIN32
	static Error server_wait_windows(const Server* server, ServerLink* link) {
		struct sockaddr_in addr;
		int addrlen = sizeof(addr);
		SOCKET sd = accept(server->internal, (struct sockaddr*) &addr, &addrlen);

		if (sd == INVALID_SOCKET) {
			return server_error_windows(WSAGetLastError());
		}

		link->internal = sd;
		link->port = ntohs(addr.sin_port);
		link->address = server_address(
			addr.sin_addr.S_un.S_un_b.s_b1,
			addr.sin_addr.S_un.S_un_b.s_b2,
			addr.sin_addr.S_un.S_un_b.s_b3,
			addr.sin_addr.S_un.S_un_b.s_b4
		);

		return error_ok();
	}
#endif

#if SERVER_IMPLEMENTED_DEFAULT && !_WIN32
	#define _POSIX_C_SOURCE 1

	#include <errno.h>
	#include <netinet/in.h>

	static Error server_wait_posix(const Server* server, ServerLink* link) {
		struct sockaddr_in addr;
		socklen_t addrlen = sizeof(addr);
		int fd = accept(server->internal, (struct sockaddr*) &addr, &addrlen);

		if (fd == -1) {
			return server_error_posix(errno);
		}

		link->address = server_address_from_u32(ntohl(addr.sin_addr.s_addr));
		link->port = ntohs(addr.sin_port);
		link->internal = fd;

		return error_ok();
	}
#endif

Error server_wait(const Server* server, ServerLink* link) {
	#if SERVER_IMPLEMENTED_DEFAULT
		#if _WIN32
			return server_wait_windows(server, link);
		#else
			return server_wait_posix(server, link);
		#endif
	#else
		return SERVER_WAIT(server, link);
	#endif
}
