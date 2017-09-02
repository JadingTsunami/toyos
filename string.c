#include "string.h"

unsigned int strlen( char* str ) {
    unsigned int i;

    if( str == 0 || *str == '\0' ) return 0;

    for( i = 0; *str++; i++ )
        ;
    return i;
}


void strcpy( char* dst, char* src ) {
    unsigned int len = strlen(src);
    unsigned int i;
    for( i = 0; i < len; i++ ) {
        dst[i] = src[i];
    }
    dst[i] = '\0';
}

