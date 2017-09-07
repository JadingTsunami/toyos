#ifndef INCLUDE_CPU_H
#define INCLUDE_CPU_H

#define NUM_GDT_ENTRIES (3)

#define GDT_SEGMENT_BASE  (0)
#define GDT_SEGMENT_LIMIT (0xFFFFF)

struct gdt {
    unsigned short size;
    unsigned int address;
} __attribute__((packed));
typedef struct gdt gdt_t;

struct gdt_entry {
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_mid;
    unsigned char aflags;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));
typedef struct gdt_entry gdt_entry_t;

gdt_entry_t gdt_entries[NUM_GDT_ENTRIES];

/* asm function */
void gdt_load( gdt_t );

void create_gdt_entry( unsigned int index, unsigned char type, unsigned char dpl );

void gdt_init();

#endif /* INCLUDE_CPU_H */
