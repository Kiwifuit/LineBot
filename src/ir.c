// IR Array is assigned to Port D, so
// PD0 through PD7 are expected to be inputs

#include "ir.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

// TODO: Move these to a global configuration struct
static uint8_t MASK = 0;

void init_sensors()
{
  // Ensure all pins on Port D are inputs
  DDRD = 0;
}

uint8_t read_sensors()
{
  return PIND;
}

uint8_t read_sensors_masked()
{
  // NOTE: Functions in C have to be
  // defined first before used. This
  // is legal since `ir.h` defines a
  // prototype of `get_mask`
  return PIND & get_mask();
}

void set_width(uint8_t width)
{
  // `cli` and `sei` are AVR C functions
  // that enable and disable interrupts.
  //
  // Since we are modifying a static global,
  // we cant have an interrupt executing
  // while we are updating the bitmask
  //
  // This makes our code "atomic", meaning
  // MASK is accessed by either the application
  // or an interrupt routine, but not both
  // at the same time
  cli();
  if (width % 2)
    return;

  // Creates a centered mask
  MASK = (uint8_t)(((2 << width) - 1) << (8 - width) >> 1); // (2^width - 1) << [(8 - width)/2]

  // Re-enable interrupts here
  sei();
}

void set_mask(uint8_t mask)
{
  cli();
  MASK = mask;
  sei();
}

uint8_t get_mask()
{
  uint8_t mask = 0;

  cli();
  // Make region here critical to uphold the
  // atomic invariant: that "MASK is to be accessed
  // by either the application or an ISR, but not
  // both at the same time"
  mask = MASK;
  sei();

  return mask;
}