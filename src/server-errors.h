#ifndef SERVER_ERRORS_H
	#define SERVER_ERRORS_H

	#define SERVER_ERROR_SPACE "server"
	#define SERVER_ERROR_UNEXPECTED_END 1

	Error server_error_unexpected_end();

	#if SERVER_IMPLEMENTED_DEFAULT
		#ifdef _WIN32
			Error server_error_windows(int code);
		#else
			Error server_error_posix(int code);
		#endif
	#endif
#endif
