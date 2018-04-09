# Bare Metal Pi Mouse.

ECE598 project where we interface with a PS/2 mouse on Raspberry Pi _from scratch_.

# Notes.

## PS/2.

[http://www.burtonsys.com/ps2\_chapweske.htm](http://www.burtonsys.com/ps2_chapweske.htm)

Clock and data lines. To let the device send data, the host must set both lines to high.

All data is transmitted one byte at a time and each byte is sent in a frame consisting of 11-12 bits.These bits are:

Data is transmitted one byte at a time. Each byte is sent in a frame of 11 or 12 bits.

  * start bit (always 0)
  * 8 data bites, least significant bit first
  * 1 parity bit (odd parity)
  * 1 stop bit (always 1)
  * 1 ack bit (host-to-device communication only)

The device writes a bit on the data line when clock is high, and it is read by the host when clock is low. The clock frequency is 10-16.7 khz. The time from the rising edge of a clock pulse to a data transition must be at least 5 microseconds. The time from a data transition to the falling edge of a clock pulse must be at least 5 microseconds and no greater than 25 microseconds. Data is read on the falling edge of the clock.

[http://hades.mech.northwestern.edu/index.php/Interfacing\_with\_a\_mouse](http://hades.mech.northwestern.edu/index.php/Interfacing_with_a_mouse)

| Byte | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
|------|----|----|----|----|----|----|----|----|
| 1    | YV | XV | YS | XS | 1  | 0  | R  | L  |
| 2    | X7 | X6 | X5 | X4 | X3 | X2 | X1 | X0 |
| 3    | Y7 | Y6 | Y5 | Y4 | Y3 | Y2 | Y1 | Y0 |
| 4    | S7 | S6 | S5 | S4 | S3 | S2 | S1 | S0 |

YV and XV are overflow flags for the motion in Y and X directions respectively where 0 means negative motion and 1 means positive motion. R is for the right button and L is for the left button where 1 equals pressed and 0 equal unpressed. X0-X7 and Y0-Y7 are binary outputs of 0 to 255, which represent how far the mouse has moved in its respective directions since the last sample (the least significant digit is on the right). The fourth byte relates the delta scroll and only applies in a certain mode (i.e. mice with scroll wheels), so we'll need to experiment with it.

## Code.

  * kernel/include/drivers/bcm2835/bcm2835\_periph.h: GPIO and interrupt hardware stuff.
  * kernel/interrupts/interrupts.c: Interrupt handler.
