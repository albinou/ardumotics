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

#include <stdlib.h>
#include <string.h>

#include "ardumotics_mod.h"
#include "ardumotics_config.h"
#include "ardumotics_errno.h"

static struct ardumotics_mod *mod_head = NULL;


int ardumotics_mod_register(struct ardumotics_mod *module)
{
	struct ardumotics_mod *m;

	if (module->name == NULL)
		return -EINVAL;
	for (m = mod_head; m != NULL; m = m->next)
		if (strcmp(m->name, module->name) == 0)
			return -EINVAL;

	module->next = mod_head;
	mod_head = module;

	return 0;
}

int ardumotics_mod_unregister(struct ardumotics_mod *module)
{
	struct ardumotics_mod *m;
	struct ardumotics_mod *prev = mod_head;

	if (module->name == NULL)
		return -EINVAL;
	for (m = mod_head; m != NULL; m = m->next)
	{
		if (strcmp(m->name, module->name) == 0)
			break;
		prev = m;
	}
	if (m == NULL)
		return -EINVAL;

	prev->next = m->next;
  return 0;
}

struct ardumotics_mod *ardumotics_mod_find(const char *name)
{
	struct ardumotics_mod *m;

	for (m = mod_head; m != NULL; m = m->next)
		if (strcmp(m->name, name) == 0)
			return m;

	return NULL;
}

int ardumotics_mod_exec(const struct ardumotics_mod *module,
                        struct ardumotics_dev *dev,
                        const char *cmd, const char **args)
{
	const struct ardumotics_mod_cmd *c;

	for (c = module->cmd; c->name != NULL; ++c)
		if (strcmp(c->name, cmd) == 0)
			return c->fct(dev, args);

	return -ENOCMD;
}

t_cmd_handler ardumotics_mod_get_fct(const struct ardumotics_mod *mod,
                                     const char *cmd)
{
	const struct ardumotics_mod_cmd *c;

	for (c = mod->cmd; c->name != NULL; ++c)
		if (strcmp(c->name, cmd) == 0)
			return c->fct;

	return NULL;
}

int ardumotics_mod_nbargs(const char **args)
{
	int res;

	for (res = 0; args[res] != NULL; ++res)
		;
	return res;
}
