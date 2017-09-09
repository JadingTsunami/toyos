#ifndef INTERRUPTS_H_MWQSIIYG
#define INTERRUPTS_H_MWQSIIYG

#define NUM_IDT_ENTRIES (256)

struct idt {
	unsigned short size;
	unsigned int address;
} __attribute__((packed));
typedef struct idt idt_t;

struct idt_descriptor {
    unsigned short offset_low;
    unsigned short segment_selector;

    unsigned char rsvd;
    unsigned char attributes;
    unsigned short offset_high;
} __attribute__((packed));
typedef struct idt_descriptor idt_descriptor_t;

struct cpu_state {
	unsigned int edi;
	unsigned int esi;
	unsigned int ebp;
	unsigned int edx;
	unsigned int ecx;
	unsigned int ebx;
	unsigned int eax;
	unsigned int esp;
} __attribute__((packed));
typedef struct cpu_state cpu_state_t;

struct stack_state {
    unsigned int error_code;
    unsigned int eip;
    unsigned int cs;
    unsigned int eflags;
} __attribute__((packed));
typedef struct stack_state stack_state_t;

void interrupt_handler(struct cpu_state cpu, unsigned int interrupt, struct stack_state stack);

/* from asm */
void load_idt(unsigned int idt_addr);

void interrupt_install_descriptor( unsigned int index, unsigned int address );
void idt_init();

#endif /* end of include guard: INTERRUPTS_H_MWQSIIYG */
