/**
  ******************************************************************************
  * File Name          : task.c
  * Description        : This file provides code about task.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#include "task.h"
#include "tim.h"
#include "modbus.h"
#include "modbus_interface.h"
#include "switch.h"
#include "led.h"
#include "oil_temp.h"
#include "memory.h"
#include "iwdg.h"

uint32_t countOver = 0;    //频率计数器溢出次数
uint16_t freq = 0;
uint16_t msCount   = 0;
uint16_t uVF = 0;
extern SwitchTypeDef sw;

/***********油温相关开始************************************************************/
volatile  uint16_t readOilTmpSpace    = 0;       //读油温时间间隔
volatile  uint16_t oilTmpConvertSpace = 0;       //油温转换时间间隔
volatile  uint8_t  flagReadOilTmp     = 0;
/***********油温相关结束************************************************************/

/*****************************************************************************
 Function    : Read_Number_Of_VF
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
uint16_t Read_Number_Of_VF(void)
{
    return __HAL_TIM_GET_COUNTER(&htim2);
}
/*****************************************************************************
 Function    : Clear_Number_Of_VF
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void Clear_Number_Of_VF(void)
{
    __HAL_TIM_SET_COUNTER(&htim2, 0);
}
/*****************************************************************************
 Function    : Calculate_Switch_Delay
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void Calculate_Switch_Delay(uint16_t u)
{
    if(u < 135)
    {
        sw.switchDelayH = 41;
        sw.switchDelayF = 36;
    }
    else if(u >= 135 && u < 145)
    {
        sw.switchDelayH = 37;
        sw.switchDelayF = 30;
    }
    else if(u >= 145 && u < 155)
    {
        sw.switchDelayH = 33;
        sw.switchDelayF = 28;
    }
    else if(u >= 155 && u < 165)
    {
        sw.switchDelayH = 31;
        sw.switchDelayF = 25;
    }
    else if(u >= 165 && u < 175)
    {
        sw.switchDelayH = 29;
        sw.switchDelayF = 23;
    }
    else if(u >= 175 && u < 185)
    {
        sw.switchDelayH = 27;
        sw.switchDelayF = 21;
    }
    else if(u >= 185 && u < 195)
    {
        sw.switchDelayH = 26;
        sw.switchDelayF = 20;
    }
    else if(u >= 195 && u < 205)
    {
        sw.switchDelayH = 24;
        sw.switchDelayF = 19;
    }
    else if(u >= 205 && u < 215)
    {
        sw.switchDelayH = 23;
        sw.switchDelayF = 18;
    }
    else if(u >= 215 && u < 225)
    {
        sw.switchDelayH = 22;
        sw.switchDelayF = 17;
    }
    else if(u >= 225 && u < 235)
    {
        sw.switchDelayH = 21;
        sw.switchDelayF = 16;
    }
    else if(u >= 235 && u < 245)
    {
        sw.switchDelayH = 20;
        sw.switchDelayF = 15;
    }
    else if(u >= 245 && u < 255)
    {
        sw.switchDelayH = 20;
        sw.switchDelayF = 15;
    }
    else if(u >= 255)
    {
        sw.switchDelayH = 19;
        sw.switchDelayF = 14;
    }
    sw.switchDelayH = 30 + (20 - sw.switchDelayH);
    sw.switchDelayF = 20 + (20 - sw.switchDelayF);
}
/*****************************************************************************
 Function    : Task_Read_Oil_Temp
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void Task_Read_Oil_Temp(void)
{
    float tmp = 0;
    if(flagReadOilTmp == 0 && readOilTmpSpace == 0)
    {
        /*-----------------关闭中断------------------------*/
        __disable_irq();
        if(Temp_Convert_Start() == TMP_OK)
        {
            oilTmpConvertSpace = OIL_TMP_CONVERT_TIME;
            flagReadOilTmp = 1;
        }
        else
            readOilTmpSpace = READ_OIL_TMP_PERIOD;
        /*-----------------打开中断------------------------*/
        __enable_irq();
    }
    if(flagReadOilTmp == 1)
    {
        if(oilTmpConvertSpace == 0)
        {
            /*-----------------关闭中断------------------------*/
            __disable_irq();
            if(Temp_Read(&tmp) == TMP_OK)
            {
                sw.temp = tmp * 10;
            }
            readOilTmpSpace = READ_OIL_TMP_PERIOD;
            flagReadOilTmp = 0;
            /*-----------------打开中断------------------------*/
            __enable_irq();
        }
    }
}
/*****************************************************************************
 Function    : Task_TIM_Work
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void Task_TIM_Work(void)
{
    Switch_TIM_Work();
    Modbus_Rx_Space_Counter();
    if(oilTmpConvertSpace > 0)
        oilTmpConvertSpace--;
    if(msCount < 1000)
        msCount++;
    else
    {
        msCount = 0;
        countOver = 0;
        freq = countOver*65536 + TIM2->CNT;
        Clear_Number_Of_VF();
        uVF = 120 + freq/50;
        Calculate_Switch_Delay(uVF);
        Task_Led();
    }
}

/*****************************************************************************
 Function    : HAL_TIM_PeriodElapsedCallback
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim == (&htim3))
    {
        Task_TIM_Work();
    }
    else if(htim == (&htim2))
    {
        countOver++;
    }
}
/*****************************************************************************
 Function    : Task_Main
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void Task_Main()
{
    HAL_IWDG_Refresh(&hiwdg); //喂狗
    Modbus_Data_Analysis();
    if(sw.clearMotionNum == 1)
    {
        sw.clearMotionNum = 0;
        Write_Switch_Montion_Num(0);
    }
    if(sw.reboot == 1 && sw.currentCmd == NONE) //开关无动作时复位
    {
        __disable_fault_irq();
        NVIC_SystemReset();
    }
    if(sw.currentCmd == NONE)  //开关不动作的时候读油温
        Task_Read_Oil_Temp();
}

/************************ZXDQ *****END OF FILE****/
