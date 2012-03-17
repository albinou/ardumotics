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

#include <stdlib.h>

#include "ardumotics_dev.h"
#include "ardumotics_errno.h"

static struct ardumotics_dev *dev_head = NULL;

static int ardumotics_dev_add(struct ardumotics_dev *dev)
{
	struct ardumotics_dev **d;
	int dd = 0;

	for (d = &dev_head; *d != NULL; d = &(*d)->next)
	{
		if (dd == (*d)->dd)
		{
			++dd;
			d = &dev_head;
		}
	}

	if (dd > UINT8_MAX)
		return -EMFILE;

	dev->dd = dd;
	dev->next = NULL;
	*d = dev;

	return dd;
}

int ardumotics_dev_register(const char *mod, const uint8_t *io_list,
                            int io_list_sz)
{
	const struct ardumotics_mod *m;
	struct ardumotics_dev *dev = NULL;
	uint8_t *io_l = NULL;
	void *private_data = NULL;
	int dd;
	int i;

	if ((m = ardumotics_mod_find(mod)) == NULL)
		return -ENOMOD;

	if (m->io_list_sz != io_list_sz)
		return -EINVAL;

	if (((dev = malloc(sizeof(struct ardumotics_dev))) == NULL) ||
	    ((io_l = malloc(m->io_list_sz * sizeof(uint8_t))) == NULL) ||
	    (m->private_data_sz &&
	     ((private_data = malloc(m->private_data_sz)) == NULL)))
	{
		dd = -ENOMEM;
		goto fail;
	}

	for (i = 0; i < io_list_sz; ++i)
		io_l[i] = io_list[i];

	dev->io_list = io_l;
	dev->private_data = private_data;
	dev->mod = m;

	if ((dd = ardumotics_dev_add(dev)) < 0)
		goto fail;

	m->init_dev(dev);

	return dd;

 fail:
	free(dev);
	free(io_l);
	free(private_data);
	return dd;
}

int ardumotics_dev_unregister(uint8_t dd)
{
	return 0;
}

struct ardumotics_dev *ardumotics_dev_find(int dd)
{
	struct ardumotics_dev *dev;

	for (dev = dev_head; (dev != NULL) && (dev->dd != dd); dev = dev->next)
		;

	return dev;
}

int ardumotics_dev_exec(int dd, const char *cmd, const char **args)
{
	struct ardumotics_dev *dev;

	if ((dev = ardumotics_dev_find(dd)) == NULL)
		return -ENODEV;
	return ardumotics_mod_exec(dev->mod, dev, cmd, args);
}

t_cmd_handler ardumotics_dev_get_fct(const struct ardumotics_dev *dev,
                                     const char *cmd)
{
	return ardumotics_mod_get_fct(dev->mod, cmd);
}
