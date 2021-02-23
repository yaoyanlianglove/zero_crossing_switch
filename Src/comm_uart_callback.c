/**
  ******************************************************************************
  * File Name          : comm_uart_callback.c
  * Description        : This file contains all functions about HAL UART callback.
  ******************************************************************************
  * @attention
  * 
  *
  ******************************************************************************
  */


#include "modbus.h"
#include "usart.h"

extern ModbusTypeDef modbus;  
extern uint8_t modbusRxBuffer;


/*****************************************************************************
 Function    : HAL_UART_RxCpltCallback
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart == &MODBUS_UART) 
        RS485DIR_RX;
}
/*****************************************************************************
 Function    : HAL_UART_RxCpltCallback
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart == &MODBUS_UART)                                  // 判断是由哪个串口触发的中断
    {
        if(modbus.rxEndFlag == 0)
        {
            modbus.rxBuffer[modbus.rxCount] = modbusRxBuffer;
            if(modbus.rxBeginFlag == 0)
                modbus.rxBeginFlag = 1;
            modbus.rxSpaceCount = 0;
            if(modbus.rxCount < 128)
                modbus.rxCount++;
            else
                modbus.rxCount = 0;
        }
        else
            modbus.rxCount = 0;
        HAL_UART_Receive_IT(&MODBUS_UART, &modbusRxBuffer, 1); // 重新使能串口1接收中断
    }
}
/************************ZXDQ *****END OF FILE****/

