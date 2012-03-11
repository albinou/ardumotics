#include <stdlib.h>
#include <errno.h>

#include "arduino_io.h"
#include "ardumotics_errno.h"

#define ARDUINO_NOT_A_PORT 0

#define ARDUINO_PB 2
#define ARDUINO_PC 3
#define ARDUINO_PD 4


volatile uint8_t *const arduino_io_port_to_mode[] PROGMEM = {
	ARDUINO_NOT_A_PORT,
	ARDUINO_NOT_A_PORT,
	&DDRB,
	&DDRC,
	&DDRD,
};

volatile uint8_t *const arduino_io_port_to_output[] PROGMEM = {
	ARDUINO_NOT_A_PORT,
	ARDUINO_NOT_A_PORT,
	&PORTB,
	&PORTC,
	&PORTD,
};

const uint8_t arduino_io_digital_pin_to_port[30] PROGMEM = {
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

const uint8_t arduino_io_digital_pin_to_bit_mask[30] PROGMEM = {
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


/**
 * Configure a PIN as INPUT or OUTPUT
 *
 * @param pin Arduino pin number
 * @param mode mode INPUT or OUTPUT
 */
void arduino_io_pin_mode(uint8_t pin, int mode)
{
	uint8_t port;
	uint8_t mask;
	volatile uint8_t *out_mode;

	port = pgm_read_byte(arduino_io_digital_pin_to_port + pin);
	out_mode = (volatile uint8_t *)
		((uint16_t ) pgm_read_byte(arduino_io_port_to_mode + port));
	mask = pgm_read_byte(arduino_io_digital_pin_to_bit_mask + pin);

	if (mode == INPUT)
		*out_mode &= ~mask;
	else
		*out_mode |= mask;
}

/**
 * Output the value to the specfied pin
 *
 * @param pin Arduino pin number
 * @param val value HIGH or LOW
 */
void arduino_io_outd(uint8_t pin, int val)
{
	uint8_t port;
	uint8_t mask;
	volatile uint8_t *outd;

	port = pgm_read_byte(arduino_io_digital_pin_to_port + pin);
	outd = (volatile uint8_t *)
		((uint16_t) pgm_read_byte(arduino_io_port_to_output + port));
	mask = pgm_read_byte(arduino_io_digital_pin_to_bit_mask + pin);

	if (val == LOW)
		*outd &= ~mask;
	else
		*outd |= mask;
}

int arduino_io_strtoi(const char *port)
{
	int res;
	char *endstr;
	uint8_t analogs[] = { A0, A1, A2, A3, A4, A5, A6, A7 };

	if (port[0] == 'A')
	{
		res = strtol(port + 1, &endstr, 10);
		if (errno || (res < 0) || (res > 7) || (*endstr != '\0'))
			return -EINVAL;
		return analogs[res];
	}

	res = strtol(port, &endstr, 10);
	if (errno || (res < 0) || (res > UINT8_MAX) || (*endstr != '\0'))
		return -EINVAL;

	return res;
}
