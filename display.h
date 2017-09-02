#ifndef INCLUDE_DISPLAY_H
#define INCLUDE_DISPLAY_H


#define FB_BLACK         0
#define FB_BLUE          1
#define FB_GREEN         2
#define FB_CYAN          3
#define FB_RED           4
#define FB_MAGENTA       5
#define FB_BROWN         6
#define FB_LIGHT_GREY    7
#define FB_DARK_GREY     8
#define FB_LIGHT_BLUE    9
#define FB_LIGHT_GREEN   10
#define FB_LIGHT_CYAN    11
#define FB_LIGHT_RED     12
#define FB_LIGHT_MAGENTA 13
#define FB_LIGHT_BROWN   14
#define FB_WHITE         15

/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos);

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param row The row to move the cursor to.
 *  @param col The column to move the cursor to.
 */
void fb_move_cursor_rc(unsigned short row, unsigned short col);


/** fb_get_cursor_pos:
 *  Return cursor position. You must divide by 80 to get the row and modulo 80
 *  to get the column.
 */
int fb_get_cursor_pos();

/** write:
 *  Starting at the cursor, write a line of output to the screen.
 *
 *  @param buf The string to write.
 *  @param len The length of the string.
 */
void write(char* buf, unsigned int len);

#endif /* INCLUDE_DISPLAY_H */
