#include "server.h"

#if SERVER_IMPLEMENTED_DEFAULT && _WIN32
	static Error server_link_write_windows(const ServerLink* link, const byte* buffer, size* length) {
		int written = send(link->internal, (char*) buffer, *length, 0);

		if (written == SOCKET_ERROR) {
			return server_error_windows(WSAGetLastError());
		} else {
			*length = written;
			return error_ok();
		}
	}
#endif

#if SERVER_IMPLEMENTED_DEFAULT && !_WIN32
	#define _POSIX_C_SOURCE 1

	#include <errno.h>
	#include <sys/socket.h>

	static Error server_link_write_posix(const ServerLink* link, const byte* buffer, size* length) {
		ssize_t written = send(link->internal, buffer, *length, MSG_NOSIGNAL);

		if (written == -1) {
			return server_error_posix(errno);
		} else {
			*length = written;
			return error_ok();
		}
	}
#endif

Error server_link_write(const ServerLink* link, const byte* buffer, size* length) {
	#if SERVER_IMPLEMENTED_DEFAULT
		#if _WIN32
			return server_link_write_windows(link, buffer, length);
		#else
			return server_link_write_posix(link, buffer, length);
		#endif
	#else
		return SERVER_LINK_WRITE(link, buffer, length);
	#endif
}

Error server_link_write_all(const ServerLink* link, const byte* buffer, size length) {
	size written = length;
	Error error;

	ERROR(server_link_write(link, buffer, &written));

	if (written == length) {
		return error_ok();
	} else {
		return server_error_unexpected_end();
	}
}
