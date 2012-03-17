/*
 * Device driver API used by modules (modules directory)
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

#ifndef _ARDUMOTICS_DEV_H_
# define _ARDUMOTICS_DEV_H_

# include <stdint.h>

# include "ardumotics_mod.h"

struct ardumotics_dev {
	uint8_t				dd;							/**< device descriptor (unique) */
	uint8_t       *io_list;				/**< array of I/O port
					   the size of this array is module dependant */
	void          *private_data;

	const struct ardumotics_mod *mod;	/**< Ref to the module */
	struct ardumotics_dev *next; /**< next device of the list */
};

int ardumotics_dev_register(const char *module, const uint8_t *io_list,
                            int io_list_sz);
int ardumotics_dev_unregister(uint8_t dd);

struct ardumotics_dev *ardumotics_dev_find(int dd);
int ardumotics_dev_exec(int dd, const char *cmd, const char **args);

t_cmd_handler ardumotics_dev_get_fct(const struct ardumotics_dev *dev,
                                     const char *cmd);

#endif /* _ARDUMOTICS_DEV_H_ */
