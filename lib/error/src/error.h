#ifndef ERROR_H
	#define ERROR_H

	#ifndef TYPE_BOOL
		#define TYPE_BOOL
		typedef enum { FALSE, TRUE } bool;
	#endif

	#define ERROR_CODE_OK 0
	#define ERROR_IF(EXP, CSQ) do { error = EXP; if (!error_is_ok(error)) CSQ; } while (0)
	#define ERROR_PRINT(FMT, EXP) ERROR_IF(EXP, fprintf(stderr, FMT, error_message(error)))
	#define ERROR_GOTO(LBL, EXP) ERROR_IF(EXP, goto LBL)
	#define ERROR_CLEAN(EXP) ERROR_GOTO(clean, EXP)
	#define ERROR(EXP) ERROR_IF(EXP, return error)

	typedef char* (*f_message)(int);

	typedef struct Error {
		f_message message_f;
		const char* space;
		int code;
	} Error;

	Error error_custom(int code, const char* space, f_message message_f);
	Error error_new(int code);
	Error error_ok();

	int error_code(Error error);
	char* error_message(Error error);

	bool error_is(Error error, Error other);
	bool error_is_from(Error error, const char* space);
	bool error_is_related(Error error, Error other);
	bool error_is_sibling(Error error, Error other);
	bool error_is_ok(Error error);
#endif
