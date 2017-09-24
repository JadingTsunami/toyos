#include "interrupts.h"
#include "cpu.h"
#include "string.h"
#include "debug.h"
#include "serial.h"
#include "keyboard.h"
#include "paging.h"

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

    /* install hardware interrupt handlers */
    /* FIXME: Would be better not to resort to absolute numbers here... */
    interrupt_install_descriptor( TIMER_INTERRUPT_OFFSET, (unsigned int) interrupt_handler_32 );
    interrupt_install_descriptor( KEYBOARD_INTERRUPT_OFFSET, (unsigned int) interrupt_handler_33 );
    interrupt_install_descriptor( PAGING_INTERRUPT_OFFSET, (unsigned int) interrupt_handler_14 );

    final_idt.address = (unsigned int) &idt_descriptors;
    final_idt.size    = sizeof(idt_descriptor_t)*NUM_IDT_ENTRIES;
    load_idt( final_idt );
}

unsigned int ticks = 0;

void interrupt_handler(struct cpu_state cpu, unsigned int interrupt, struct stack_state stack) {
    /* for now, do nothing */
    /* dummy instructions so compiler doesn't complain */
    cpu.eax = cpu.eax;
    stack.eip = stack.eip;
    char buf[32];

    switch( interrupt ) {
        case 0x20:
            ticks++;
            serial_write_str( "Timer interrupt; ticks: " );
            serial_write_str( uint_to_str( buf, ticks ) );
            serial_write_str ("\n" );
            pic_acknowledge(interrupt);
            break;
        case 0x21:
            keyboard_handle_interrupt();
            pic_acknowledge(interrupt);
            break;
        case PAGING_INTERRUPT_OFFSET:
            page_fault();
            break;
        default:
            log("Spurious interrupt. Number:");
            log(uint_to_str(buf, interrupt));
            pic_acknowledge(interrupt);
            break;
    }
}

void enable_interrupts() {
    asm("sti");
}
void disable_interrupts() {
    asm("cli");
}
