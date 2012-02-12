#include <stdio.h>
#include <avr/pgmspace.h>

#include "ardumotics_log.h"

void ardumotics_log(const char *format, ...)
{
	return;
}

void ardumotics_log_mod(const struct ardumotics_mod *mod,
                        const char *info)
{
	printf_P(PSTR("module %s: %s"), mod->name, info);
}

void ardumotics_log_mod_err(const struct ardumotics_mod *mod, int err,
                            const char *info)
{
	printf_P(PSTR("module %s: error %d - %s"), mod->name, err, info);
}
