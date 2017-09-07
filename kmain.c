#include "display.h"
#include "string.h"
#include "io.h"
#include "serial.h"
#include "debug.h"
#include "cpu.h"

void kmain() {
    char str[6];
    char newstr[10];

    gdt_init();

    strcpy( str, "hello" );
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
    strcpy( newstr, "foo\nmoo\n" );

    serial_initialize(SERIAL_COM1_BASE);
    serial_write(newstr,strlen(newstr));
    serial_write(newstr,strlen(newstr));
    write_str(newstr);

    serial_debug_print( SEVERITY_FATAL, "Fatal message.\n" );
    serial_debug_print( SEVERITY_DEBUG, "Debug message.\n" );
    serial_debug_print( SEVERITY_INFOR, "Information message.\n" );

    newstr[0] = '\n';
    newstr[1] = '\0';

    write_str(newstr);

    fb_move_cursor_rc( 0, 0 );
    /* for( int i = 0; i < 2*FB_WIDTH*FB_HEIGHT; i++ ) { */
    for( int i = 0; i < FB_HEIGHT; i++ ) {
        newstr[0] = (i/10) + 0x30;
        newstr[1] = (i%10) + 0x30;
        newstr[2] = '\n';
        newstr[3] = '\0';

        write_str( newstr );
        serial_write_str( newstr );
    }

    write_str( int_to_str( newstr, sizeof(unsigned char) ) );
    write_str( "stop 1\nstart 2 " );
    write_str( int_to_str( newstr, -123 ) );
    write_str( "stop 2\nstart 3 " );
    write_str( int_to_str( newstr, 0 ) );
    write_str( "stop 3\nstart 4 " );
    write_str( uint_to_str( newstr, 0xdead ) );
    write_str( "stop 4\nstart 5 " );
    return;
}
