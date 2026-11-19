# Line following bot Notes

## Building

### Requirements

* `avrdude`
* AVR toolchain `avr-gcc`, `avr-libc`, `avr-objcopy`, etc.
* GNU Make

To compile, run `make` to produce the ihex file of the program.
`make flash` uses AVRDude to flash to the target chip using a USBASP
device.

On Windows systems using MSYS2, `mingw32-make` is used over `make`.

### Programming without an usbasp

Override the `AVRDUDE_ARGS` variable to include `-c arduino`. Below is an
example for programming on windows

```sh
mingw32-make flash AVRDUDE_ARGS="-c arduino -P ch340"
```

## Pin assignments

| Module | Function | Pin (m328p) | Physical Pin# (m328p) |
| ------ | -------- | ----------- | ------------- |
| Motor Driver | PWM | PB1 | 15 |
| Motor Driver | Direction | PC[0..3] | 23 to 26 |
| Motor Driver | Standby | PC4 | 27 |
| IR Array | Array Input | PD[0..7] | 2 to 6, 11 to 13 |

## Microcontroller Pinout

![Atmega328p](./doc/atmega328p-pinout.gif)

## Customization

The project primarily targets the ATMega328P, commonly found in
the Arduino Nano and Uno. This, alongside other options, can be
modified upon invoking `make` or `mingw32-make`:

* `MCU`: The microcontroller to reference. `avr-gcc` and `avrdude`
  use this option. Modify this option on different microcontrollers other than recommended
* `PROGRAMMER`: The use of a USBasp is recommended, but other
  programmers can be used through this variable
* `FLASHER_EXTRA`: Extra arguments to pass to `avrdude`

Note that the clock speed which this firmware may use is
hardcoded to 8 MHz, and the fuse bytes are hardcoded to
reflect the use of the internal 8 MHz RC Oscillator.
This can be changed by modifying `Makefile` and `main.c`
directly

Other recipes such as `fuses` and `erase` may not work on other
programmers.
