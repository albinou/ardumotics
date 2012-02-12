#include <stdlib.h>

#include "ardumotics_mod.h"
#include "ardumotics_dev.h"
#include "ardumotics_log.h"
#include "arduino_io.h"

#include "ardumotics_led.h"

static int ardumotics_led_init(struct ardumotics_dev *dev);
static int ardumotics_led_on(struct ardumotics_dev *dev, const char **args);
static int ardumotics_led_off(struct ardumotics_dev *dev, const char **args);

static const struct ardumotics_mod_cmd ardumotics_led_cmd[] = {
	{ "on", ardumotics_led_on },
	{ "off", ardumotics_led_off },
	{ NULL, NULL },
};

static struct ardumotics_mod mod_led =
	{
		.name =             "led",
		.io_list_sz =       1,
		.private_data_sz =  0,

		.init_dev =         ardumotics_led_init,
		.cmd =              ardumotics_led_cmd,
	};


void ardumotics_led_register(void)
{
	int err;

	if ((err = ardumotics_mod_register(&mod_led)))
		ardumotics_log_mod_err(&mod_led, err, "cannot register the module");
}

static int ardumotics_led_init(struct ardumotics_dev *dev)
{
	ARDUINO_PIN_MODE(dev->io_list[0], OUTPUT);
	ARDUINO_OUTD(dev->io_list[0], LOW);
	return 0;
}

static int ardumotics_led_on(struct ardumotics_dev *dev, const char **args)
{
	ARDUINO_OUTD(dev->io_list[0], HIGH);
	return 0;
}

static int ardumotics_led_off(struct ardumotics_dev *dev, const char **args)
{
	ARDUINO_OUTD(dev->io_list[0], LOW);
	return 0;
}
