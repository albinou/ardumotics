#ifndef _ARDUMOTICS_LOG_H_
# define _ARDUMOTICS_LOG_H_

# include "ardumotics_mod.h"

void ardumotics_log(const char *format, ...);
void ardumotics_log_mod(const struct ardumotics_mod *mod,
                        const char *info);
void ardumotics_log_mod_err(const struct ardumotics_mod *mod, int err,
                            const char *info);

#endif /* !_ARDUMOTICS_LOG_H_ */
