#include "I2C_function.h"

#define _I2C_WRITE_MODE     0
#define _I2C_READ_MODE      1

bool I2C_ReadBytes(uint8_t slaveAddr, uint8_t registerNum, int dataLength, uint8_t *data)
{
    uint8_t     status;
    bool        noError = false;
    int         i;
   
   
    status = I2C_MasterSendStart(slaveAddr, _I2C_WRITE_MODE);
    if (status == I2C_MSTR_NO_ERROR){
        //Send registration
        status = I2C_MasterWriteByte(registerNum);
        if(status != I2C_MSTR_NO_ERROR)
            goto FINISHED;
         status = I2C_MasterSendRestart(slaveAddr, _I2C_READ_MODE);
         if(status != I2C_MSTR_NO_ERROR)
            goto FINISHED;
       
        for (i = 0; i < dataLength; i++){
            if( i< (dataLength -1))
                *data = I2C_MasterReadByte(I2C_ACK_DATA);
            else
                *data = I2C_MasterReadByte(I2C_NAK_DATA);
           
            data++;
        }  
        noError = true;
    }
FINISHED:
I2C_MasterSendStop();
   
   
    return noError;
}
//-------------------------------------------------------------------------------------------
bool I2C_WriteBytes(uint8_t slaveAddr, uint8_t registerNum, int dataLength, uint8_t *data)
{
    uint8_t status;
    bool    noError = false;
    int     i;
   
    status = I2C_MasterSendStart(slaveAddr, _I2C_WRITE_MODE);
    if (status == I2C_MSTR_NO_ERROR){
        //Send registerNum
        status = I2C_MasterWriteByte(registerNum);
        if(status != I2C_MSTR_NO_ERROR)
            goto FINISHED;
       
        for (i = 0; i<dataLength; i++){
            status = I2C_MasterWriteByte(*data);
            if(status != I2C_MSTR_NO_ERROR)
                goto FINISHED;
            data++;
        }
        noError = true;
    }
FINISHED:
       I2C_MasterSendStop();
       return noError;
}
