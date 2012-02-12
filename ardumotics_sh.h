#ifndef _ARDUMOTICS_SH_H_
# define _ARDUMOTICS_SH_H_

# define ARDUMOTICS_SH_ARGS_MAX 10

struct ardumotics_cmd {
	const char *name;
	int (*callback) (const char **args);
};

void ardumotics_cmd_exec(char *cmd);

#endif /* !_ARDUMOTICS_SH_H_ */
