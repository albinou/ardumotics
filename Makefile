# The build system uses scons

all: ardumotics

ardumotics:
	@scons

reset:
	@scons reset

upload:
	@scons upload

clean:
	@scons -c

.PHONY: all ardumotics reset upload clean
