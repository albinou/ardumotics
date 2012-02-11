# The build system uses scons

all: ardumotics

ardumotics:
	@scons

reset:
	@scons reset

upload:
	@scons upload

size:
	@scons size

clean:
	@scons -c

.PHONY: all ardumotics reset upload clean
