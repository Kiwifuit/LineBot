#include "sketch.h"

#include "m328p.h"

void setup()
{
  init();
  set_motor_clk_prescaler(8);
  set_motor_frequency(20000);
}

void loop()
{
  set_motor_speed(127);
  motor_forward();
}