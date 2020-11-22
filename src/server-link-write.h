#ifndef SERVER_LINK_WRITE_H
	#define SERVER_LINK_WRITE_H

	Error server_link_write(const ServerLink* link, const byte* buffer, umax* length);
	Error server_link_write_all(const ServerLink* link, const byte* buffer, umax length);
#endif
