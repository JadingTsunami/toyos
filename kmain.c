#include "display.h"

void kmain() {
    char str[6];
    str[0] = 'h';
    str[1] = 'e';
    str[2] = 'l';
    str[3] = 'l';
    str[4] = 'o';

    fb_write_cell(0,'A',FB_GREEN,FB_BLACK);
    fb_move_cursor(1600);
    write(str,5);
    fb_move_cursor(1680);
    write(str,5);
    return;
}
