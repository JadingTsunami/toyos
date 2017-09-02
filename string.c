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

void memcpy(void* dst, void* src, unsigned int len) {
    char *csrc = (char*) src;
    char *cdst = (char*) dst;

    for( unsigned int i = 0; i < len; i++ ) {
        cdst[i] = csrc[i];
    }
}

