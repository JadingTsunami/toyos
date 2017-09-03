#include "string.h"
#include "display.h"
#include "io.h"

/* framebuffer location */
char *fb = (char *) 0x000B8000;

/* track cursor position internally to avoid excessive port reads */
unsigned int cursor_pos = 0;
unsigned short fg = FB_LIGHT_GREY;
unsigned short bg = FB_BLACK;

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
    fb[i] = c;
    fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void fb_move_cursor(unsigned short pos) {
    /* bounds checking -- if we go past the end of the
     * screen, wrap back
     */
    if ( pos > (FB_WIDTH + (FB_HEIGHT*FB_WIDTH)) ) {
        pos = pos % (FB_WIDTH+(FB_HEIGHT*FB_WIDTH));
    }
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
    cursor_pos = pos;
}


void fb_move_cursor_rc(unsigned short row, unsigned short col) {
    unsigned short position = (row*FB_WIDTH) + col;
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
    /* TODO: Add scrolling code. Should adjust
     * cursor to the proper position and scroll
     */
    unsigned short row = cursor_pos / FB_WIDTH;
    unsigned short col = cursor_pos % FB_WIDTH;

    for( i = 0; i < len; i++ ) {

        if( col > FB_WIDTH || buf[i] == '\n' ) {
            col = 0;
            row++;
        }

        if( row >= FB_HEIGHT ) {
            col = 0;
            row = FB_HEIGHT-1;
            /* move screen lines up 1 */
            for( int j = 1; j < FB_HEIGHT; j++ ) {
                memcpy( (void*)&(fb[2*(j-1)*FB_WIDTH]), (void*)&(fb[2*j*FB_WIDTH]), 2*FB_WIDTH );
            }

            /* clear last row */
            for( int j = 0; j < FB_WIDTH; j++ ) {
                fb[2*(FB_WIDTH*(FB_HEIGHT-1) + j)    ] = (char) ' ';
                fb[2*(FB_WIDTH*(FB_HEIGHT-1) + j) + 1] = (char) '\0';
            }
        }

        if( buf[i] != '\n' ) {
            fb_write_cell(2*(row*FB_WIDTH+col++),buf[i],fg,bg);
        }
    }
    fb_move_cursor(row*FB_WIDTH+col);
}

void write_str(char* buf) {
    write( buf, strlen(buf) );
}
