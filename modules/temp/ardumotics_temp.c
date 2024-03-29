/*
 * Temperature module
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
#include <avr/pgmspace.h>

#include "ardumotics_dev.h"
#include "ardumotics_log.h"

#include "ardumotics_temp.h"

static int ardumotics_temp_get(struct ardumotics_dev *dev, const char **args);

static const struct ardumotics_mod_cmd ardumotics_temp_cmd[] = {
	{ "get", ardumotics_temp_get },
	{ NULL, NULL },
};

static struct ardumotics_mod mod_temp =
	{
		.name =             "temp",
		.io_list_sz =       1,
		.private_data_sz =  0,

		.init_dev =         NULL,
		.cmd =              ardumotics_temp_cmd,
	};


static int ardumotics_temp_get(struct ardumotics_dev *dev, const char **args)
{
	puts_P(PSTR("OK"));
	return 0;
}

ARDUMOTICS_MOD_INIT (temp, &mod_temp)
