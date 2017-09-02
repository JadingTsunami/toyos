#include "string.h"
#include "display.h"
#include "io.h"

/* framebuffer location */
char *fb = (char *) 0x000B8000;

/* track cursor position internally to avoid excessive port reads */
unsigned short cursor_pos = 0;
unsigned short fg = FB_LIGHT_GREY;
unsigned short bg = FB_BLACK;

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
    fb[i] = c;
    fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void fb_move_cursor(unsigned short pos) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
    cursor_pos = pos;
}


void fb_move_cursor_rc(unsigned short row, unsigned short col) {
    unsigned short position = (row*80) + col;
    fb_move_cursor(position);
}

int fb_get_cursor_pos() {
    unsigned short offset;
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    offset = inb( FB_DATA_PORT ) << 8;
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    offset |= inb( FB_DATA_PORT );
    return offset;
}

void set_fg(unsigned char nfg) {
    if( nfg <= 0xF )
        fg = nfg;
}

void set_bg(unsigned char nbg) {
    if( nbg <= 0xF )
        bg = nbg;
}

void write(char* buf, unsigned int len) {
    unsigned int i = 0;
    for( i = 0; i < len; i++ ) {
        fb_write_cell(2*(cursor_pos+i),buf[i],fg,bg);
    }
    fb_move_cursor(cursor_pos+len);
}

void write_str(char* buf) {
    write( buf, strlen(buf) );
}
