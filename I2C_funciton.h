#ifndef _I2C_FUNCTION_H
#define _I2C_FUNCTION_H
   
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "project.h"
   
bool I2C_ReadBytes(uint8_t slaveAddr, uint8_t registerNum, int dataLength, uint8_t *data);
bool I2C_WriteBytes(uint8_t slaveAddr, uint8_t registerNum, int dataLength, uint8_t *data);


#endif
