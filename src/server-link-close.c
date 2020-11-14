#include "server.h"

#if SERVER_IMPLEMENTED_DEFAULT && _WIN32
	static Error server_link_close_windows(const ServerLink* link) {
		if (closesocket(link->internal) == SOCKET_ERROR) {
			return server_error_windows(WSAGetLastError());
		} else {
			return error_ok();
		}
	}
#endif

#if SERVER_IMPLEMENTED_DEFAULT && !_WIN32
	#define _POSIX_C_SOURCE 1

	#include <errno.h>
	#include <unistd.h>

	static Error server_link_close_posix(const ServerLink* link) {
		if (close(link->internal) == -1) {
			return server_error_posix(errno);
		} else {
			return error_ok();
		}
	}
#endif

Error server_link_close(const ServerLink* link) {
	#if SERVER_IMPLEMENTED_DEFAULT
		#if _WIN32
			return server_link_close_windows(link);
		#else
			return server_link_close_posix(link);
		#endif
	#else
		return SERVER_LINK_CLOSE(link);
	#endif
}
