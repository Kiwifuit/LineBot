#pragma once

#include <stdint.h>

/// @brief Initializes the mcu
void init();

/// @brief Reads the IR sensors and returns their states
/// @return State of the 8-channel IR sensor
uint8_t read_ir_sensors();

/// @brief Moves both motors forward
void motor_forward();

/// @brief Moves both motors backward
void motor_backward();

/// @brief Moves the left motor forward and right motor backward, turning left
void motor_left();

/// @brief Moves the right motor forward and left motor backward, turning right
void motor_right();

/// @brief Stops both motors
void motor_stop();