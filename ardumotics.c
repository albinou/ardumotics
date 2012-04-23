/*
 * Main function of the Ardumotics Operating System
 *
 * Copyright 2012 Albin Kauffmann <albin.kauffmann@gmail.com>
 *
 * This file is part of Ardumotics.
 *
 * Ardumotics is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Ardumotics is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Ardumotics.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <avr/io.h>

#include "ardumotics_dev.h"
#include "ardumotics_job.h"
#include "ardumotics_sh.h"
#include "arduino_io.h"
#include "arduino_uart.h"

# define ARDUMOTICS_VERSION "0.1-(git)"
# define ARDUMOTICS_PROMPT "shell> "


int main(void)
{
	char *cmd;

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
