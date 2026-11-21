#ifndef _LB_STATE
#define _LB_STATE

#include <stdint.h>

typedef struct
{
  uint8_t ir_bitmask;
  int16_t kp;
  int16_t ki;
  int16_t kd;
} lb_state_t;

/// @brief Loads the configuration saved into EEPROM
/// @return Read-only access to the state
const lb_state_t *load_state(void);

#endif