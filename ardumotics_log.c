/*
 * Logging API
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

#include "ardumotics_log.h"

void ardumotics_log(const char *format, ...)
{
	return;
}

void ardumotics_log_mod(const struct ardumotics_mod *mod,
                        const char *info)
{
	printf_P(PSTR("module %s: %s"), mod->name, info);
}

void ardumotics_log_mod_err(const struct ardumotics_mod *mod, int err,
                            const char *info)
{
	printf_P(PSTR("module %s: error %d - %s"), mod->name, err, info);
}
