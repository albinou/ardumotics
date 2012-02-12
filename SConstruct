MCU             = "atmega328p"
F_CPU           = "16000000"
ARDUINO_PORT    = "/dev/ttyACM0"

OBJCOPY         = "avr-objcopy"
OBJDUMP         = "avr-objdump"
SIZE            = "avr-size"
NM              = "avr-nm"

AVRDUDE         = "avrdude"
AVRDUDE_OPTS    = "-D -p %s -c arduino -P %s" % (MCU, ARDUINO_PORT)
STTY            = "stty"

env = DefaultEnvironment(CC="avr-gcc",
                         CXX="avr-g++",
                         AS="avr-as",
                         AR="avr-ar",
                         CCFLAGS="-mmcu=%s -DF_CPU=%s -Os -Wall -std=gnu99 \
-ffunction-sections -fdata-sections" % (MCU, F_CPU),
                         LINKFLAGS="-mmcu=%s -Wl,--gc-sections"  % (MCU))

elf_to_hex = Builder(action="%s -O ihex -R .eeprom $SOURCE $TARGET" % (OBJCOPY),
                     suffix=".hex",
                     src_suffix=".elf")
env.Append(BUILDERS={"ElfToHex" : elf_to_hex})

Help("""
Usage: 'scons'          build ardumotics
       'scons reset'    reset the Arduino board
       'scons upload'   upload ardumotics to the board
""")

ARDUMOTICS_SRCS  = ["ardumotics.c",
                    "ardumotics_mod.c",
                    "ardumotics_dev.c",
                    "ardumotics_sh.c",
                    "ardumotics_log.c",
                    "arduino_io.c",
                    "arduino_uart.c"]

ARDUMOTICS_MODULES = [("modules/temp", "ardumotics_temp", ["ardumotics_temp.c"])]

ardumotics_inc = ["."]
for m in ARDUMOTICS_MODULES:
    ardumotics_inc.append(m[0])

ardumotics_objs = []
for c in ARDUMOTICS_SRCS:
    ardumotics_objs.append(env.Object(c, CPPPATH=ardumotics_inc))

ardumotics_libs = []
for m in ARDUMOTICS_MODULES:
    ardumotics_libs.append(env.StaticLibrary("%s/%s" % (m[0], m[1]),
                                             ["%s/%s" % (m[0], c) for c in m[2]],
                                             CPPPATH=ardumotics_inc))

ardumotics_elf = env.Program("ardumotics", ardumotics_objs, LIBS=ardumotics_libs)
ardumotics_hex = env.ElfToHex("ardumotics.hex", ardumotics_elf)
Default(ardumotics_hex)

# Reset target:
env.Command("reset", None, "%s --file=%s hupcl" % (STTY, ARDUINO_PORT))

# Upload target:
env.Command("upload", ardumotics_hex,
            "%s %s -U flash:w:$SOURCE:i" % (AVRDUDE, AVRDUDE_OPTS))

# Size target:
env.Command("size", ardumotics_elf, "%s $SOURCE" % (SIZE))
