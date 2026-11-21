#ifndef _LB_PID
#define _LB_PID

#include <stdint.h>

/// @brief PID Controller State
typedef struct
{
  int32_t integral;
  int8_t pid_prev_err;
  int8_t sensor_last_err;
} pid_state_t;

/// @brief Initializes a PID controller gains
/// @param Uninitialized state
void init_pid(pid_state_t *pid_state);

int8_t compute_ir_error(uint8_t ir_sensor, pid_state_t *pid_state);

int16_t update_pid(pid_state_t *pid_state, const lb_state_t *gains, int8_t error);

#endif