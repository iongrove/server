#ifndef SERVER_LINK_H
	#define SERVER_LINK_H

	#if SERVER_IMPLEMENTED_DEFAULT
		#define SERVER_LINK_INTERNAL_IS_NUMERIC 1
		#define SERVER_LINK_INTERNAL_IS_INHERITABLE 1
		#define SERVER_LINK_INTERNAL int
	#endif

	typedef struct ServerLink {
		SERVER_LINK_INTERNAL internal;
		ServerAddress address;
		u16 port;
	} ServerLink;
#endif
