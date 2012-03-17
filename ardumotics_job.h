/*
 * Job API (modules can run code by adding jobs)
 *
 * Copyright 2012 Albin Kauffmann <albin.kauffmann@gmail.com>
 *
 * This file is part of Ardumotics.
 *
 * Ardumotics is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Ardumotics is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Ardumotics.  If not, see <http://www.gnu.org/licenses/>.
 */

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
