#include <stdlib.h>
#include <errno.h>

#include "arduino_io.h"
#include "ardumotics_errno.h"


volatile uint8_t *const arduino_io_port_to_mode_PGM[] PROGMEM = {
	ARDUINO_NOT_A_PORT,
	ARDUINO_NOT_A_PORT,
	&DDRB,
	&DDRC,
	&DDRD,
};

volatile uint8_t *const arduino_io_port_to_output_PGM[] PROGMEM = {
	ARDUINO_NOT_A_PORT,
	ARDUINO_NOT_A_PORT,
	&PORTB,
	&PORTC,
	&PORTD,
};

const uint8_t arduino_io_digital_pin_to_port_PGM[30] PROGMEM = {
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

const uint8_t arduino_io_digital_pin_to_bit_mask_PGM[30] PROGMEM = {
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


int ardumotics_io_strtoi(const char *port)
{
	int res;
	char *endstr;

	res = strtol(port, &endstr, 10);
	if (errno || (res < 0) || (res > UINT8_MAX) || (*endstr != '\0'))
		return -EINVAL;

	return res;
}
