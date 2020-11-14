#include "server.h"

#if SERVER_IMPLEMENTED_DEFAULT && _WIN32
	static Error server_start_windows(Server* server, ServerAddress address, u16 port) {
		SOCKET sd = socket(AF_INET, SOCK_STREAM, 0);
		struct sockaddr_in localaddr;

		if (sd == INVALID_SOCKET) {
			return server_error_windows(WSAGetLastError());
		}

		memset(&localaddr, 0, sizeof(localaddr));
		localaddr.sin_addr.S_un.S_un_b.s_b1 = address.bytes[0];
		localaddr.sin_addr.S_un.S_un_b.s_b2 = address.bytes[1];
		localaddr.sin_addr.S_un.S_un_b.s_b3 = address.bytes[2];
		localaddr.sin_addr.S_un.S_un_b.s_b4 = address.bytes[3];
		localaddr.sin_port = htons(port);
		localaddr.sin_family = AF_INET;

		if (bind(sd, (struct sockaddr*) &localaddr, sizeof(localaddr)) == SOCKET_ERROR) {
			return server_error_windows(WSAGetLastError());
		}

		if (listen(sd, SERVER_BACKLOG_SIZE) == SOCKET_ERROR) {
			return server_error_windows(WSAGetLastError());
		}

		server->internal = sd;
		server->address = address;
		server->port = port;

		return error_ok();
	}
#endif

#if SERVER_IMPLEMENTED_DEFAULT && !_WIN32
	#define _POSIX_C_SOURCE 1

	#include <errno.h>
	#include <string.h>
	#include <netinet/in.h>
	#include <sys/socket.h>

	static Error server_start_posix(Server* server, ServerAddress address, u16 port) {
		int fd = socket(AF_INET, SOCK_STREAM, 0);
		struct sockaddr_in localaddr;

		if (fd == -1) {
			return server_error_posix(errno);
		}

		memset(&localaddr, 0, sizeof(localaddr));
		localaddr.sin_addr.s_addr = htonl(server_address_to_u32(address));
		localaddr.sin_port = htons(port);
		localaddr.sin_family = AF_INET;

		if (bind(fd, (struct sockaddr*) &localaddr, sizeof(localaddr)) == -1) {
			return server_error_posix(errno);
		}

		if (listen(fd, SERVER_BACKLOG_SIZE) == -1) {
			return server_error_posix(errno);
		}

		server->internal = fd;
		server->address = address;
		server->port = port;

		return error_ok();
	}
#endif

Error server_start(Server* server, ServerAddress address, u16 port) {
	#if SERVER_IMPLEMENTED_DEFAULT
		#if _WIN32
			return server_start_windows(server, address, port);
		#else
			return server_start_posix(server, address, port);
		#endif
	#else
		return SERVER_START(server, address, port);
	#endif
}
