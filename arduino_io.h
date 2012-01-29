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

/**
 * Configure a PIN as INPUT or OUTPUT
 *
 * @param pin Arduino pin number
 * @param mode INPUT or OUTPUT
 */
# define ARDUINO_PIN_MODE(pin,mode)                     \
  do {                                                  \
  if (mode == INPUT) {                                  \
    *arduino_io_port_to_mode_PGM[                       \
        arduino_io_digital_pin_to_port_PGM[pin]] &=     \
      ~arduino_io_digital_pin_to_bit_mask_PGM[pin];     \
  } else {                                              \
    *arduino_io_port_to_mode_PGM[                       \
        arduino_io_digital_pin_to_port_PGM[pin]] |=     \
      arduino_io_digital_pin_to_bit_mask_PGM[pin];      \
  }                                                     \
  } while (0)

/**
 * Output the value to the specfied pin
 *
 * @param pin Arduino pin number
 * @param val HIGH or LOW
 */
# define ARDUINO_OUTD(pin,val)                          \
  do {                                                  \
  if (val == LOW) {                                     \
    *arduino_io_port_to_output_PGM[                     \
        arduino_io_digital_pin_to_port_PGM[pin]] &=     \
      ~arduino_io_digital_pin_to_bit_mask_PGM[pin];     \
  } else {                                              \
    *arduino_io_port_to_output_PGM[                     \
        arduino_io_digital_pin_to_port_PGM[pin]] |=     \
      arduino_io_digital_pin_to_bit_mask_PGM[pin];      \
  }                                                     \
  } while (0)


volatile uint8_t PROGMEM *const arduino_io_port_to_mode_PGM[] = {
	ARDUINO_NOT_A_PORT,
	ARDUINO_NOT_A_PORT,
	&DDRB,
	&DDRC,
	&DDRD,
};

volatile uint8_t PROGMEM *const arduino_io_port_to_output_PGM[] = {
	ARDUINO_NOT_A_PORT,
	ARDUINO_NOT_A_PORT,
	&PORTB,
	&PORTC,
	&PORTD,
};

const uint8_t PROGMEM arduino_io_digital_pin_to_port_PGM[30] = {
	ARDUINO_PD, /* 0 */
	ARDUINO_PD,
	ARDUINO_PD,
	ARDUINO_PD,
	ARDUINO_PD,
	ARDUINO_PD,
	ARDUINO_PD,
	ARDUINO_PD,
	ARDUINO_PB, /* 8 */
	ARDUINO_PB,
	ARDUINO_PB,
	ARDUINO_PB,
	ARDUINO_PB,
	ARDUINO_PB,
	ARDUINO_PC, /* 14 */
	ARDUINO_PC,
	ARDUINO_PC,
	ARDUINO_PC,
	ARDUINO_PC,
	ARDUINO_PC,
};

const uint8_t PROGMEM arduino_io_digital_pin_to_bit_mask_PGM[30] = {
	_BV(0), /* 0, port D */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
	_BV(0), /* 8, port B */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(0), /* 14, port C */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
};

#endif /* !_ARDUINO_IO_H_ */
