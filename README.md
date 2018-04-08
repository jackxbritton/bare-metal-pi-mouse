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

The device writes a bit on the data line when clock is high, and it is read by the host when clock is low. The clock frequency is 10-16.7 khz. The time from the rising edge of a clock pulse to a data transition must be at least 5 microseconds. The time from a data transition to the falling edge of a clock pulse must be at least 5 microseconds and no greater than 25 microseconds.
