#ifndef _EEPROM24CDEPENDENCIES_H_
#define _EEPROM24CDEPENDENCIES_H_
#include <inttypes.h>
#include <stdbool.h>

#ifdef _cplusplus
extern "C"
{
#endif // _cplusplus

/**
 * @brief Write to i2c memory
*/
extern bool _write_to_i2c_memory(uint16_t deviceAddres, uint16_t memoryAddress, uint8_t *buffer, uint16_t bufferSize);

/**
 * @brief Read from i2c memory
*/
extern bool _read_from_i2c_memory(uint16_t deviceAddres, uint16_t memoryAddress, uint8_t *buffer, uint16_t bufferSize);

#ifdef _cplusplus
}
#endif // _cplusplus

#endif // _EEPROM24CDEPENDENCIES_H_