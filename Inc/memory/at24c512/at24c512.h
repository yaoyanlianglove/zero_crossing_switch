/**
  ******************************************************************************
  * File Name          : at24c512.h
  * Description        : This file provides code about at24c512.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __at24c512_H
#define __at24c512_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

int16_t Write_Data_To_Memory(uint8_t *data, uint16_t addr, uint16_t length);
int16_t Read_Data_From_Memory(uint8_t *data, uint16_t addr, uint16_t length);

#ifdef __cplusplus
}
#endif
#endif /*__at24c512_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT ZXDQ *****END OF FILE****/
