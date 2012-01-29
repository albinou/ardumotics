#include <avr/io.h>

#include "ardumotics.h"
#include "ardumotics_module.h"


int main(void)
{
	ardumotics_modules_register_all();

  DDRB |= _BV(PB5);
  PORTB |= _BV(PB5);
  while (1)
    ;
  return 0;
}
