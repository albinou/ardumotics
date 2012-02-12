#include <stdlib.h>

#include "ardumotics_dev.h"
#include "ardumotics_errno.h"

static struct ardumotics_dev *dev_head;

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