#include "cpu.h"


void create_gdt_entry( unsigned int index, unsigned char type, unsigned char dpl ) {

    /* base is 0 */
    gdt_entries[index].base_low = GDT_SEGMENT_BASE        & 0xFFFF;
    gdt_entries[index].base_mid = (GDT_SEGMENT_BASE>>16)  & 0xFF;
    gdt_entries[index].base_high = (GDT_SEGMENT_BASE>>24) & 0xFF;

    /* lower 16-bits of limit */
    gdt_entries[index].limit_low = GDT_SEGMENT_LIMIT & 0xFFFF;

    /* 4 kB units, 32-bit operation size, 32-bit code */
    /* also contains upper portion of the limit */
    gdt_entries[index].granularity = (0xC0) | ((GDT_SEGMENT_LIMIT>>16) & 0xF);

    gdt_entries[index].aflags = (0x01 << 7) | ((dpl & 0x03) << 5) | (0x01 << 4) | (type & 0x0F);
}

void gdt_init() {
    /* create GDT structure */
    gdt_t final_gdt;
    final_gdt.size = sizeof(gdt_entry_t)*NUM_GDT_ENTRIES;
    final_gdt.address = (unsigned int)&gdt_entries;

    /* fill with entries */

    create_gdt_entry( 0, 0,   0 ); /* null gdt entry      */
    create_gdt_entry( 1, 0xA, 0 ); /* kernel code segment */
    create_gdt_entry( 2, 0x2, 0 ); /* kernel data segment */

    /* load into GDT */
    gdt_load( final_gdt );
}
