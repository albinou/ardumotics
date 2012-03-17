/*
 * Arduino specific functions to use the serial console (UART)
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

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "arduino_uart.h"

#define ARDUINO_UART_BUFFER_SZ	64

static char arduino_uart_buffer[ARDUINO_UART_BUFFER_SZ];
static int arduino_uart_buffer_pos;
static int arduino_uart_buffer_ready;


static int uart_stdout_putchar(char c, FILE *stream);
static FILE uart_stdout_stream = FDEV_SETUP_STREAM(uart_stdout_putchar, NULL,
                                                   _FDEV_SETUP_WRITE);


void arduino_uart_init(uint16_t baudrate)
{
	arduino_uart_buffer_pos = 0;
	arduino_uart_buffer_ready = 0;

	UBRR0H = (baudrate >> 8) & 0xFF;
	UBRR0L = baudrate & 0xFF;
	UCSR0A &= ~(1 << U2X0);
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
	UCSR0B |= (1 << RXCIE0);

	sei();

	stdout = &uart_stdout_stream;
}


void arduino_uart_putchar(char c)
{
	if (c == '\n')
		arduino_uart_putchar('\r');
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
}


char *arduino_uart_getline(void)
{
	if (arduino_uart_buffer_ready)
		return arduino_uart_buffer;
	else
		return NULL;
}


void arduino_uart_flush(void)
{
	while (bit_is_set(UCSR0A, RXC0))
		UDR0;
}


void arduino_uart_continue(void)
{
	arduino_uart_buffer_ready = 0;
	arduino_uart_buffer_pos = 0;
	arduino_uart_flush();
	UCSR0B |= (1 << RXCIE0);
}


ISR(USART_RX_vect) {
	char c = UDR0;
	if (bit_is_clear(UCSR0A, FE0))
	{
		arduino_uart_putchar(c);
		if (c == '\r')
		{
			arduino_uart_putchar('\n');
			arduino_uart_buffer[arduino_uart_buffer_pos] = '\0';
			arduino_uart_buffer_ready = 1;
			UCSR0B &= ~_BV(RXCIE0);
		}
		else
		{
			arduino_uart_buffer[arduino_uart_buffer_pos] = c;
			++arduino_uart_buffer_pos;
		}
	}
}


static int uart_stdout_putchar(char c, FILE *stream)
{
	arduino_uart_putchar(c);
	return 0;
}
