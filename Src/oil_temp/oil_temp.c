/**
  ******************************************************************************
  * File Name          : oil_temp.c
  * Description        : This file contains all functions about related to oil 
                         temperature measurement.
  ******************************************************************************
  * @attention
  * 
  *
  ******************************************************************************
  */

#include "oil_temp.h"
#include "delay.h"

/*****************************************************************************
 Function    : DS18B20_Reset
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
static uint8_t DS18B20_Reset(void)                                        
{
    uint8_t i;                                                   
    DATA_WIRE_LOW;                                             
    delay_us(500);                                     //延时500uS(480-960)
    DATA_WIRE_HIGH;  
    delay_us(80);                 
    i = DATA_WIRE_STATUS;
    delay_us(500);                                    //延时500uS(保持>480uS)
      
    if (i) 
    {
        return 0x00;
    }
    else 
    {
        return 0x01;
    }
}
/*****************************************************************************
 Function    : DS18B20_Write_Byte
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
static void DS18B20_Write_Byte(uint8_t value) 
{
    uint8_t i;
    for (i = 8; i != 0; i--) 
    {
                                                            // DQ_OUT;S设置为输出
        DATA_WIRE_LOW;                                      //DQ_CLR;置低电平
        delay_us(15) ;                                      //延时15uS
        if (value & 0x01) 
        {
            DATA_WIRE_HIGH;                                 //DQ_SET;置高电平        
        }
        delay_us(60);                                       //延时80uS
        DATA_WIRE_HIGH;                                     //DQ_SET置高电平              
        value >>= 1;    
    }
}
/*****************************************************************************
 Function    : DS18B20_Read_Byte
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
static uint8_t DS18B20_Read_Byte(void) 
{
    uint8_t i;
    uint8_t value = 0;
    for (i = 8; i != 0; i--) 
    {
        value >>= 1;
                                                             // DQ_OUT;
        DATA_WIRE_LOW;                                       // DQ_CLR;置低电平
        delay_us(2);                                         //*延时4uS  
        DATA_WIRE_HIGH;                                      // DQ_SET;置高电平
                                                             //DQ_IN;设置为输入模式
        delay_us(1);                                         //*延时10uS 
        if (DATA_WIRE_STATUS)
        {
            value |= 0x80;      
        }
        delay_us(70);                                        //*延时60uS    
    }
    return(value);
}
/*****************************************************************************
 Function    : DS18B20_Start
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
static uint8_t DS18B20_Start(void) 
{
    uint8_t errorNum = 0;
    while(DS18B20_Reset() == 0)
    {
        errorNum++;
        if(errorNum > 3)
            return 1;
    }
    DS18B20_Write_Byte(0xCC);           //勿略地址
    DS18B20_Write_Byte(0x44);           //启动转换
    return 0;
}

/*****************************************************************************
 Function    : Temp_Convert_Start
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
TmpStatusTypeDef Temp_Convert_Start(void)
{
    if(DS18B20_Start() != 0)
        return TMP_ERROR;
    return TMP_OK;
}
/*****************************************************************************
 Function    : Temp_Read
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
TmpStatusTypeDef Temp_Read(float *tmp)
{
    short   i = 0;
    uint8_t errorNum = 0;
    uint8_t buf[9];
    while(DS18B20_Reset() == 0)
    {
        errorNum++;
        if(errorNum > 3)
            return TMP_ERROR;
    }
    DS18B20_Write_Byte(0xCC);           //勿略地址
    DS18B20_Write_Byte(0xBE);           //读取温度
    buf[0] = DS18B20_Read_Byte();
    buf[1] = DS18B20_Read_Byte(); 
    while(DS18B20_Reset() == 0)
    {
        errorNum++;
        if(errorNum > 3)
            return TMP_ERROR;
    }   
    i = (buf[1] << 8) + buf[0];
    if(i < 0)
        *tmp = (~i + 1) * 0.0625;
    else
        *tmp =  i * 0.0625;  
    if(*tmp < 125 && *tmp > (-55))            
        return TMP_OK;
    else
        return TMP_ERROR;
}

/************************ZXDQ *****END OF FILE****/

