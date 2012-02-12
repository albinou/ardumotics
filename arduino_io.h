#ifndef _ARDUINO_IO_H_
# define _ARDUINO_IO_H_

# include <stdint.h>
# include <avr/pgmspace.h>

# define HIGH   0x1
# define LOW    0x0

# define INPUT  0x0
# define OUTPUT 0x1

# define ARDUINO_NOT_A_PORT 0

# define ARDUINO_PB 2
# define ARDUINO_PC 3
# define ARDUINO_PD 4

/**
 * Configure a PIN as INPUT or OUTPUT
 *
 * @param pin Arduino pin number
 * @param mode INPUT or OUTPUT
 */
# define ARDUINO_PIN_MODE(pin,mode)                     \
  do {                                                  \
  if (mode == INPUT) {                                  \
    *arduino_io_port_to_mode_PGM[                       \
        arduino_io_digital_pin_to_port_PGM[pin]] &=     \
      ~arduino_io_digital_pin_to_bit_mask_PGM[pin];     \
  } else {                                              \
    *arduino_io_port_to_mode_PGM[                       \
        arduino_io_digital_pin_to_port_PGM[pin]] |=     \
      arduino_io_digital_pin_to_bit_mask_PGM[pin];      \
  }                                                     \
  } while (0)

/**
 * Output the value to the specfied pin
 *
 * @param pin Arduino pin number
 * @param val HIGH or LOW
 */
# define ARDUINO_OUTD(pin,val)                          \
  do {                                                  \
  if (val == LOW) {                                     \
    *arduino_io_port_to_output_PGM[                     \
        arduino_io_digital_pin_to_port_PGM[pin]] &=     \
      ~arduino_io_digital_pin_to_bit_mask_PGM[pin];     \
  } else {                                              \
    *arduino_io_port_to_output_PGM[                     \
        arduino_io_digital_pin_to_port_PGM[pin]] |=     \
      arduino_io_digital_pin_to_bit_mask_PGM[pin];      \
  }                                                     \
  } while (0)


extern volatile uint8_t *const arduino_io_port_to_mode_PGM[];
extern volatile uint8_t *const arduino_io_port_to_output_PGM[];
extern const uint8_t arduino_io_digital_pin_to_port_PGM[30];
extern const uint8_t arduino_io_digital_pin_to_bit_mask_PGM[30];


int ardumotics_io_strtoi(const char *port);

#endif /* !_ARDUINO_IO_H_ */
