#include "drivers/mouse/mouse.h"

#include <stdint.h>
#include "drivers/gpio/gpio.h"

#include "lib/printk.h"

static const int gpio_clock = 23;
static const int gpio_data  = 24;
static int irq;

int mouse_init(void) {

    uint32_t status;

    // Request the clock and data pins.
    status = gpio_request(gpio_clock, "mouse_clock");
    if (status < 0) return -1;
    status = gpio_request(gpio_clock, "mouse_data");
    if (status < 0) return -1;

    // Those are inputs.
    gpio_direction_input(gpio_clock);
    gpio_direction_input(gpio_data);

    // Get the IRQ number for the clock,
    // since that's what we'll be watching.
    irq = gpio_to_irq(gpio_clock);
    if (irq < 0) return -1;

    // Watch the falling edge and enable.
    gpio_set_falling(gpio_clock);
    irq_enable(irq);

    printk("mouse_init successful.\n");
    return 0;

}

void mouse_cleanup(void) {

    // Release the GPIO pins.
	gpio_free(gpio_data);
	gpio_free(gpio_clock);

}

int mouse_interrupt_handler(void) {

    // TODO

    return 0;

}
