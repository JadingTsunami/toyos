#include "paging.h"
#include "serial.h"
#include "string.h"

unsigned int identity_page_directory[NUM_PAGE_TABLES] __attribute__((aligned(PAGE_FRAME_SIZE)));
unsigned int identity_page_table[NUM_PAGE_FRAMES]     __attribute__((aligned(PAGE_FRAME_SIZE)));

void init_identity_paging() {
    for( int i = 0; i < NUM_PAGE_TABLES; i++ ) {
        identity_page_directory[i] = 0x2;
    }
    identity_page_directory[0] = (unsigned int)identity_page_table;
    identity_page_directory[0] |= 3;

    for( int i = 0; i < NUM_PAGE_FRAMES; i++ ) {
        identity_page_table[i] = ( i << 12 ) | 3;
    }

    enable_paging_identity((unsigned int)identity_page_directory);
}

void page_fault() {
    serial_write_str( "Page fault detected." );
}
