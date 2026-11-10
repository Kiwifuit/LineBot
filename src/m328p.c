#include "m328p.h"

#include <avr/io.h>

#define BYTE_LOW 0x0F
#define BYTE_HIGH 0xF0

void init()
{
  DDRB |= BYTE_LOW | (1 << PB4);
  DDRD |= BYTE_HIGH;
  DDRC |= (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3);
}

uint8_t read_ir_sensors()
{
  return 0;
}

void motor_forward() {}

void motor_backward() {}

void motor_left() {}

void motor_right() {}

void motor_stop() {}
