#include "display.h"

void kmain() {
    fb_write_cell(0,'H',FB_GREEN,FB_DARK_GREY);
    fb_move_cursor(1);
    fb_write_cell(0,'E',FB_GREEN,FB_WHITE);
    fb_move_cursor(2);
    fb_write_cell(0,'L',FB_GREEN,FB_WHITE);
    fb_move_cursor(3);
    fb_write_cell(0,'L',FB_GREEN,FB_WHITE);
    fb_write_cell(2,'O',FB_GREEN,FB_WHITE);
    fb_move_cursor(160);
    fb_write_cell(0,'W',FB_BLUE,FB_WHITE);
    fb_write_cell(2,'O',FB_BLUE,FB_WHITE);
    fb_write_cell(4,'R',FB_BLUE,FB_WHITE);
    fb_write_cell(8,'L',FB_BLUE,FB_WHITE);
    fb_write_cell(10,'D',FB_BLUE,FB_WHITE);
    return;
}
