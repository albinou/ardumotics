#ifndef _ARDUMOTICS_JOB_H_
# define _ARDUMOTICS_JOB_H_

# include "ardumotics_dev.h"

struct ardumotics_job {
	/**
	 * if fct() returns a non-zero value, the job is removed from the list of
	 * jobs
	 */
	int (*fct)(struct ardumotics_dev *dev);
	struct ardumotics_dev *dev;

	struct ardumotics_job *next;
};

int ardumotics_job_add(struct ardumotics_job *job);
int ardumotics_job_del(struct ardumotics_job *job);

void ardumotics_job_exec(void);

#endif /* !_ARDUMOTICS_JOB_H_ */
