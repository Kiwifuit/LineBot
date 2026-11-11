#include "m328p.h"

#include <avr/io.h>

#define BYTE_LOW 0x0F
#define BYTE_HIGH 0xF0

#define F_CPU 16000000L
#define FREQ(F_PWM) ((F_CPU) / (2 * PRESCALER * F_PWM))

static uint16_t PRESCALER = 1;

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

  // Waveform: Phase-correct PWM with OCR2A as TOP
  // Output: Set OC2B high on match during up-counting, clear on match during down-counting
  TCCR2A |= (1 << WGM20) | (1 << COM2B0) | (1 << COM2B1);
  TCCR2B |= (1 << WGM22);
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

void set_motor_clk_prescaler(uint16_t prescaler)
{
  uint8_t old_value = TCCR2B & 0b111;
  TCCR2B &= ~(0b111);

  switch (prescaler)
  {
  case 1:
    TCCR2B |= (1 << CS20);
    PRESCALER = 1;
    break;

  case 8:
    TCCR2B |= (1 << CS21);
    PRESCALER = 8;
    break;

  case 32:
    TCCR2B |= (1 << CS21) | (1 << CS20);
    PRESCALER = 32;
    break;

  case 64:
    TCCR2B |= (1 << CS22);
    PRESCALER = 64;
    break;

  case 128:
    TCCR2B |= (1 << CS22) | (1 << CS20);
    PRESCALER = 128;
    break;

  case 256:
    TCCR2B |= (1 << CS22) | (1 << CS21);
    PRESCALER = 256;
    break;

  case 1024:
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
    PRESCALER = 1024;
    break;

  default:
    TCCR2B |= old_value;
    break;
  }
}

void set_motor_speed(uint8_t speed)
{
  OCR2B = speed;
}

void set_motor_frequency(uint16_t frequency)
{
  OCR2A = FREQ(frequency);
}