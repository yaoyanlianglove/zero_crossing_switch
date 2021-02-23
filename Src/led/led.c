/**
  ******************************************************************************
  * File Name          : led.c
  * Description        : This file contains all functions about led.
  ******************************************************************************
  * @attention
  * 
  *
  ******************************************************************************
  */
#include "led.h"
#include "switch.h"

extern SwitchTypeDef sw;
/*****************************************************************************
 Function    : Task_Led
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void Task_Led(void)
{
    if(sw.lock == 1)
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
    else
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
}

/************************ZXDQ *****END OF FILE****/

