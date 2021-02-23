/**
  ******************************************************************************
  * File Name          : delay.c
  * Description        : This file provides functions about delay.
  ******************************************************************************
  * @attention
  * 
  *
  ******************************************************************************
  */


#include "delay.h"

/*****************************************************************************
 Function    : delay_us
 Description : Delay time*（0.97）us.
 Input       : time
 Output      : None
 Return      : None
 *****************************************************************************/
void delay_us(uint32_t time)
{    
    uint16_t i = 0;  
    while(time--)
    {
        i = 11;  //自己定义
        while(i--) ;    
    }
}
/*****************************************************************************
 Function    : delay_ms
 Description : Delay time*（0.97）us*1000.
 Input       : time
 Output      : None
 Return      : None
 *****************************************************************************/
void delay_ms(uint32_t time)
{    
    uint32_t i = 0;  
    while(time--)
    {
        i = 11000;  //自己定义
        while(i--) ;    
    }
}

/************************ZXDQ *****END OF FILE****/

