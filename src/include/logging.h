
#ifndef THE_COMPLIANT_LOGGING_HEAD
#define THE_COMPLIANT_LOGGING_HEAD

// logging.h is the ONLY header that does NOT include root.h
// thus, it includes string itself
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void log_abort ( const char* fmt, ... );
void log_err ( const char* fmt, ...  );
void log_warn( const char* fmt, ...  );
void log_note ( const char* fmt, ...  );

#endif
