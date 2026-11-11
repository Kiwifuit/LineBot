#include "m328p.h"

#include <avr/io.h>

#define BYTE_LOW 0x0F
#define BYTE_HIGH 0xF0

void init()
{
  // High byte of IR sensor
  DDRB &= ~BYTE_LOW; // ANDs the inverse of the first 4 pins, ensuring they are inputs

  // Low byte of IR sensor
  DDRD &= ~BYTE_HIGH;

  // Motor driver STDBY signal
  DDRB |= (1 << PB4);

  // Motor driver control pins
  DDRC |= BYTE_LOW;
}

uint8_t read_ir_sensors()
{
  // High nibble takes lower 4 pins of port B
  uint8_t high = PINB & BYTE_LOW;
  // Low nibble takes upper 4 pins of port D
  uint8_t low = PIND & BYTE_HIGH;

  return (high << 4) | (low >> 4);
}

void motor_forward()
{
  PORTC |= (1 << PC0) | (1 << PC2);
}

void motor_backward()
{
  PORTC |= (1 << PC1) | (1 << PC3);
}

void motor_left()
{
  PORTC |= (1 << PC0) | (1 << PC3);
}

void motor_right()
{
  PORTC |= (1 << PC1) | (1 << PC2);
}

void motor_stop()
{
  PORTC &= ~BYTE_LOW;
}
