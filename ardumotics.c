#include <stdio.h>
#include <avr/io.h>

#include "ardumotics.h"
#include "ardumotics_mod.h"
#include "ardumotics_sh.h"
#include "arduino_io.h"
#include "arduino_uart.h"


int main(void)
{
	char *cmd;

	ardumotics_mod_register_all();
	arduino_uart_init(103);

	ARDUINO_PIN_MODE(13, OUTPUT);
	ARDUINO_OUTD(13, HIGH);

	puts_P(PSTR("Ardumotics configuration: OK"));
	puts_P(PSTR(""));
	printf_P(PSTR("Welcome to Ardumotics v%s shell\n"), ARDUMOTICS_VERSION);
	puts_P(PSTR("Enter 'help' for a list of commands."));
	puts_P(PSTR(""));
	printf_P(PSTR(ARDUMOTICS_PROMPT));

	while (1)
	{
		cmd = arduino_uart_getline();
		if (cmd)
		{
			ardumotics_cmd_exec(cmd);
			printf_P(PSTR(ARDUMOTICS_PROMPT));
			arduino_uart_continue();
		}
	}
	return 0;
}
