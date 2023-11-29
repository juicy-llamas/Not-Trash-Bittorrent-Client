 
#ifndef I_AM_GROOT_HEAD__xXEXTRA_DISTINCTIVE_VERSIONXx
#define I_AM_GROOT_HEAD__xXEXTRA_DISTINCTIVE_VERSIONXx

/*
 * IMPORTANT Definitions.
 */

// uses custom assert functions
#define USE_ASSERT

// disables asserts. Up to the builder.
// #define NDEBUG

// uses the logging macros instead of the logging functions defined in logging.h,
// which write to both stdout/err and a log file (tbd). Should be disabled once
// the logging macros are sufficiently tested and safe. You cannot use the logger
// functions and debug at the same time.
#define USE_LOGGING_MACROS

/*
 * Basic C stdlib includes
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define STRCNV_PVT( x ) x
#define STRCNV( x ) #x

#ifdef USE_ASSERT

	#define massert_pfx( vital ) printf( "%sssertion failed (" __FILE__ ": %i): ",								\
	(vital) ? "Vital a" : "A", __LINE__ );

	#define massert( val1, cond, val2, fmt ) ({																\
		if ( !( (val1) (cond) (val2) ) ) {																		\
			masssert_pfx( 1 );																					\
			fprintf( stderr, "%s %s %s is not true (" (fmt) " is not %s to " (fmt) "\n", __LINE__,				\
				STRCNV( val1 ), STRCNV( cond ), STRCNV( val2 ), (val1), STRCNV( cond ), (val2) );				\
		}																										\
	})

	#define massert_pvec( vec, size, lep, rep ) ({					\
		printf( (lep) ? "[ " : "... " );							\
		for ( int i = 0; i < size; i++ ) {							\
			printf( "0x%02X, ", ((unsigned char*)vec)[ i ] );		\
		}															\
		printf( (rep) ? "]" : " ..." );								\
	})

	#define massert_mem_rng( ptr1, ptr2, byteamt, range ) ({		\
		unsigned char* p1 = (unsigned char*)(ptr1);					\
		unsigned char* p2 = (unsigned char*)(ptr2);					\
		int lep = 1;												\
		int rep = 1;												\
		massert_vtl( (ptr1), !=, 0, "0x%016lX" );															\
		massert_vtl( (ptr2), !=, 0, "0x%016lX" );															\
		for ( size_t i = 0; i < (byteamt) ) {																\
			if ( *(p1 + i) != *(p2 + i) ) {																	\
				massert_pfx( 0 );																			\
				printf( "buff %s isn't equal to buff %s\n", STRCNV( ptr1 ), STRCNV( ptr2 ) );				\
				if ( i < 3 )																				\
					lep = 0;																				\
				if ( i > byteamt - 3 )																		\
					rep = 0;																				\
				massert_pvec( (p1 + i - 3), 6, lep, rep );													\
			}														\
		}															\
	})

#else
	#define massert_vtl( val1, cond, val2 fmt ) (void)0
	#define massert_mem_rng( ptr1, ptr2, byteamt, range ) (void)0
#endif

/*
 * Helper logging macros
 */

#ifdef USE_LOGGING_MACROS

	#define log_abort( fmt, ... ) ({									\
		char* estr = strerror( errno );									\
		fprintf( stderr, "FATAL ERROR (file %s, line %i): " 			\
				fmt ": %s\n", __FILE__, __LINE__, 						\
				##__VA_ARGS__, estr );									\
		abort();														\
	})

	#define log_err( fmt, ... ) ({										\
		char* estr = strerror( errno );									\
		fprintf( stderr, "ERROR (file %s, line %i): " 					\
				fmt ": %s\n", __FILE__, __LINE__, 						\
				##__VA_ARGS__, estr );									\
	})

	#define log_warn( fmt, ... ) 						 				\
		printf( "WARNING (file %s, line %i): " fmt "\n",				\
				__FILE__, __LINE__, ##__VA_ARGS__ );

	#define log_note( fmt, ... ) 										\
		printf( "LOG (file %s, line %i): " fmt "\n",					\
				__FILE__, __LINE__, ##__VA_ARGS__ );

	#ifndef NDEBUG
		#define log_dbgnote( fmt, ... )  								\
			printf( "DEBUG (file %s, line %i): " fmt "\n",				\
					__FILE__, __LINE__, ##__VA_ARGS__ );

// 		vec is a void* array (any will do) and
		#define printvec( vec, size ) ({								\
			printf( "PRINTING VECTOR \"%s\" (file %s, line %i): \n[ ",	\
					#vec, __FILE__, __LINE__ );							\
			for ( int i = 0; i < size; i++ ) {							\
				printf( "0x%02X, ", ((char*)vec)[ i ] );				\
				if ( i != 0 && i % 16 == 0 )							\
					printf( "\n" );										\
			}															\
			printf( "]" );												\
		})
	#else
		#define log_dbg( fmt, ... ) ((void)0)
		#define printvec( vec, size ) ((void)0)
	#endif

#else
	#include "logging.h"
	#define log_dbgnote( fmt, ... ) ((void)0)
	#define printvec( vec, size ) ((void)0)
#endif

/*
 * Other useful macros, such as suppressing the unused warning.
 */

#define UNUSED( a ) ( (void)( 0 + a ) )

#endif
