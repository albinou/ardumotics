#include <stdlib.h>
#include <string.h>

#include "ardumotics_module.h"
#include "ardumotics_config.h"
#include "ardumotics_errno.h"

#ifdef ARDUMOTICS_CONFIG_TEMP
# include "ardumotics_temp.h"
#endif /* !ARDUMOTICS_CONFIG_TEMP */


static struct ardumotics_module *module_head = NULL;


void ardumotics_modules_register_all(void)
{
#ifdef ARDUMOTICS_CONFIG_TEMP
	ardumotics_temp_register();
#endif /* !ARDUMOTICS_CONFIG_TEMP */
}

int ardumotics_module_register(struct ardumotics_module *module)
{
	struct ardumotics_module *m;

	if (module->name == NULL)
		return -EINVAL;
	for (m = module_head; m != NULL; m = m->next)
		if (strcmp(m->name, module->name) == 0)
			return -EINVAL;

	module->next = module_head;
	module_head = module;

	return 0;
}

int ardumotics_module_unregister(struct ardumotics_module *module)
{
	struct ardumotics_module *m;
	struct ardumotics_module *prev = module_head;

	if (module->name == NULL)
		return -EINVAL;
	for (m = module_head; m != NULL; m = m->next)
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

static int ardumotics_module_exec_cmd(const struct ardumotics_module *module,
                                      const char *cmd, const char **args)
{
	const struct ardumotics_module_cmd *c;

	for (c = module->cmd; c->name != NULL; ++c)
		if (strcmp(c->name, cmd) == 0)
			return c->fct(args);

	return -ENOCMD;
}

int ardumotics_module_exec(const char *module, const char *cmd,
                           const char **args)
{
	const struct ardumotics_module *m;

	for (m = module_head; m != NULL; m = m->next)
		if (strcmp(m->name, module) == 0)
			return ardumotics_module_exec_cmd(m, cmd, args);

	return -ENOMOD;
}
