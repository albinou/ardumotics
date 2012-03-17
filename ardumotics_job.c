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

#include <stdlib.h>
#include <util/atomic.h>

#include "ardumotics_job.h"
#include "ardumotics_errno.h"

static struct ardumotics_job *job_head = NULL;

int ardumotics_job_add(struct ardumotics_job *job)
{
	struct ardumotics_job **j;
	int ret = 0;

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		for (j = &job_head; (*j != NULL) && (*j != job); j = &((*j)->next))
			;

		if (*j != NULL)
			ret = -EEXIST;
		else
		{
			job->next = NULL;
			*j = job;
		}
	}
	return ret;
}

int ardumotics_job_del(struct ardumotics_job *job)
{
	struct ardumotics_job **j;
	struct ardumotics_job *del;
	int ret = 0;

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		for (j = &job_head; (*j != NULL) && (*j != job); j = &((*j)->next))
			;
		if (*j == NULL)
			ret = -ENOJOB;
		else
		{
			del = *j;
			*j = del->next;
			del->next = NULL;
		}
	}
	return ret;
}

void ardumotics_job_exec(void)
{
	struct ardumotics_job *j;

	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		j = job_head;
	}
	while (j != NULL)
	{
		if (j->fct(j->dev))
			ardumotics_job_del(j);
		ATOMIC_BLOCK(ATOMIC_FORCEON)
		{
			j = j->next;
		}
	}
}
