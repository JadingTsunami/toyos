#ifndef PIC_H_NIYOSK4F
#define PIC_H_NIYOSK4F

#define PIC1_PORT_A 0x20
#define PIC2_PORT_A 0xA0

#define PIC1_CMD_PORT  0x20
#define PIC1_DATA_PORT 0x21
#define PIC2_CMD_PORT  0xA0
#define PIC2_DATA_PORT 0xA1

#define PIC1_INIT_1 0x11
#define PIC1_INIT_2 0x20
#define PIC1_INIT_3 0x04
#define PIC1_INIT_4 0x01

#define PIC2_INIT_1 0x11
#define PIC2_INIT_2 0x28
#define PIC2_INIT_3 0x02
#define PIC2_INIT_4 0x01

/* The PIC interrupts have been remapped */
#define PIC1_START_INTERRUPT 0x20
#define PIC2_START_INTERRUPT 0x28
#define PIC2_END_INTERRUPT   PIC2_START_INTERRUPT + 7

#define PIC_ACK     0x20


/** pic_init:
 * Initialize PIC and set up keyboard.
 */
void pic_init();

/** pic_acknowledge:
 *  Acknowledges an interrupt from either PIC 1 or PIC 2.
 *
 *  @param num The number of the interrupt
 */
void pic_acknowledge(unsigned int interrupt);


#endif /* end of include guard: PIC_H_NIYOSK4F */
