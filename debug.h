#ifndef INCLUDE_DEBUG_H
#define INCLUDE_DEBUG_H

#define SEVERITY_LEN (9)

#define SEVERITY_FATAL   0
#define SEVERITY_ERROR   1
#define SEVERITY_WARNG   2
#define SEVERITY_INFOR   3
#define SEVERITY_DEBUG   4

#define FATAL_STR "FATAL: "
#define ERROR_STR "ERROR: "
#define WARNG_STR "WARNG: "
#define INFOR_STR "INFOR: "
#define DEBUG_STR "DEBUG: "

void log( char* buf );

void serial_debug_print(unsigned int severity, char* buf );

#endif  /*               INCLUDE_DEBUG_H */
