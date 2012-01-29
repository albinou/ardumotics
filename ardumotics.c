#include <avr/io.h>

#include "ardumotics.h"
#include "ardumotics_module.h"
#include "arduino_io.h"


int main(void)
{
	ardumotics_modules_register_all();

	ARDUINO_PIN_MODE(13, OUTPUT);
	ARDUINO_OUTD(13, HIGH);
	while (1)
		;
	return 0;
}
