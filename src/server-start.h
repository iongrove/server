#ifndef SERVER_START_H
	#define SERVER_START_H

	#ifndef SERVER_BACKLOG_SIZE
		#define SERVER_BACKLOG_SIZE 128
	#endif

	Error server_start(Server* server, ServerAddress address, u16 port);
#endif
