#ifndef SERVER_TYPES_H
	#define SERVER_TYPES_H

	#ifndef TYPE_BYTE
		#define TYPE_BYTE
		typedef unsigned char byte;
	#endif

	#ifndef TYPE_UMAX
		#define TYPE_UMAX
		#if __STDC_VERSION__ >= 199901L
			#define TYPE_UMAX_LONG 1
			typedef unsigned long long int umax;
		#else
			#define TYPE_UMAX_LONG 0
			typedef unsigned long int umax;
		#endif
	#endif

	#ifndef TYPE_U16
		#define TYPE_U16
		typedef unsigned short int u16;
	#endif

	#ifndef TYPE_U32
		#define TYPE_U32
		typedef unsigned long int u32;
	#endif
#endif
