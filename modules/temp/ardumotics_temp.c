#include <stdio.h>
#include <avr/pgmspace.h>

#include "ardumotics_mod.h"
#include "ardumotics_log.h"

#include "ardumotics_temp.h"

static int ardumotics_temp_get (const char **args);

static const struct ardumotics_mod_cmd ardumotics_temp_cmd[] = {
	{ "get", ardumotics_temp_get },
	{ NULL, NULL },
};

static struct ardumotics_mod module_temp =
	{
		.name =             "temp",
		.io_list_sz =       1,
		.private_data_sz =  0,

		.init_dev =         NULL,
		.cmd =              ardumotics_temp_cmd,
	};

void ardumotics_temp_register(void)
{
	int err;

	if ((err = ardumotics_mod_register(&module_temp)))
		ardumotics_log_mod_err(&module_temp, err, "can't register the module");
}

static int ardumotics_temp_get (const char **args)
{
	puts_P(PSTR("OK"));
	return 0;
}
