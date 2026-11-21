// EEPROM-backed state tracking

#include "state.h"

#include <avr/eeprom.h>
#include <avr/interrupt.h>

static lb_state_t EEMEM default_state = {
    .ir_bitmask = 0xFF,
    .kp = 0,
    .ki = 0,
    .kd = 0};

static lb_state_t working_state;

const lb_state_t *load_state(void)
{
  cli();
  eeprom_read_block((void *)&working_state, (const void *)&default_state, sizeof(lb_state_t));
  sei();

  return (const lb_state_t *)&working_state;
}
