/*
 * Timer module
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
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <errno.h>

#include "ardumotics_dev.h"
#include "ardumotics_job.h"
#include "ardumotics_log.h"
#include "ardumotics_errno.h"

#include "ardumotics_timer.h"

static int ardumotics_timer_init(struct ardumotics_dev *dev);
static int ardumotics_timer_clean(struct ardumotics_dev *dev);
static int ardumotics_timer_job(struct ardumotics_dev *dev);
static int ardumotics_timer_help(struct ardumotics_dev *dev, const char **args);
static int ardumotics_timer_get(struct ardumotics_dev *dev, const char **args);
static int ardumotics_timer_add(struct ardumotics_dev *dev, const char **args);
static int ardumotics_timer_del(struct ardumotics_dev *dev, const char **args);


static const struct ardumotics_mod_cmd ardumotics_timer_cmd[] =
	{
		{ "help", ardumotics_timer_help },
		{ "get", ardumotics_timer_get },
		{ "add", ardumotics_timer_add },
		{ "del", ardumotics_timer_del },
		{ NULL, NULL },
	};

struct ardumotics_timer_elt {
	uint16_t              period;
	struct ardumotics_dev *dev;
	char                  **args;
	t_cmd_handler         callback;

	struct ardumotics_timer_elt *next;
};

struct ardumotics_timer {
	uint16_t msec;
	struct ardumotics_timer_elt *head;
};

static struct ardumotics_mod mod_timer =
	{
		.name =             "timer",
		.io_list_sz =       0,
		.private_data_sz =  sizeof (struct ardumotics_timer),

		.init_dev =         ardumotics_timer_init,
		.clean_dev =        ardumotics_timer_clean,
		.cmd =              ardumotics_timer_cmd,
	};

static struct ardumotics_timer *timer = NULL;

static struct ardumotics_job job =
	{
		.fct = ardumotics_timer_job,
		.dev = NULL,

		.next = NULL,
	};


ISR(TIMER0_COMPA_vect) {
}

ISR(TIMER0_COMPB_vect) {
}

ISR(TIMER0_OVF_vect) {
	timer->msec += 16;    // = 0x100 * 1024 * 1000 / F_CPU
	ardumotics_job_add(&job);
}

static int ardumotics_timer_init(struct ardumotics_dev *dev)
{
	if (timer)
		return EBUSY;

	timer = dev->private_data;
	timer->msec = 0;
	timer->head = NULL;
	job.dev = dev;

	TCCR0A = 0;
	TCCR0B = 0;
	TIMSK0 = (0 << OCIE0A) | (0 << OCIE0B) | (1 << TOIE0);
	TCCR0B = (1 << CS12) | (0 << CS11) | (1 << CS10);
	sei();
	return 0;
}

static int ardumotics_timer_clean(struct ardumotics_dev *dev)
{
	TIMSK0 = 0;
	timer = NULL;
	return 0;
}

static int ardumotics_timer_job(struct ardumotics_dev *dev)
{
	struct ardumotics_timer_elt *elt;

	for (elt = timer->head; elt != NULL; elt = elt->next)
		if ((timer->msec % elt->period) == 0)
			elt->callback(elt->dev, elt->args);
	return 1;
}

static int ardumotics_timer_help(struct ardumotics_dev *dev, const char **args)
{
	puts_P(PSTR("usage: add <dd> <cmd> <period>"));
	puts_P(PSTR("       del <dd> <cmd> <period>"));
	puts_P(PSTR("       get"));
	return 0;
}

static int ardumotics_timer_get(struct ardumotics_dev *dev, const char **args)
{
	printf_P(PSTR("timer = %u ms\n"), timer->msec);
	return 0;
}

static int ardumotics_timer_add(struct ardumotics_dev *dev, const char **args)
{
	struct ardumotics_timer_elt *elt;
	struct ardumotics_dev *dd_dev;
	t_cmd_handler fct;
	char *endstr;
	int dd;
	int period;

	if (ardumotics_mod_nbargs(args) != 3)
		return -EINVAL;

	dd = strtol(args[0], &endstr, 10);
	if (errno || (*endstr != '\0') || (dd < 0) || (dd > UINT8_MAX) ||
	    ((dd_dev = ardumotics_dev_find (dd)) == NULL))
		return -EINVAL;
	if ((fct = ardumotics_dev_get_fct(dd_dev, args[1])) == NULL)
		return -EINVAL;
	period = strtol(args[2], &endstr, 10);
	if (errno || (*endstr != '\0') || (period < 0) || (period > UINT16_MAX))
		return -EINVAL;

	if ((elt = malloc(sizeof (struct ardumotics_timer_elt))) == NULL)
		return -ENOMEM;

	period -= period % 16;

	elt->period = period;
	elt->dev = dd_dev;
	elt->args = NULL; // FIXME
	elt->callback = fct;
	elt->next = timer->head;
	timer->head = elt;

	return 0;
}

static int ardumotics_timer_del(struct ardumotics_dev *dev, const char **args)
{
	return 0;
}

ARDUMOTICS_MOD_INIT (timer, &mod_timer)
