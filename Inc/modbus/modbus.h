/**
  ******************************************************************************
  * File Name          : modbus.h
  * Description        : This file provides the function about modbus.
  ******************************************************************************
  * @attention
  
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __modbus_H
#define __modbus_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

#define MODBUS_UART                     huart1
#define MODBUS_DEVICE_ID                0x01
#define MODBUS_RX_SPACE_TIMEOUT         3


#define MODBUS_COIN_REG_LIMIT           2
#define MODBUS_DIS_INPUT_REG_LIMIT      3
#define MODBUS_INPUT_REG_LIMIT          3


#define RS485DIR_TX     HAL_GPIO_WritePin(RS485_EN_GPIO_Port, RS485_EN_Pin, GPIO_PIN_SET)       
#define RS485DIR_RX     HAL_GPIO_WritePin(RS485_EN_GPIO_Port, RS485_EN_Pin, GPIO_PIN_RESET)

/**
  * @brief  Modbus structures definition
  */
typedef struct 
{
    uint8_t  rxBuffer[128];               //接收数据
    uint8_t  txBuffer[128];               //发送数据 
    uint8_t  txLength;                    //发送数据长度
    uint8_t  rxBeginFlag;                 //接收开始标志 
    uint8_t  rxEndFlag;                   //接收结束标志
    uint8_t  rxCount;                     //接收计数
    uint8_t  rxSpaceCount;                //接收数据时间间隔计数
    uint8_t  *coilReg[32];                //线圈寄存器
    uint8_t  *discreteInputReg[32];       //离散输入寄存器
    uint16_t *inputReg[32];               //输入寄存器
    uint16_t *holdingReg[32];             //保存寄存器
}ModbusTypeDef;


void Modbus_Send_Data(uint8_t *pData, uint16_t size);
void Modbus_Start_Rec(void);
void Modbus_Rx_Space_Counter(void);
void Modbus_Data_Analysis(void);

#ifdef __cplusplus
}
#endif

#endif

/************************ZXDQ *****END OF FILE****/
  

