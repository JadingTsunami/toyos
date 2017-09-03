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


char* int_to_str( char* buf, int i ) {
    if( buf == 0 ) return 0;
    char* ret = buf;
    if( i < 0 ) {
        *buf++ = '-';
        i = -i;
    }
    uint_to_str( buf, i );
    return ret;
}

char* uint_to_str( char* buf, unsigned int i ) {
    if( buf == 0 ) return 0;
    if( i == 0 ) {
        buf[0] = '0';
        buf[1] = '\0';
        return buf;
    }
    unsigned int pos = 0;
    for( pos = i; pos > 0; pos /= 10 ) {
        buf++;
    }
    *buf = '\0';
    for( pos = i; pos > 0; pos /= 10 ) {
        *--buf = (pos%10) + 0x30;
    }
    return buf;
}
