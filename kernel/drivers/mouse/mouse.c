#include "drivers/mouse/mouse.h"

#include <stdint.h>
#include "drivers/gpio/gpio.h"

#include "lib/printk.h"

static const int gpio_clock = 23;
static const int gpio_data  = 24;
static int irq;

int mouse_init(void) {

    int status;

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

static void mouse_update(unsigned char bytes[4]) {

}

int mouse_interrupt_handler(void) {

    // TODO Do we have a scroll wheel?
    //      If so, collect four bytes instead of three.

    static int byte_counter       = 0,
               bit_counter        = 0,
               parity             = 0;
    static unsigned char bytes[4] = { 0, 0, 0, 0 };
    int bit;

    bit = gpio_get_value(gpio_data);

    switch (bit_counter) {

    case  0: // Start bit.

        if (bit != 0) {
            printk("Invalid start bit %x.\n", bit);
            goto mouse_interrupt_handler_failure;
        }

        break;

    case  9: // Parity bit.

        parity += bit;
        if (parity & 0x1 == 0) { // It's even (should be odd!).
            printk("Invalid parity %x.\n", parity);
            goto mouse_interrupt_handler_failure;
        }
        parity = 0;

        break;

    case 10: // Stop bit.

        if (bit != 1) {
            printk("Invalid stop bit %x.\n", bit);
            goto mouse_interrupt_handler_failure;
        }

        byte_counter = (byte_counter + 1) % 4; // TODO Set to 3 if no scroll wheel.
        if (byte_counter == 0) {

            // We just finished reading the final byte.

            mouse_update(bytes);

        }

        break;
    
    default: // Data bits.

        // Put the bit into the byte and add to parity.

        bytes[byte_counter] |= bit << (bit_counter-1);
        parity += bit;

        break;

    }

    // Increment bit_counter.

    bit_counter = (bit_counter + 1) % 11;

    return 0;

mouse_interrupt_handler_failure:

    bit_counter  = 0;
    parity       = 0;
    byte_counter = 0;
    bytes[0]     = 0;
    bytes[1]     = 0;
    bytes[2]     = 0;
    bytes[3]     = 0;
    return -1;

}
