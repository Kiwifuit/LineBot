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

/// @brief Sets the Motor PWM's prescaler value
/// @param prescaler Prescaler value to set
void set_motor_clk_prescaler(uint16_t prescaler);

/// @brief Sets the motor speed from 0 - 255
/// @param speed Motor speed
void set_motor_speed(uint8_t speed);

/// @brief Sets the Motor PWM's frequency
/// @param frequency Frequency in Hz
void set_motor_frequency(uint16_t frequency);
