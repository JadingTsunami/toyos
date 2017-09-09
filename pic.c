#include "io.h"
#include "pic.h"

void pic_init() {

    /* pic 1 init words */
    outb(PIC1_CMD_PORT,PIC1_INIT_1);
    outb(PIC1_DATA_PORT,PIC1_INIT_2);
    outb(PIC1_DATA_PORT,PIC1_INIT_3);
    outb(PIC1_DATA_PORT,PIC1_INIT_4);

    /* pic 2 init words */
    outb(PIC2_CMD_PORT,PIC2_INIT_1);
    outb(PIC2_DATA_PORT,PIC2_INIT_2);
    outb(PIC2_DATA_PORT,PIC2_INIT_3);
    outb(PIC2_DATA_PORT,PIC2_INIT_4);

    /* pic masking */
    outb(PIC1_DATA_PORT, 0xFC); /* timer and keyboard */
    outb(PIC2_DATA_PORT, 0xFF); /* no pic2 interrupts */

}

void pic_acknowledge(unsigned int interrupt) {
    if (interrupt < PIC1_START_INTERRUPT || interrupt > PIC2_END_INTERRUPT) {
      return;
    }

    if (interrupt >= PIC2_START_INTERRUPT) {
      outb(PIC2_PORT_A, PIC_ACK);
    }

    outb(PIC1_PORT_A, PIC_ACK);
}

