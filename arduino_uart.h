#ifndef _ARDUINO_UART_H_
# define _ARDUINO_UART_H_

# include <stdio.h>

extern FILE *uart_pgm;

void arduino_uart_init(uint16_t baudrate);
void arduino_uart_putchar(char c);
char *arduino_uart_getline(void);
void arduino_uart_flush(void);
void arduino_uart_continue(void);

#endif /* !_ARDUINO_UART_H_ */
