// Uncomment to use production headers
//#define PRODUCTION

#ifndef PRODUCTION
// Include all tonc functions, better to only include files you're using
#include <tonc.h>
#else
// Trim these down to only what you're using. If you use all of these,
// just use tonc.h
#include <tonc_types.h> // Define useful data types and macros (almost required)
#include <tonc_memdef.h> // Register/memory locations & register macros
#include <tonc_bios.h> // BIOS control flags & registers (includes compression)
#include <tonc_core.h> // Many useful functions
#include <tonc_input.h> // Key checking and polling functions
#include <tonc_irq.h> // Used for managing interrupts
#include <tonc_math.h> // Math macros and LUTs
#include <tonc_oam.h> // Manage OAM attributes (including affines)
#include <tonc_tte.h> // Tonc Text Engine
#include <tonc_video.h> // Macros, functions, & defines for various video modes
#include <tonc_surface.h> // Create and manage surfaces
#include <tonc_nocash.h> // NoCash Debugging functions
#endif // PRODUCTION

int main(void) {
	// Wait for vsync (necessary for this? probably not, but good practice)
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
