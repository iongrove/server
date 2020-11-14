#include "server.h"

#if SERVER_IMPLEMENTED_DEFAULT && _WIN32
	static Error server_link_open_windows(ServerLink* link, ServerAddress address, u16 port) {
		SOCKET sd = socket(AF_INET, SOCK_STREAM, 0);
		struct sockaddr_in addr;

		if (sd == INVALID_SOCKET) {
			return server_error_windows(WSAGetLastError());
		}

		memset(&addr, 0, sizeof(addr));
		addr.sin_addr.S_un.S_un_b.s_b1 = address.bytes[0];
		addr.sin_addr.S_un.S_un_b.s_b2 = address.bytes[1];
		addr.sin_addr.S_un.S_un_b.s_b3 = address.bytes[2];
		addr.sin_addr.S_un.S_un_b.s_b4 = address.bytes[3];
		addr.sin_port = htons(port);
		addr.sin_family = AF_INET;

		if (connect(sd, (struct sockaddr*) &addr, sizeof(addr)) == SOCKET_ERROR) {
			return server_error_windows(WSAGetLastError());
		}

		link->internal = sd;
		link->address = address;
		link->port = port;

		return error_ok();
	}
#endif

#if SERVER_IMPLEMENTED_DEFAULT && !_WIN32
	#define _POSIX_C_SOURCE 1

	#include <errno.h>
	#include <string.h>
	#include <netinet/in.h>

	static Error server_link_open_posix(ServerLink* link, ServerAddress address, u16 port) {
		int fd = socket(AF_INET, SOCK_STREAM, 0);
		struct sockaddr_in addr;

		if (fd == -1) {
			return server_error_posix(errno);
		}

		memset(&addr, 0, sizeof(addr));
		addr.sin_addr.s_addr = htonl(server_address_to_u32(address));
		addr.sin_port = htons(port);
		addr.sin_family = AF_INET;

		if (connect(fd, (struct sockaddr*) &addr, sizeof(addr)) == -1) {
			return server_error_posix(errno);
		}

		link->internal = fd;
		link->address = address;
		link->port = port;

		return error_ok();
	}
#endif

Error server_link_open(ServerLink* link, ServerAddress address, u16 port) {
	#if SERVER_IMPLEMENTED_DEFAULT
		#if _WIN32
			return server_link_open_windows(link, address, port);
		#else
			return server_link_open_posix(link, address, port);
		#endif
	#else
		return SERVER_LINK_OPEN(link, address, port);
	#endif
}
