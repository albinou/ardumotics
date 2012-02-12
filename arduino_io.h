#ifndef _ARDUINO_IO_H_
# define _ARDUINO_IO_H_

# include <stdint.h>
# include <avr/pgmspace.h>

# define HIGH   0x1
# define LOW    0x0

# define INPUT  0x0
# define OUTPUT 0x1

# define ARDUINO_NOT_A_PORT 0

# define ARDUINO_PB 2
# define ARDUINO_PC 3
# define ARDUINO_PD 4

extern volatile uint8_t *const arduino_io_port_to_mode[];
extern volatile uint8_t *const arduino_io_port_to_output[];
extern const uint8_t arduino_io_digital_pin_to_port[30];
extern const uint8_t arduino_io_digital_pin_to_bit_mask[30];


void arduino_io_pin_mode(uint8_t pin, int mode);
void arduino_io_outd(uint8_t pin, int val);

int arduino_io_strtoi(const char *port);

#endif /* !_ARDUINO_IO_H_ */
