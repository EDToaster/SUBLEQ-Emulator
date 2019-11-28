
all: emulator

emulator: emulator.c
	gcc -Wall -Wextra -o emulator emulator.c
