CC = avr-gcc
CFLAGS ?= -Os -Wall -Werror -mmcu=atmega328p
BUILDDIR ?= build
TARGET = linbot
AVRDUDE_ARGS ?= -c usbasp
ALL_MOD = main sketch m328p

ALL_OBJ = $(patsubst %,$(BUILDDIR)/%.o,$(ALL_MOD))

$(BUILDDIR)/$(TARGET).hex: $(BUILDDIR)/$(TARGET)
	avr-objcopy -j .text -j .data -S -O ihex $< $@

$(BUILDDIR)/$(TARGET): $(ALL_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILDDIR)/%.o: src/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c -o $@ $^

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

.PHONY: clean
clean:
	@rm -rf $(BUILDDIR)

flash: $(BUILDDIR)/$(TARGET).hex
	avrdude -p m328p $(AVRDUDE_ARGS) -U flash:w:$<:i