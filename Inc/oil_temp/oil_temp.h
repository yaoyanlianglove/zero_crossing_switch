/**
  ******************************************************************************
  * File Name          : oil_temp.h
  * Description        : This file contains all functions about related to oil 
                         temperature measurement.
  ******************************************************************************
  * @attention
  
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __oil_temp_H
#define __oil_temp_H
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"


#define    DATA_WIRE_HIGH    HAL_GPIO_WritePin(TEMP_GPIO_Port, TEMP_Pin, GPIO_PIN_SET)       
#define    DATA_WIRE_LOW     HAL_GPIO_WritePin(TEMP_GPIO_Port, TEMP_Pin, GPIO_PIN_RESET)
#define    DATA_WIRE_STATUS  HAL_GPIO_ReadPin(TEMP_GPIO_Port, TEMP_Pin) 
#define    READ_OIL_TMP_PERIOD   30      //秒
#define    OIL_TMP_CONVERT_TIME  850     //毫秒


/**
  * @brief  Tmp status definition
  */
typedef enum
{
    TMP_OK          = 0x00U,
    TMP_ERROR       = 0x01U
}TmpStatusTypeDef;
TmpStatusTypeDef   Temp_Convert_Start(void);
TmpStatusTypeDef   Temp_Read(float *tmp);

#ifdef __cplusplus
}
#endif

#endif

/************************ZXDQ *****END OF FILE****/
  

