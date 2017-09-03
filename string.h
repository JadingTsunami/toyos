#ifndef INCLUDE_STRING_H
#define INCLUDE_STRING_H

#ifndef NULL
    #define NULL (0)
#endif

unsigned int strlen( char* str );

void strcpy( char* dst, char* src );

void memcpy(void* dst, void* src, unsigned int len);

char* int_to_str( char* buf, int i );
char* uint_to_str( char* buf, unsigned int i );

#endif /* INCLUDE_STRING_H */
