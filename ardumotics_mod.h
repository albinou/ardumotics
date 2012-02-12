#ifndef _ARDUMOTICS_MOD_H_
# define _ARDUMOTICS_MOD_H_

# include <stdint.h>

struct ardumotics_dev;

struct ardumotics_mod_cmd {
	char *name;										/**< command name */
	int (*fct) (const char** args);	/**< callback of the command */
};

struct ardumotics_mod {
	char          *name;					/**< Name of the module (driver) */
	int           io_list_sz;			/**< Number of I/O port used by the module */
	int						private_data_sz; /**< size (bytes) of private data or 0 */

	int (*init_dev)(struct ardumotics_dev *dev); /**< NULL or device init function */
	const struct ardumotics_mod_cmd *cmd;	/**< NULL terminated list of commands */

	struct ardumotics_mod *next;	/**< next module of the list */
};

void ardumotics_mod_register_all(void);

int ardumotics_mod_register(struct ardumotics_mod *module);
int ardumotics_mod_unregister(struct ardumotics_mod *module);

struct ardumotics_mod *ardumotics_mod_find(const char *name);

int ardumotics_mod_exec(const char *module, const char *cmd,
                        const char **args);

#endif /* !_ARDUMOTICS_MOD_H_ */
