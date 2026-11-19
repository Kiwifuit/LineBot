CC = avr-gcc
MCU ?= atmega328p
CFLAGS ?= -Os -Wall -Werror -mmcu=$(MCU) -DF_CPU=8000000000L
BUILDDIR ?= build
TARGET = linbot

AVRDUDE_ARGS ?= -c usbasp
ALL_MOD = main

PROGRAMMER ?= usbasp
FLASHER_ARGS = -c $(PROGRAMMER) -p $(MCU) $(FLASHER_EXTRA)
FLASHER = avrdude $(FLASHER_ARGS)

ALL_OBJ = $(patsubst %,$(BUILDDIR)/%.o,$(ALL_MOD))

$(BUILDDIR)/$(TARGET).elf: $(ALL_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILDDIR)/%.o: src/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c -o $@ $^

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

.PHONY: clean flash fuses erase
clean:
	@rm -rf $(BUILDDIR)

flash: $(BUILDDIR)/$(TARGET).elf
	$(FLASHER) -U flash:w:$<:e

fuses: $(BUILDDIR)/$(TARGET).elf
	$(FLASHER) -U lfuse:w:$<:e -U hfuse:w:$<:e -U efuse:w:$<:e

erase:
	$(FLASHER) -e