#ifndef _DS3231_H
#define _DS3231_H
   
#define DS3231_SLAVE_ADDR       0x68    

#define DS3231_REG_SECONDS      0x00
#define DS3231_REG_MINUTES      0x01
#define DS3231_REG_HOURS        0x02
#define DS3231_REG_DAY          0x03
#define DS3231_REG_DATE         0x04
#define DS3231_REG_MONTH        0x05
#define DS3231_REG_YEAR         0x06
#define DS3231_REG_CONTROL      0x0E
#define DS3231_REG_STATUS       0x0F

#define DS3231_BIT_12HRFORMAT   0x40
#define DS3231_BIT_24HRFORMAT   0x00
#define DS3231_BIT_AM           0x00
#define DS3231_BIT_PM           0x20
#define DS3231_BIT_CTRL_EOSC    0x80    
#define DS3231_BIT_STAT_OSF     0x80    

#define DS3231_DAY_SUN          0x01
#define DS3231_DAY_MON          0x02
#define DS3231_DAY_TUE          0x03
#define DS3231_DAY_WED          0x04
#define DS3231_DAY_THR          0x05
#define DS3231_DAY_FRI          0x06
#define DS3231_DAY_SAT          0x07


#define DEC2BCD(dec) ( (uint8_t)((((dec) / 10U) << 4) | ((dec) % 10U)) )
#define BCD2DEC(bcd) ( (uint8_t)((((bcd) >> 4) * 10U) + ((bcd) & 0x0FU)))    
   
#endif
