#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <avr/pgmspace.h>

#include "ardumotics_sh.h"
#include "ardumotics_dev.h"
#include "ardumotics_errno.h"
#include "arduino_io.h"

static int ardumotics_sh_help(const char **args);
static int ardumotics_sh_mod(const char **args);
static int ardumotics_sh_dev(const char **args);

static struct ardumotics_cmd ardumotics_cmds[] = {
	{ "help", ardumotics_sh_help },
	{ "mod", ardumotics_sh_mod },
	{ "dev", ardumotics_sh_dev },
	{ NULL, NULL },
};


static int ardumotics_sh_split_args(const char *args[ARDUMOTICS_SH_ARGS_MAX + 1],
                                    char *cmd)
{
	int i = 0;

	while ((*cmd != '\0') && (*cmd == ' '))
		++cmd;
	while (*cmd != '\0')
	{
		if (i >= ARDUMOTICS_SH_ARGS_MAX)
			return -ENOMEM;
		args[i++] = cmd;
		while ((*cmd != '\0') && (*cmd != ' '))
			++cmd;
		if (*cmd == ' ')
		{
			*cmd = '\0';
			++cmd;
		}
		while ((*cmd != '\0') && (*cmd == ' '))
			++cmd;
	}
	args[i] = NULL;

	return 0;
}

void ardumotics_sh_exec(char *cmd)
{
	struct ardumotics_cmd *p;
	const char *args[ARDUMOTICS_SH_ARGS_MAX + 1];

	if (ardumotics_sh_split_args(args, cmd))
		return;

	for (p = ardumotics_cmds; p->name != NULL; ++p)
		if (strcmp(p->name, args[0]) == 0)
		{
			p->callback(args);
			break;
		}

	if (p->name == NULL)
		puts_P(PSTR("Unknown command: try \"help\" to get some help"));
}

static int ardumotics_sh_help(const char **args)
{
	puts_P(PSTR("Ardumotics commands:"));
	puts_P(PSTR("  mod list                              list loaded modules"));
	puts_P(PSTR("  mod <mod_name>                        display help on the module"));
	puts_P(PSTR("  dev <mod_name> register [i/o ...]     register a new device"));
	puts_P(PSTR("  dev <dd> unregister                   unregister the device"));
	puts_P(PSTR("  dev <dd> <cmd> [args ...]             execute a command on the device"));
	puts_P(PSTR("  help                                  display this help message"));
	return 0;
}

static int ardumotics_sh_mod(const char **args)
{
	if ((args[1] == NULL) || (strcmp(args[1], "help") == 0))
	{
		puts_P(PSTR("usage: mod list"));
		puts_P(PSTR("       mod <mod_name>"));
		return 0;
	}
	if ((strcmp(args[1], "list") == 0))
	{
		puts_P(PSTR("TODO: loaded modules should be listed here :)"));
		return 0;
	}
	printf_P(PSTR("TODO: should display help on the module %s :)\n"), args[1]);

	return 0;
}

static void ardumotics_sh_dev_help(void)
{
	puts_P(PSTR("usage: dev <mod_name> register [i/o ...]"));
	puts_P(PSTR("       dev <dd> unregister"));
	puts_P(PSTR("       dev <dd> <cmd> [args ...]"));
}

static int ardumotics_sh_dev(const char **args)
{
	uint8_t io_list[ARDUMOTICS_SH_ARGS_MAX - 3];
	char *endstr;
	long int dd;
	int res;
	int i;

	if ((args[1] == NULL) || (args[2] == NULL) || (strcmp(args[1], "help") == 0))
	{
		ardumotics_sh_dev_help();
		return 0;
	}

	dd = strtol(args[1], &endstr, 10);
	if (errno || (*endstr != '\0'))
	{
		if (strcmp(args[2], "register"))
		{
			ardumotics_sh_dev_help();
			return -EINVAL;
		}
		for (i = 0; args[i + 3] != NULL; ++i)
		{
			if ((res = arduino_io_strtoi(args[i + 3])) < 0)
			{
				puts_P(PSTR("Invalid I/O pin number"));
				return -EINVAL;
			}
			io_list[i] = res;
		}
		if ((res = ardumotics_dev_register(args[1], io_list, i)) < 0)
			printf_P(PSTR("Cannot register device (errno = %d)\n"), -res);
		else
			printf_P(PSTR("%s device registered (dd = %i)\n"), args[1], res);
		return res;
	}

	if ((dd < 0) || (dd > UINT8_MAX))
	{
		puts_P(PSTR("Invalid device descriptor"));
		return -ENODEV;
	}
	if (strcmp(args[2], "unregister") == 0)
	{
		if ((res = ardumotics_dev_unregister(dd)))
			printf_P(PSTR("Cannot unregister device %i (errno = %d)\n"), dd, -res);
		else
			printf_P(PSTR("%s device unregistered (dd = %i)\n"), args[2], res);
	}
	else
	{
		res = ardumotics_dev_exec(dd, args[2], &args[3]);
		if (res == -ENOCMD)
			printf_P(PSTR("No such command \"%s\"\n"), args[2]);
	}
	return res;
}
