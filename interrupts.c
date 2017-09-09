#include "interrupts.h"
#include "cpu.h"

idt_descriptor_t idt_descriptors[NUM_IDT_ENTRIES];
idt_t final_idt;

void interrupt_install_descriptor( unsigned int index, unsigned int address ) {
    idt_descriptors[index].offset_low = (address)&0xFFFF;
    idt_descriptors[index].segment_selector = CODE_SEGMENT;
    idt_descriptors[index].rsvd = 0;
    idt_descriptors[index].attributes = 0;
    idt_descriptors[index].attributes |= (1<<7); /* handler present in memory */
    idt_descriptors[index].attributes |= (1<<3); /* 32-bit size */
    idt_descriptors[index].attributes |= (0x6); /* 110 fixed */
    idt_descriptors[index].offset_high = (address>>16)&0xFFFF;
}

void idt_init() {
    final_idt.address = (unsigned int) &idt_descriptors;
    final_idt.size    = sizeof(idt_descriptor_t)*NUM_IDT_ENTRIES;
    load_idt( (unsigned int) &final_idt );
}

void interrupt_handler(struct cpu_state cpu, unsigned int interrupt, struct stack_state stack) {
    /* for now, do nothing */
    /* dummy instructions so compiler doesn't complain */
    cpu.eax = cpu.eax;
    interrupt = interrupt;
    stack.eip = stack.eip;
}
