#include "display.h"

void kmain() {
    fb_write_cell(0,'H',FB_GREEN,FB_DARK_GREY);
    fb_write_cell(2,'E',FB_GREEN,FB_WHITE);
    fb_write_cell(4,'L',FB_GREEN,FB_WHITE);
    fb_write_cell(6,'L',FB_GREEN,FB_WHITE);
    fb_write_cell(8,'O',FB_GREEN,FB_WHITE);
    fb_write_cell(2*80+0,'W',FB_BLUE,FB_WHITE);
    fb_write_cell(2*80+2,'O',FB_BLUE,FB_WHITE);
    fb_write_cell(2*80+4,'R',FB_BLUE,FB_WHITE);
    fb_write_cell(2*80+6,'L',FB_BLUE,FB_WHITE);
    fb_write_cell(2*80+8,'D',FB_BLUE,FB_WHITE);
    return;
}
