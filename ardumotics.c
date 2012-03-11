#include <stdio.h>
#include <avr/io.h>

#include "ardumotics.h"
#include "ardumotics_dev.h"
#include "ardumotics_job.h"
#include "ardumotics_sh.h"
#include "arduino_io.h"
#include "arduino_uart.h"


int main(void)
{
	char *cmd;

	ardumotics_mod_register_all();
	arduino_uart_init(103);

	arduino_io_pin_mode(13, OUTPUT);
	arduino_io_outd(13, HIGH);

	puts_P(PSTR("Ardumotics configuration: OK"));
	puts_P(PSTR(""));
	printf_P(PSTR("Welcome to Ardumotics v%s shell\n"), ARDUMOTICS_VERSION);
	puts_P(PSTR("Enter 'help' for a list of commands."));
	puts_P(PSTR(""));
	printf_P(PSTR(ARDUMOTICS_PROMPT));

	while (1)
	{
		ardumotics_job_exec();
		cmd = arduino_uart_getline();
		if (cmd)
		{
			ardumotics_sh_exec(cmd);
			printf_P(PSTR(ARDUMOTICS_PROMPT));
			arduino_uart_continue();
		}
	}
	return 0;
}
