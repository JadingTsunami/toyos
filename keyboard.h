#ifndef KEYBOARD_H_AX4MTA3K
#define KEYBOARD_H_AX4MTA3K

#include "io.h"
#include "display.h"

#define KBD_DATA_PORT   0x60

#define SCAN_CODE_LSHIFT_DOWN (0x2A)
#define SCAN_CODE_RSHIFT_DOWN (0x36)

#define SCAN_CODE_LSHIFT_UP (0xAA)
#define SCAN_CODE_RSHIFT_UP (0xB6)

#define MAX_SCAN_CODE (0x39)

/** read_scan_code:
 *  Reads a scan code from the keyboard
 *
 *  @return The scan code (NOT an ASCII character!)
 */
unsigned char read_scan_code(void);

void keyboard_handle_interrupt();

#endif /* end of include guard: KEYBOARD_H_AX4MTA3K */
