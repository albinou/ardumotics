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
