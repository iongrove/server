#ifndef SERVER_H
	#define SERVER_H

	#ifndef SERVER_IMPLEMENTED
		#define SERVER_IMPLEMENTED 1
		#define SERVER_IMPLEMENTED_DEFAULT 1
	#endif

	#ifdef _WIN32
		#include <winsock2.h>
		#undef ERROR
		#undef FALSE
		#undef TRUE
	#endif

	#ifndef SERVER_SKIP_PRELUDE
		#include "error.h"
		#include "server-types.h"
		#include "server-errors.h"
		#include "server-address.h"
	#endif

	#if SERVER_IMPLEMENTED_DEFAULT
		#define SERVER_INTERNAL_IS_INHERITABLE 1
		#define SERVER_INTERNAL_IS_NUMERIC 1

		#ifdef _WIN32
			#define SERVER_INTERNAL SOCKET
		#else
			#define SERVER_INTERNAL int
		#endif
	#endif

	typedef struct Server {
		SERVER_INTERNAL internal;
		ServerAddress address;
		u16 port;
	} Server;

	#ifndef SERVER_SKIP_PRELUDE
		#include "server-link.h"
		#include "server-link-open.h"
		#include "server-link-read.h"
		#include "server-link-write.h"
		#include "server-link-close.h"
		#include "server-start.h"
		#include "server-wait.h"
		#include "server-end.h"
		#include "server-test.h"
	#endif
#endif
