#include "server.h"

#if SERVER_IMPLEMENTED_DEFAULT && _WIN32
	static Error server_link_read_windows(const ServerLink* link, byte* buffer, size* length, int flags) {
		int readin = recv(link->internal, (char*) buffer, *length, flags);

		if (readin == SOCKET_ERROR) {
			return server_error_windows(WSAGetLastError());
		} else {
			*length = readin;
			return error_ok();
		}
	}
#endif

#if SERVER_IMPLEMENTED_DEFAULT && !_WIN32
	#define _POSIX_C_SOURCE 1

	#include <errno.h>
	#include <sys/socket.h>

	static Error server_link_read_posix(const ServerLink* link, byte* buffer, size* length, int flags) {
		ssize_t readin = recv(link->internal, buffer, *length, flags);

		if (readin == -1) {
			return server_error_posix(errno);
		} else {
			*length = readin;
			return error_ok();
		}
	}
#endif

Error server_link_read(const ServerLink* link, byte* buffer, size* length) {
	#if SERVER_IMPLEMENTED_DEFAULT
		#if _WIN32
			return server_link_read_windows(link, buffer, length, 0);
		#else
			return server_link_read_posix(link, buffer, length, 0);
		#endif
	#else
		return SERVER_LINK_READ(link, buffer, length);
	#endif
}

Error server_link_read_all(const ServerLink* link, byte* buffer, size length) {
	#if SERVER_IMPLEMENTED_DEFAULT
		size written = length;
		Error error;

		#if _WIN32
			#ifndef MSG_WAITALL
				#define MSG_WAITALL 0x8
			#endif

			ERROR(server_link_read_windows(link, buffer, &written, MSG_WAITALL));
		#else
			ERROR(server_link_read_posix(link, buffer, &written, MSG_WAITALL));
		#endif

		if (written == length) {
			return error_ok();
		} else {
			return server_error_unexpected_end();
		}
	#else
		return SERVER_LINK_READ_ALL(link, buffer, length);
	#endif
}
