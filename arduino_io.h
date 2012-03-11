#ifndef _ARDUINO_IO_H_
# define _ARDUINO_IO_H_

# include <stdint.h>
# include <avr/pgmspace.h>

# define HIGH   0x1
# define LOW    0x0

# define INPUT  0x0
# define OUTPUT 0x1

# define A0			14
# define A1			15
# define A2			16
# define A3			17
# define A4			18
# define A5			19
# define A6			20
# define A7			21


void arduino_io_pin_mode(uint8_t pin, int mode);
void arduino_io_outd(uint8_t pin, int val);

int arduino_io_strtoi(const char *port);

#endif /* !_ARDUINO_IO_H_ */
