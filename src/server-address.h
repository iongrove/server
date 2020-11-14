#ifndef SERVER_ADDRESS_H
	#define SERVER_ADDRESS_H

	typedef struct ServerAddress {
		byte bytes[4];
	} ServerAddress;

	ServerAddress server_address(byte one, byte two, byte three, byte four);

	u32 server_address_to_u32(ServerAddress address);
	ServerAddress server_address_from_u32(u32 n);

	void server_address_test();
#endif
