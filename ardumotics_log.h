#ifndef _ARDUMOTICS_LOG_H_
# define _ARDUMOTICS_LOG_H_

# include "ardumotics_module.h"

void ardumotics_log(const char *format, ...);
void ardumotics_log_mod(const struct ardumotics_module *module,
                        const char *format, ...);
void ardumotics_log_mod_err(const struct ardumotics_module *module, int err,
                            const char *format, ...);

#endif /* !_ARDUMOTICS_LOG_H_ */
