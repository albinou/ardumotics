/*
 * Arduino specific functions to perform I/O
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
