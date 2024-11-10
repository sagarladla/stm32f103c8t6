toolchain	:=arm-none-eabi
cpu		:=cortex-m3
std		:=gnu17
CC		:=$(toolchain)-gcc
CFLAGS		:=-mcpu=$(cpu) -mthumb -std=$(std) -Wall -Wextra -Werror -g -O0 -fno-common -fno-builtin -Iincludes
LDFLAGS		:=-mthumb -nostdinc -nolibc -nostartfiles --specs=nosys.specs --specs=nano.specs -T stm32f103.ld -Wl,-Map=main.map,--verbose

main.elf: main.o startup_stm32f103.o
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

flash:
	openocd -f openocd.cfg -c "program main.elf verify reset exit"
clean:
	rm -rf *.o *.elf *.map *.out *.gch
