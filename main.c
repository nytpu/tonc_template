#include <tonc.h>
#include "gbfs.h"

int
main(void)
{
	// Wait for vsync
	vid_vsync();

	// Bitmap mode 3, enable BG2 (bitmap layer)
	REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;

	// Plot RGB points
	m3_plot(119, 80, RGB15(31, 0, 0)); // Red
	m3_plot(120, 80, RGB15(0, 31, 0)); // Green
	m3_plot(121, 80, RGB15(0, 0, 31)); // Blue

	while (1); // Loop so you don't get nasal demons

	return 0;
}
