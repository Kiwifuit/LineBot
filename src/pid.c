// PID controller

#include "pid.h"
#include "state.h"

#include <stdint.h>

#define PID_SHIFT 4      // divide final result by 16
#define INTEGRAL_MAX 500 // anti-windup limit

static const int8_t WEIGHTS[8] = {-7, -5, -3, -1, 1, 3, 5, 7};

void init_pid(pid_state_t *pid_state)
{
  pid_state->integral = 0;
  pid_state->pid_prev_err = 0;
  pid_state->sensor_last_err = 0;
}

int8_t compute_ir_error(uint8_t ir_sensor, pid_state_t *pid_state)
{
  int16_t sum = 0;
  uint8_t count = 0;

  for (int i = 0; i < sizeof(WEIGHTS); i++)
  {
    if (ir_sensor & (1 << i))
    {
      sum += WEIGHTS[(sizeof(WEIGHTS) - 1) - i];
      count++;
    }
  }

  if (count != 0)
  {
    pid_state->sensor_last_err = (int8_t)(sum / count);
  }

  return pid_state->sensor_last_err;
}

int16_t update_pid(pid_state_t *pid_state, const lb_state_t *gains, int8_t error)
{
  int32_t p = gains->kp * error;

  // Accumulate error over time
  pid_state->integral += error;
  // Clamp integral value to between INTEGRAL_MAX and -INTEGRAL_MAX
  if (pid_state->integral > INTEGRAL_MAX)
    pid_state->integral = INTEGRAL_MAX;
  if (pid_state->integral < -INTEGRAL_MAX)
    pid_state->integral = -INTEGRAL_MAX;

  int32_t i = gains->ki * pid_state->integral;

  int32_t d = gains->kd * (error - pid_state->pid_prev_err);
  pid_state->pid_prev_err = error;

  int32_t u = (p + i + d) >> PID_SHIFT;
  return (int16_t)u;
}