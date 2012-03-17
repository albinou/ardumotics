/*
 * Shell run with the serial console
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

#ifndef _ARDUMOTICS_SH_H_
# define _ARDUMOTICS_SH_H_

# define ARDUMOTICS_SH_ARGS_MAX 10

struct ardumotics_cmd {
	const char *name;
	int (*callback) (const char **args);
};

void ardumotics_sh_exec(char *cmd);

#endif /* !_ARDUMOTICS_SH_H_ */
