#include "server.h"

static char* server_error_message(int code) {
	if (code == ERROR_CODE_OK) {
		return "Success";
	} else if (code == SERVER_ERROR_UNEXPECTED_END) {
		return "Unexpected end of stream";
	} else {
		return "Unknown error";
	}
}

static Error server_error(int code) {
	return error_custom(code, SERVER_ERROR_SPACE, server_error_message);
}

Error server_error_unexpected_end() {
	return server_error(SERVER_ERROR_UNEXPECTED_END);
}

#if SERVER_IMPLEMENTED_DEFAULT && !_WIN32
	#include <string.h>
	Error server_error_posix(int code) {
		return error_custom(code, SERVER_ERROR_SPACE, strerror);
	}
#endif

#if SERVER_IMPLEMENTED_DEFAULT && _WIN32
	/* see: https://docs.microsoft.com/en-us/windows/win32/winsock/windows-sockets-error-codes-2 */
	static char* windows_error_message(int code) {
		if (code == WSA_INVALID_HANDLE) {
			return "Specified event object handle is invalid";
		} else if (code == WSA_NOT_ENOUGH_MEMORY) {
			return "Insufficient memory available";
		} else if (code == WSA_INVALID_PARAMETER) {
			return "One or more parameters are invalid";
		} else if (code == WSA_OPERATION_ABORTED) {
			return "Overlapped operation aborted";
		} else if (code == WSA_IO_INCOMPLETE) {
			return "Overlapped I/O event object not in signaled state";
		} else if (code == WSA_IO_PENDING) {
			return "Overlapped operations will complete later";
		} else if (code == WSAEINTR) {
			return "Interrupted function call";
		} else if (code == WSAEBADF) {
			return "File handle is not valid";
		} else if (code == WSAEACCES) {
			return "Permission denied";
		} else if (code == WSAEFAULT) {
			return "Bad address";
		} else if (code == WSAEINVAL) {
			return "Invalid argument";
		} else if (code == WSAEMFILE) {
			return "Too many open files";
		} else if (code == WSAEWOULDBLOCK) {
			return "Resource temporarily unavailable";
		} else if (code == WSAEINPROGRESS) {
			return "Operation now in progress";
		} else if (code == WSAEALREADY) {
			return "Operation already in progress";
		} else if (code == WSAENOTSOCK) {
			return "Socket operation on nonsocket";
		} else if (code == WSAEDESTADDRREQ) {
			return "Destination address required";
		} else if (code == WSAEMSGSIZE) {
			return "Message too long";
		} else if (code == WSAEPROTOTYPE) {
			return "Protocol wrong type for socket";
		} else if (code == WSAENOPROTOOPT) {
			return "Bad protocol option";
		} else if (code == WSAEPROTONOSUPPORT) {
			return "Protocol not supported";
		} else if (code == WSAESOCKTNOSUPPORT) {
			return "Socket type not supported";
		} else if (code == WSAEOPNOTSUPP) {
			return "Operation not supported";
		} else if (code == WSAEPFNOSUPPORT) {
			return "Protocol family not supported";
		} else if (code == WSAEAFNOSUPPORT) {
			return "Address family not supported by protocol family";
		} else if (code == WSAEADDRINUSE) {
			return "Address already in use";
		} else if (code == WSAEADDRNOTAVAIL) {
			return "Cannot assign requested address";
		} else if (code == WSAENETDOWN) {
			return "Network is down";
		} else if (code == WSAENETUNREACH) {
			return "Network is unreachable";
		} else if (code == WSAENETRESET) {
			return "Network dropped connection on reset";
		} else if (code == WSAECONNABORTED) {
			return "Software caused connection abort";
		} else if (code == WSAECONNRESET) {
			return "Connection reset by peer";
		} else if (code == WSAENOBUFS) {
			return "No buffer space available";
		} else if (code == WSAEISCONN) {
			return "Socket is already connected";
		} else if (code == WSAENOTCONN) {
			return "Socket is not connected";
		} else if (code == WSAESHUTDOWN) {
			return "Cannot send after socket shutdown";
		} else if (code == WSAETOOMANYREFS) {
			return "Too many references";
		} else if (code == WSAETIMEDOUT) {
			return "Connection timed out";
		} else if (code == WSAECONNREFUSED) {
			return "Connection refused";
		} else if (code == WSAELOOP) {
			return "Cannot translate name";
		} else if (code == WSAENAMETOOLONG) {
			return "Name too long";
		} else if (code == WSAEHOSTDOWN) {
			return "Host is down";
		} else if (code == WSAEHOSTUNREACH) {
			return "No route to host";
		} else if (code == WSAENOTEMPTY) {
			return "Directory not empty";
		} else if (code == WSAEPROCLIM) {
			return "Too many processes";
		} else if (code == WSAEUSERS) {
			return "User quota exceeded";
		} else if (code == WSAEDQUOT) {
			return "Disk quota exceeded";
		} else if (code == WSAESTALE) {
			return "Stale file handle reference";
		} else if (code == WSAEREMOTE) {
			return "Item is remote";
		} else if (code == WSASYSNOTREADY) {
			return "Network subsystem is unavailable";
		} else if (code == WSAVERNOTSUPPORTED) {
			return "Winsock.dll version out of range";
		} else if (code == WSANOTINITIALISED) {
			return "Successful WSAStartup not yet performed";
		} else if (code == WSAEDISCON) {
			return "Graceful shutdown in progress";
		} else if (code == WSAENOMORE) {
			return "No more results";
		} else if (code == WSAECANCELLED) {
			return "Call has been canceled";
		} else if (code == WSAEINVALIDPROCTABLE) {
			return "Procedure call table is invalid";
		} else if (code == WSAEINVALIDPROVIDER) {
			return "Service provider is invalid";
		} else if (code == WSAEPROVIDERFAILEDINIT) {
			return "Service provider failed to initialize";
		} else if (code == WSASYSCALLFAILURE) {
			return "System call failure";
		} else if (code == WSASERVICE_NOT_FOUND) {
			return "Service not found";
		} else if (code == WSATYPE_NOT_FOUND) {
			return "Class type not found";
		} else if (code == WSA_E_NO_MORE) {
			return "No more results";
		} else if (code == WSA_E_CANCELLED) {
			return "Call was canceled";
		} else if (code == WSAEREFUSED) {
			return "Database query was refused";
		} else if (code == WSAHOST_NOT_FOUND) {
			return "Host not found";
		} else if (code == WSATRY_AGAIN) {
			return "Nonauthoritative host not found";
		} else if (code == WSANO_RECOVERY) {
			return "This is a nonrecoverable error";
		} else if (code == WSANO_DATA) {
			return "Valid name, no data record of requested type";
		} else if (code == WSA_QOS_RECEIVERS) {
			return "QoS receivers";
		} else if (code == WSA_QOS_SENDERS) {
			return "QoS senders";
		} else if (code == WSA_QOS_NO_SENDERS) {
			return "No QoS senders";
		} else if (code == WSA_QOS_NO_RECEIVERS) {
			return "QoS no receivers";
		} else if (code == WSA_QOS_REQUEST_CONFIRMED) {
			return "QoS request confirmed";
		} else if (code == WSA_QOS_ADMISSION_FAILURE) {
			return "QoS admission error";
		} else if (code == WSA_QOS_POLICY_FAILURE) {
			return "QoS policy failure";
		} else if (code == WSA_QOS_BAD_STYLE) {
			return "QoS bad style";
		} else if (code == WSA_QOS_BAD_OBJECT) {
			return "QoS bad object";
		} else if (code == WSA_QOS_TRAFFIC_CTRL_ERROR) {
			return "QoS traffic control error";
		} else if (code == WSA_QOS_GENERIC_ERROR) {
			return "QoS generic error";
		} else if (code == WSA_QOS_ESERVICETYPE) {
			return "QoS service type error";
		} else if (code == WSA_QOS_EFLOWSPEC) {
			return "QoS flowspec error";
		} else if (code == WSA_QOS_EPROVSPECBUF) {
			return "Invalid QoS provider buffer";
		} else if (code == WSA_QOS_EFILTERSTYLE) {
			return "Invalid QoS filter style";
		} else if (code == WSA_QOS_EFILTERTYPE) {
			return "Invalid QoS filter type";
		} else if (code == WSA_QOS_EFILTERCOUNT) {
			return "Incorrect QoS filter count";
		} else if (code == WSA_QOS_EOBJLENGTH) {
			return "Invalid QoS object length";
		} else if (code == WSA_QOS_EFLOWCOUNT) {
			return "Incorrect QoS flow count";
		} else if (code == WSA_QOS_EUNKOWNPSOBJ) {
			return "Unrecognized QoS object";
		} else if (code == WSA_QOS_EPOLICYOBJ) {
			return "Invalid QoS policy object";
		} else if (code == WSA_QOS_EFLOWDESC) {
			return "Invalid QoS flow descriptor";
		} else if (code == WSA_QOS_EPSFLOWSPEC) {
			return "Invalid QoS provider-specific flowspec";
		} else if (code == WSA_QOS_EPSFILTERSPEC) {
			return "Invalid QoS provider-specific filterspec";
		} else if (code == WSA_QOS_ESDMODEOBJ) {
			return "Invalid QoS shape discard mode object";
		} else if (code == WSA_QOS_ESHAPERATEOBJ) {
			return "Invalid QoS shaping rate object";
		} else if (code == WSA_QOS_RESERVED_PETYPE) {
			return "Reserved policy QoS element type";
		} else {
			return "Unknown error";
		}
	}

	Error server_error_windows(int code) {
		return error_custom(code, SERVER_ERROR_SPACE, windows_error_message);
	}
#endif
