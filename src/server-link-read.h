#ifndef SERVER_LINK_READ_H
	#define SERVER_LINK_READ_H

	Error server_link_read(const ServerLink* link, byte* buffer, umax* length);
	Error server_link_read_all(const ServerLink* link, byte* buffer, umax length);
#endif
