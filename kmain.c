#include "display.h"
#include "string.h"
#include "io.h"
#include "serial.h"
#include "debug.h"
#include "cpu.h"
#include "interrupts.h"
#include "pic.h"
#include "multiboot.h"

typedef void (*call_module_t)(void);

void kmain( multiboot_info_t *mbinfo ) {
    char str[6];
    char newstr[10];

    /* early init code */
    gdt_init();
    idt_init();
    pic_init();
    enable_interrupts();
    serial_initialize(SERIAL_COM1_BASE);

    /* check module integrity */
    if( mbinfo->mods_count != 1 ) {
        write_str( "Bad module loaded!\n" );
        write_str( "Mods count: " );
        write_str( uint_to_str( str, mbinfo->mods_count ) );
    } else {
        write_str( "Module loaded!\n" );
        unsigned int program_address = ((module_t*) mbinfo->mods_addr)->mod_start;
        write_str( uint_to_str( newstr, mbinfo->flags ) );
        write_str( "!\n" );
        write_str( uint_to_str( newstr, mbinfo->mods_count ) );
        write_str( "!\n" );
        write_str( uint_to_str( newstr, program_address) );
        write_str( "!\n" );
        call_module_t start_program = (call_module_t) program_address;
        start_program();
    }
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

    serial_write(newstr,strlen(newstr));
    serial_write(newstr,strlen(newstr));
    write_str(newstr);

    return;
}
