#include <assert.h>
#include "server.h"

ServerAddress server_address(byte one, byte two, byte three, byte four) {
	ServerAddress address;
	address.bytes[0] = one;
	address.bytes[1] = two;
	address.bytes[2] = three;
	address.bytes[3] = four;
	return address;
}

u32 server_address_to_u32(ServerAddress address) {
	u32 n = 0;

	n |= ((address.bytes[0] & 0xFFu) << (3*8));
	n |= ((address.bytes[1] & 0xFFu) << (2*8));
	n |= ((address.bytes[2] & 0xFFu) << (1*8));
	n |= ((address.bytes[3] & 0xFFu) << (0*8));

	return n;
}

ServerAddress server_address_from_u32(u32 n) {
	ServerAddress address;

	address.bytes[0] = ((n >> 3*8) & 0xFFu);
	address.bytes[1] = ((n >> 2*8) & 0xFFu);
	address.bytes[2] = ((n >> 1*8) & 0xFFu);
	address.bytes[3] = ((n >> 0*8) & 0xFFu);

	return address;
}

static void address_conversion_test(ServerAddress addressin, u32 expected) {
	u32 n = server_address_to_u32(addressin);
	ServerAddress addressout = server_address_from_u32(n);

	assert(addressin.bytes[0] == addressout.bytes[0]);
	assert(addressin.bytes[1] == addressout.bytes[1]);
	assert(addressin.bytes[2] == addressout.bytes[2]);
	assert(addressin.bytes[3] == addressout.bytes[3]);

	assert(n == expected);
}

void server_address_test() {
	address_conversion_test(server_address(0, 0, 0, 0), 0u);
	address_conversion_test(server_address(127, 0, 0, 1), 2130706433u);
	address_conversion_test(server_address(192, 168, 0, 1), 3232235521u);
	address_conversion_test(server_address(255, 255, 255, 255), 4294967295u);
}
