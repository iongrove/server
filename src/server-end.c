#include "server.h"

#if SERVER_IMPLEMENTED_DEFAULT && _WIN32
	static Error server_end_windows(const Server* server) {
		if (closesocket(server->internal) == SOCKET_ERROR) {
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

	static Error server_end_posix(const Server* server) {
		if (close(server->internal) == -1) {
			return server_error_posix(errno);
		} else {
			return error_ok();
		}
	}
#endif

Error server_end(const Server* server) {
	#if SERVER_IMPLEMENTED_DEFAULT
		#if _WIN32
			return server_end_windows(server);
		#else
			return server_end_posix(server);
		#endif
	#else
		return SERVER_END(server);
	#endif
}
