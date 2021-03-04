/*
 * File:   vl53l0x.c
 * Author: Torben
 *
 * Created on February 2, 2021, 3:47 PM
 */


#include <xc.h>
#include <assert.h>
#include <stdbool.h>
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c_master_example.h"
#include "mcp79410.h"

#define MCP79410_ADDR               0x6F //0x57 
    
#define RTCC_SECONDS                0x00
#define RTCC_MINUTES                0x01
#define RTCC_HOUR                   0x02
#define RTCC_DAY                    0x03
#define RTCC_DATE                   0x04
#define RTCC_MONTH                  0x05
#define RTCC_YEAR                   0x06
#define CONTROL_REG                 0x07
#define CALIBRATION                 0x08

#define PWR_DOWN_MINUTES            0x18
#define PWR_DOWN_HOUR               0x19
#define PWR_DOWN_DATE               0x1A
#define PWR_DOWN_MONTH              0x1B
#define PWR_UP_MINUTES              0x1C
#define PWR_UP_HOUR                 0x1D
#define PWR_UP_DATE                 0x1E
#define PWR_UP_MONTH                0x1F

uint8_t Slave_Address;                                                          // definiert "Slave_Address" 
uint8_t writeBuffer[3];                                                         // definiert "writeBuffer"
uint8_t readBuffer;                                                             // definiert "readBuffer" 

void MCP79410_set_date_time(                                                    // "MCP79410_set_date_time"
                             uint8_t day,                                       // definiert "day"
                             uint8_t mouth,                                     // definiert "mouth"
                             uint8_t year,                                      // definiert "year"        
                             uint8_t hour,                                      // definiert "hour"
                             uint8_t min){                                      // definiert "min" 
    
    I2C_Write1ByteRegister(MCP79410_ADDR, RTCC_DAY, 0x08);                      // schreibt "0x08" in "RTCC_DAY"
    I2C_Write1ByteRegister(MCP79410_ADDR, RTCC_SECONDS, 0x80);                  // schreibt "0x80" in "RTCC_SECONDS"
    I2C_Write1ByteRegister(MCP79410_ADDR, RTCC_HOUR, 0x01);                     // schreibt "0x01" in "RTCC_HOUR"
    I2C_Write1ByteRegister(MCP79410_ADDR, CONTROL_REG, 0x40);                   // schreibt "0x40" in "CONTROL_REG"
    __delay_ms(1000);                                                           // warte 1000ms
    
    day = day & 0b00111111;                                                     // "day" maskieren mit "0b00111111"
    I2C_Write1ByteRegister(MCP79410_ADDR, RTCC_DATE, day);                      // schreibt "day" in "RTCC_DATE"
    
    mouth = mouth & 0b00111111;                                                 // "mouth" maskieren mit "0b00111111" 
    I2C_Write1ByteRegister(MCP79410_ADDR, RTCC_MONTH, mouth);                   // schreibt "mouth" in "RTCC_MONTH"
    
    year = year & 0b11111111;                                                   // "year" maskieren mit "0b11111111"
    I2C_Write1ByteRegister(MCP79410_ADDR, RTCC_YEAR, year);                     // schreibt "year" in "RTCC_YEAR"
    
    hour = hour & 0b01111111;                                                   // "hour" maskieren mit "0b01111111" 
    I2C_Write1ByteRegister(MCP79410_ADDR, RTCC_HOUR, hour);                     // schreibt "hour" in "RTCC_HOUR"
    
    min = min & 0b01111111;                                                     // "min" maskieren mit "0b01111111"
    I2C_Write1ByteRegister(MCP79410_ADDR, RTCC_MINUTES, min);                   // schreibt "min" in "RTCC_MINUTES"
}                                                                               // 

void MCP79410_get_date(                                                         // "MCP79410_get_date"
                        uint8_t *day,                                           // definiert "day"
                        uint8_t *mouth,                                         // definiert "mouth" 
                        uint8_t *year){                                         // definiert "year"

    *day = I2C_Read1ByteRegister(MCP79410_ADDR,RTCC_DATE);                      // "day" gleich I2C read (RTCC_DATE)
    *day = *day & 0b00111111;                                                   // maskiert "day" mit "0b00111111"

    *mouth = I2C_Read1ByteRegister(MCP79410_ADDR,RTCC_MONTH);                   // "mouth" gleich I2C read (RTCC_MONTH)
    *mouth = *mouth & 0b00011111;                                               // maskiert "mouth" mit "0b00011111"

    *year = I2C_Read1ByteRegister(MCP79410_ADDR,RTCC_YEAR);                     // "year" gleich I2C read (RTCC_YEAR)
}                                                                               // 

void MCP79410_get_time(                                                         // "MCP79410_get_time"
                        uint8_t *hour,                                          // definiert "hour"
                        uint8_t *min,                                           // definiert "min"
                        uint8_t *sec){                                          // definiert "sec"

    *sec = I2C_Read1ByteRegister(MCP79410_ADDR,RTCC_SECONDS);                   // "readBuffer" gleich I2C read (RTCC_SECONDS)
    *sec = *sec & 0b01111111;                                                   // maskiert "sec" mit "0b01111111"
    
    *min = I2C_Read1ByteRegister(MCP79410_ADDR,RTCC_MINUTES);                   // "readBuffer" gleich I2C read (RTCC_MINUTES)
    *min = *min & 0b01111111;                                                   // maskiert "min" mit "0b01111111"
    
    *hour = I2C_Read1ByteRegister(MCP79410_ADDR,RTCC_HOUR);                     // "readBuffer" gleich I2C read (RTCC_HOUR)
    *hour = *hour & 0b00111111;                                                 // maskiert "hour" mit "0b00111111"
}                                                                               //  
