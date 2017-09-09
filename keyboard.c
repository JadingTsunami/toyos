#include "keyboard.h"

char scan_codes[] = {
    0,
    0, /* esc */
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
    0, /* backspace */
    ' ', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
    '\n', /* enter */
    0, /*LCtrl */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',
    '`',
    0, /*LShift*/
    '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
    0, /*rshift*/
    0, /* keypad-* */
    0, /*'LAlt*/
    ' ', /* space bar */
};

char shift_scan_codes[] = {
    0,
    0, /* esc */
    '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+',
    0, /* backspace */
    ' ', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}',
    '\n', /* enter */
    0, /*LCtrl */
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"',
    '~',
    0, /*LShift*/
    '|',
    'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?',
    0, /*rshift*/
    0, /* keypad-* */
    0, /*'LAlt*/
    ' ', /* space bar */
};



unsigned char read_scan_code(void) {
    return inb(KBD_DATA_PORT);
}

unsigned char shift = 0;
void keyboard_handle_interrupt() {
    unsigned char c = read_scan_code();

    if( c == SCAN_CODE_LSHIFT_DOWN || c == SCAN_CODE_RSHIFT_DOWN ) {
        shift = 1;
    }

    if( c == SCAN_CODE_LSHIFT_UP || c == SCAN_CODE_RSHIFT_UP ) {
        shift = 0;
    }

    if( c > MAX_SCAN_CODE ){
        return;
    } else {
        char buf[6];
        if( shift ) {
            buf[0] = shift_scan_codes[c];
        } else {
            buf[0] = scan_codes[c];
        }
        buf[1] = '\0';
        write_str(buf);
    }
    
}
