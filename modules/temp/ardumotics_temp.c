#include <string.h>

#include "ardumotics_module.h"
#include "ardumotics_log.h"

#include "ardumotics_temp.h"

static int ardumotics_temp_init(void);
static int ardumotics_temp_get (char *res, const char *args);

static uint8_t module_io[] = { 255 };

static struct ardumotics_module_cmd ardumotics_temp_cmd[] = {
  { "get", ardumotics_temp_get }
};

static struct ardumotics_module module_temp =
	{
		.name =             "temp",
		.io_list =          module_io,
		.io_list_sz =       1,

		.private_data =     NULL,

		.init =             ardumotics_temp_init,
    .cmd =              ardumotics_temp_cmd,
	};

void ardumotics_temp_register(void)
{
	int err;

	if ((err = ardumotics_module_register(&module_temp)))
		ardumotics_log_mod_err(&module_temp, err, "can't register the module");
}

static int ardumotics_temp_init(void)
{
	return 0;
}

static int ardumotics_temp_get (char *res, const char *args)
{
  strcpy (res, "OK");
  return 0;
}
