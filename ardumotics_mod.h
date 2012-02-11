#ifndef _ARDUMOTICS_MOD_H_
# define _ARDUMOTICS_MOD_H_

# include <stdint.h>

struct ardumotics_mod_cmd {
	char *name;
	int (*fct) (const char** args);
};

struct ardumotics_mod {
	char          *name;
	uint8_t       *io_list;
	int           io_list_sz;

	void          *private_data;

	int (*init)(void);
	const struct ardumotics_mod_cmd *cmd;

	struct ardumotics_mod *next;
};

void ardumotics_mod_register_all(void);

int ardumotics_mod_register(struct ardumotics_mod *module);
int ardumotics_mod_unregister(struct ardumotics_mod *module);

int ardumotics_mod_exec(const char *module, const char *cmd,
                        const char **args);

#endif /* !_ARDUMOTICS_MOD_H_ */
