/*
 * LED module
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

#include "ardumotics_dev.h"
#include "ardumotics_log.h"
#include "arduino_io.h"

#include "ardumotics_led.h"

static int ardumotics_led_init(struct ardumotics_dev *dev);
static int ardumotics_led_on(struct ardumotics_dev *dev, const char **args);
static int ardumotics_led_off(struct ardumotics_dev *dev, const char **args);
static int ardumotics_led_toggle(struct ardumotics_dev *dev, const char **args);

static const struct ardumotics_mod_cmd ardumotics_led_cmd[] = {
	{ "on", ardumotics_led_on },
	{ "off", ardumotics_led_off },
	{ "toggle", ardumotics_led_toggle },
	{ NULL, NULL },
};

static struct ardumotics_mod mod_led =
	{
		.name =             "led",
		.io_list_sz =       1,
		.private_data_sz =  sizeof (char),

		.init_dev =         ardumotics_led_init,
		.cmd =              ardumotics_led_cmd,
	};


static int ardumotics_led_init(struct ardumotics_dev *dev)
{
	arduino_io_pin_mode(dev->io_list[0], OUTPUT);
	ardumotics_led_off(dev, NULL);
	return 0;
}

static int ardumotics_led_on(struct ardumotics_dev *dev, const char **args)
{
	arduino_io_outd(dev->io_list[0], HIGH);
	*((char *) dev->private_data) = HIGH;
	return 0;
}

static int ardumotics_led_off(struct ardumotics_dev *dev, const char **args)
{
	arduino_io_outd(dev->io_list[0], LOW);
	*((char *) dev->private_data) = LOW;
	return 0;
}

static int ardumotics_led_toggle(struct ardumotics_dev *dev, const char **args)
{
	if (*((char *) dev->private_data) == LOW)
		ardumotics_led_on(dev, args);
	else
		ardumotics_led_off(dev, args);
	return 0;
}

ARDUMOTICS_MOD_INIT (led, &mod_led)
