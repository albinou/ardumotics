#ifndef _ARDUMOTICS_DEV_H_
# define _ARDUMOTICS_DEV_H_

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

#endif /* _ARDUMOTICS_DEV_H_ */
