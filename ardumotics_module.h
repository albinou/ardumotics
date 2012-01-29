#ifndef _ARDUMOTICS_MODULE_H_
# define _ARDUMOTICS_MODULE_H_

# include <stdint.h>

struct ardumotics_module_cmd {
	char *cmd;
	int (*fct) (char *res, const char* args);
};

struct ardumotics_module {
	char          *name;
	uint8_t       *io_list;
	int           io_list_sz;

	void          *private_data;

	int (*init)(void);
	struct ardumotics_module_cmd *cmd;

	struct ardumotics_module *next;
};

void ardumotics_modules_register_all(void);

int ardumotics_module_register(struct ardumotics_module *module);
int ardumotics_module_unregister(struct ardumotics_module *module);

#endif /* !_ARDUMOTICS_MODULE_H_ */
