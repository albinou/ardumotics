#include <stdio.h>
#include <string.h>
#include <avr/pgmspace.h>

#include "ardumotics_cmd.h"
#include "ardumotics_mod.h"
#include "ardumotics_errno.h"

static int ardumotics_cmd_help(const char **args);
static int ardumotics_cmd_mod(const char **args);

static struct ardumotics_cmd ardumotics_cmds[] = {
	{ "help", ardumotics_cmd_help },
	{ "mod", ardumotics_cmd_mod },
	{ NULL, NULL },
};


static int ardumotics_cmd_split_args(const char *args[ARDUMOTICS_CMD_ARGS_MAX + 1],
                                     char *cmd)
{
	int i = 0;

	while ((*cmd != '\0') && (*cmd == ' '))
		++cmd;
	while (*cmd != '\0')
	{
		if (i >= ARDUMOTICS_CMD_ARGS_MAX)
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

void ardumotics_cmd_exec(char *cmd)
{
	struct ardumotics_cmd *p;
	const char *args[ARDUMOTICS_CMD_ARGS_MAX + 1];

	if (ardumotics_cmd_split_args(args, cmd))
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

static int ardumotics_cmd_help(const char **args)
{
	puts_P(PSTR("Ardumotics commands:"));
	puts_P(PSTR("  mod list:             list loaded modules"));
	puts_P(PSTR("  mod <name> [args]:    execute a command on a module"));
	puts_P(PSTR("  help:                 display this help message"));
	return 0;
}

static int ardumotics_cmd_mod(const char **args)
{
	const char *module;
	const char *cmd;
	int res;

	if ((args[1] == NULL) || (strcmp(args[1], "help") == 0))
	{
		puts_P(PSTR("usage: mod <name> <fct> [args]"));
		puts_P(PSTR("   or: mod list"));
		return 0;
	}
	if ((strcmp(args[1], "list") == 0))
	{
		puts_P(PSTR("TODO: loaded modules should be listed here :)"));
		return 0;
	}

	module = args[1];
	if (args[2] == NULL)
		cmd = "help";
	else
		cmd = args[2];
	res = ardumotics_mod_exec(module, cmd, &args[3]);
	if (res == -ENOMOD)
		printf_P(PSTR("%s: No such module\n"), module);
	if (res == -ENOCMD)
		printf_P(PSTR("%s: No such command \"%s\"\n"), module, cmd);
	return res;
}
