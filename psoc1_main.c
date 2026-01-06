#include "FreeRTOS_PSoC.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "I2C_function.h"
#include "ds3231.h"

#define TASK_STACK_SIZE         (1024)
#define TASK_DATETIME_PRIORITY  (tskIDLE_PRIORITY + 2)

SemaphoreHandle_t xMutex_I2C;
void vTask_DateTime(void *parameters);


void MyPsoCSetup()
{
    
    I2C_Start();
    LCD_Start();
    LCD_ClearDisplay();
    LCD_PrintString("FreeRTOS RTC PSoC1");
    UART_Start();
    UART_ClearRxBuffer();
    UART_ClearTxBuffer();
    UART_PutString("\n\nPSoC1 FreeRTOS UART..\n\n");
    CyDelay(2000);
}

int main(void)
{
    BaseType_t err;

    FreeRTOS_Init();
    MyPsoCSetup();

    // Create MUTEX
    xMutex_I2C = xSemaphoreCreateMutex();
    if (xMutex_I2C == NULL) {
        LCD_Position(0,0);
        LCD_PrintString("MUTEX Err.");
        while(1);
    }

    // Create DateTime Task
    err = xTaskCreate(
        vTask_DateTime,
        "DateTime Task",
        TASK_STACK_SIZE,
        NULL,
        TASK_DATETIME_PRIORITY,
        NULL
    );
    

    vTaskStartScheduler();
    for(;;) {}
}



void vTask_DateTime(void *parameters)
{
    uint8_t buf[7];
    uint8_t ss, mm, hh, day, DD, MM, YYYY;
    bool isPm;
    char *weekDay[] = {"SU", "MO", "TU", "WE", "TH", "FR", "SA"};
    char str[50];
    bool status;

    // Check DS3231 Control Reg
    while(xSemaphoreTake(xMutex_I2C, portMAX_DELAY) != pdPASS);
    status = I2C_ReadBytes(DS3231_SLAVE_ADDR, DS3231_REG_CONTROL, 1, buf);
    xSemaphoreGive(xMutex_I2C);

    if (status) {
        buf[0] &= ~DS3231_BIT_CTRL_EOSC; // Enable oscillator
        while(xSemaphoreTake(xMutex_I2C, portMAX_DELAY) != pdPASS);
        I2C_WriteBytes(DS3231_SLAVE_ADDR, DS3231_REG_CONTROL, 1, buf);
        xSemaphoreGive(xMutex_I2C);
    }

    while(1)
    {
        while(xSemaphoreTake(xMutex_I2C, portMAX_DELAY) != pdPASS);
        status = I2C_ReadBytes(DS3231_SLAVE_ADDR, DS3231_REG_SECONDS, 7, buf);
        xSemaphoreGive(xMutex_I2C);

        if (status) {
            ss = BCD2DEC(buf[0]);
            mm = BCD2DEC(buf[1]);

            if (buf[2] & DS3231_BIT_12HRFORMAT) {
                // 12-hour format
                isPm = buf[2] & DS3231_BIT_PM;
                hh = BCD2DEC(buf[2] & 0x1F);
            } else {
                hh = BCD2DEC(buf[2] & 0x3F);
                isPm = false;
            }

            uint16_t  motorSpeed;

            // Determine motor speed based on seconds
            if (ss <= 10) motorSpeed = 1500;       //30% duty cyle
            else if (ss <= 30) motorSpeed = 3000;   //60% duty cycle
            else motorSpeed = 4998;         //100% duty cycle
            
            
            

            // Send motor speed via UART to PSoC 2
            char uartCmd[20];
            sprintf(uartCmd, "#SPEED:%d;", motorSpeed);
            UART_PutString(uartCmd);
            UART_PutString("\n");

            
            day = buf[3];
            DD = BCD2DEC(buf[4]);
            MM = BCD2DEC(buf[5]);
            YYYY = BCD2DEC(buf[6]);

            sprintf(str, "%02d:%02d:%02d %s", hh, mm, ss, isPm ? "PM" : "AM");
            LCD_Position(0, 0);
            LCD_PrintString(str);

            sprintf(str, "%04d/%02d/%02d %s", YYYY+2000, MM, DD, weekDay[day-1]);
            LCD_Position(1, 0);
            LCD_PrintString(str);
        }
        
        vTaskDelay(pdMS_TO_TICKS(1000)); // update every 1 second
    }
}
