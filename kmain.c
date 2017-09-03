#include "display.h"
#include "string.h"
#include "io.h"
#include "serial.h"

void kmain() {
    char str[6];
    char newstr[8];
    str[0] = 'h';
    str[1] = 'e';
    str[2] = 'l';
    str[3] = 'l';
    str[4] = 'o';
    str[5] = '\0';

    strcpy( newstr, str );

    str[0] = 'm';

    fb_write_cell(0,'A',FB_GREEN,FB_BLACK);
    fb_move_cursor(1600);
    write(str,5);
    set_fg(FB_GREEN);
    set_bg(FB_DARK_GREY);
    fb_move_cursor(1680);
    write(newstr,5);
    fb_move_cursor(fb_get_cursor_pos()+1);
    write_str(newstr);

    fb_move_cursor(1760);
    set_fg(FB_BLUE);
    set_bg(FB_LIGHT_GREY);
    newstr[0] = 'f';
    newstr[1] = 'o';
    newstr[2] = 'o';
    newstr[3] = '\n';
    newstr[4] = 'm';
    newstr[5] = 'o';
    newstr[6] = 'o';
    newstr[7] = '\0';

    serial_initialize(SERIAL_COM1_BASE);
    serial_write(newstr,strlen(newstr));
    write_str(newstr);

    newstr[0] = '\n';
    newstr[1] = '\0';

    write_str(newstr);

    fb_move_cursor_rc( FB_HEIGHT, FB_WIDTH-3 );
    /* for( int i = 0; i < 2*FB_WIDTH*FB_HEIGHT; i++ ) { */
    for( int i = 0; i < 160; i++ ) {
        newstr[0] = (char) ((i / FB_WIDTH) + 0x30);
        write( newstr, 1 );
        serial_write(newstr, 1);
        /* hacky delay loop */
        for( int j = 0; j < 50000; j++ ) {
            inb(0x80);
        }
    }

    return;
}
