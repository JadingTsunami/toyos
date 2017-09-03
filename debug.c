#include "debug.h"
#include "serial.h"
#include "string.h"

void serial_debug_print(unsigned int severity, char* buf ) {

    char sevstr[SEVERITY_LEN];
    switch( severity ) {
        case SEVERITY_FATAL:
        strcpy( sevstr, FATAL_STR );
        break;
        case SEVERITY_ERROR:
        strcpy( sevstr, ERROR_STR );
        break;
        case SEVERITY_WARNG:
        strcpy( sevstr, WARNG_STR );
        break;
        case SEVERITY_INFOR:
        strcpy( sevstr, INFOR_STR );
        break;
        case SEVERITY_DEBUG:
        default:
        strcpy( sevstr, DEBUG_STR );
        break;
    }

    serial_write_str( sevstr );
    serial_write_str( buf );
}
