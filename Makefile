####################################################################################################
# 
# @file: Makefile
# @author: Sagarrajvarman Ladla
# @date: 2025-08-03
# @brief: This file contains the build instructions for the stm32f103c8t6 project
# @version: 1.0
# @license: MIT License
# @note: This project is developed using the C23 language standard version.
#
####################################################################################################

PROJECT = main

# Source files
INCLUDES          =  -Iinc
SRC_DIR           =  src
SRCS              :=  $(wildcard $(SRC_DIR)/*.c)
BUILD_DIR         =  build
RELEASE_DIR       =  release
OBJS              := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
SCRIPTS           = scripts

# Ensure the build directory exists
$(shell mkdir -p $(BUILD_DIR)/$(RELEASE_DIR))
# Define the target executable
TARGET            = $(BUILD_DIR)/$(RELEASE_DIR)/$(PROJECT)

# Microcontroller settings
MCU               = cortex-m3

# Compiler settings
toolchain         = arm-none-eabi-
CC                = $(toolchain)gcc
CSTD              = c2x

CFLAGS            = -mcpu=$(MCU) -mthumb -std=$(CSTD) \
                    -Wall -Wextra -Werror -g -O3 \
                    -fno-common -fno-builtin -ffreestanding \
                    -nostdlib -nostartfiles -Wno-unused-parameter -v ${INCLUDES}

LDSCRIPT          = $(SCRIPTS)/stm32f103.ld
LDFLAGS           = -T$(LDSCRIPT) -mthumb -nostdinc -nolibc \
                    -nostartfiles --specs=nosys.specs --specs=nano.specs \
                    -Wl,--gc-sections -Wl,-Map=$(TARGET).map --verbose
OBJCOPY           = $(toolchain)objcopy

default: all

# Default target
all: $(TARGET).elf $(TARGET).bin $(TARGET).hex

# Build rules
$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

flash:
	openocd -f $(SCRIPTS)/openocd.cfg -c "program $(TARGET).elf verify reset exit"

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR)

# PHONY commands
.PHONY: all clean flash