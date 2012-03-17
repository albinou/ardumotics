/*
 * Module API used by device drivers
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

#ifndef _ARDUMOTICS_MOD_H_
# define _ARDUMOTICS_MOD_H_

# include <stdint.h>

struct ardumotics_dev;

typedef int (*t_cmd_handler)(struct ardumotics_dev *dev,
                             const char** args);

struct ardumotics_mod_cmd {
	char          *name;          /**< command name */
	t_cmd_handler fct;            /**< callback of the command */
};

struct ardumotics_mod {
	char          *name;          /**< Name of the module (driver) */
	int           io_list_sz;     /**< Number of I/O port used by the module */
	int           private_data_sz; /**< size (bytes) of private data or 0 */

	int (*init_dev)(struct ardumotics_dev *dev); /**< NULL or device init fct */
	int (*clean_dev)(struct ardumotics_dev *dev); /**< NULL or device clean fct */
	const struct ardumotics_mod_cmd *cmd; /**< NULL terminated list of commands */

	struct ardumotics_mod *next;  /**< next module of the list */
};

void ardumotics_mod_register_all(void);

int ardumotics_mod_register(struct ardumotics_mod *module);
int ardumotics_mod_unregister(struct ardumotics_mod *module);

struct ardumotics_mod *ardumotics_mod_find(const char *name);

int ardumotics_mod_exec(const struct ardumotics_mod *module,
                        struct ardumotics_dev *dev,
                        const char *cmd, const char **args);

t_cmd_handler ardumotics_mod_get_fct(const struct ardumotics_mod *mod,
                                     const char *cmd);

int ardumotics_mod_nbargs(const char **args);

#endif /* !_ARDUMOTICS_MOD_H_ */
