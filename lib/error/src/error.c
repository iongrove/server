#include <string.h>
#include "error.h"

static char* default_error_message(int code) {
	if (code == ERROR_CODE_OK) {
		return "Success";
	} else {
		return "Unknown error";
	}
}

Error error_custom(int code, const char* space, f_message message_f) {
	Error error;
	error.code = code;
	error.space = space;
	error.message_f = message_f;
	return error;
}

Error error_new(int code) {
	return error_custom(code, "error", default_error_message);
}

Error error_ok() {
	return error_new(ERROR_CODE_OK);
}

int error_code(Error error) {
	return error.code;
}

char* error_message(Error error) {
	return error.message_f(error.code);
}

bool error_is(Error error, Error other) {
	return error_is_sibling(error, other) && error.code == other.code;
}

bool error_is_from(Error error, const char* space) {
	return strcmp(error.space, space) == 0;
}

bool error_is_related(Error error, Error other) {
	return error_is_from(error, other.space);
}

bool error_is_sibling(Error error, Error other) {
	return error_is_related(error, other) && error.message_f == other.message_f;
}

bool error_is_ok(Error error) {
	return error.code == ERROR_CODE_OK;
}
