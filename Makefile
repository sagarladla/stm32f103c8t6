CC=arm-none-eabi-gcc
MARCH=cortex-m3
CFLAGS= -c -mcpu=$(MARCH) -mthumb -std=gnu17 -Wall -O0
LDFLAGS= -nostdlib -T linker_script.ld -Wl,-Map=final.map

all: main.o startup.o final.elf

main.o: main.c
	$(CC) $(CFLAGS) $^ -o $@

startup.o: startup.c
	$(CC) $(CFLAGS) $^ -o $@

final.elf: main.o startup.o
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm -rf *.o *.elf *map *.out
