#ifndef _LB_IR
#define _LB_IR

#include <stdint.h>

/// @brief Initializes Port D (PD0..PD7) for use in the 8-bit IR
//         sensor
void init_sensors();

/// @brief Reads the state of Port D
/// @return State of the IR sensors from Port D
uint8_t read_sensors();

/// @brief Reads the IR sensor state at Port D
/// @return State of IR sensors, pre-masked
uint8_t read_sensors_masked();

/// @brief Set the bit mask width used by the algorithm to
///        determine error
/// @param width Width of the mask. Uneven numbers are
///              silently rejected
void set_width(uint8_t width);

/// @brief Directly sets the mask instead of computing.
///        exposed to let consumers load a value from
///        EEPROM or some other source
/// @param mask Mask to set. Evenness is not checked
void set_mask(uint8_t mask);

/// @brief Gets the mask set internally.
/// @return Mask set. Evenness is not guaranteed!
uint8_t get_mask();
#endif