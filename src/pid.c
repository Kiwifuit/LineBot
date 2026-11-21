// PID controller

#include "pid.h"

#include <stdint.h>

#define PID_SHIFT 4      // divide final result by 16
#define INTEGRAL_MAX 500 // anti-windup limit

static const int8_t WEIGHTS[8] = {-7, -5, -3, -1, 1, 3, 5, 7};
static int16_t last_err = 0;

struct pid_t
{
  // TODO: Move these to a global configuration struct
  int16_t kp;
  int16_t ki;
  int16_t kd;
  int32_t integral;
  int8_t last_err;
};

int8_t compute_ir_error(uint8_t ir_sensor)
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
    last_err = (int8_t)(sum / count);
  }

  return last_err;
}

int16_t update_pid(struct pid_t *pid_state, int8_t error)
{
  int32_t p = pid_state->kp * error;

  // Accumulate error over time
  pid_state->integral += error;
  // Clamp integral value to between INTEGRAL_MAX and -INTEGRAL_MAX
  if (pid_state->integral > INTEGRAL_MAX)
    pid_state->integral = INTEGRAL_MAX;
  if (pid_state->integral < -INTEGRAL_MAX)
    pid_state->integral = -INTEGRAL_MAX;

  int32_t i = pid_state->ki * pid_state->integral;

  int32_t d = pid_state->kd * (error - pid_state->last_err);
  pid_state->last_err = error;

  int32_t u = (p + i + d) >> PID_SHIFT;
  return (int16_t)u;
}