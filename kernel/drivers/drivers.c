#include <stddef.h>
#include <stdint.h>

#include "lib/printk.h"

#include "drivers/drivers.h"
#include "drivers/led/led.h"
#include "drivers/timer/timer.h"
#include "drivers/serial/serial.h"
#include "drivers/framebuffer/framebuffer.h"
#include "drivers/framebuffer/framebuffer_console.h"

void drivers_init_all(void) {

	uint32_t framebuffer_width=800,framebuffer_height=600;

	/**************************/
	/* Device Drivers	  */
	/**************************/

	/* Set up ACT LED */
	led_init();

	/* Set up timer */
	timer_init();

	/* Enable the Framebuffer */
#if 0
	if (atag_info.framebuffer_x!=0) {
		framebuffer_width=atag_info.framebuffer_x;
	}
	if (atag_info.framebuffer_y!=0) {
		framebuffer_height=atag_info.framebuffer_y;
	}
#endif

	framebuffer_init(framebuffer_width,framebuffer_height,24);
	framebuffer_console_init();

	serial_enable_interrupts();

}
