/**
  ******************************************************************************
  * File Name          : memory.h
  * Description        : This file provides code about memory.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __memory_H
#define __memory_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/


#define SWITCH_MOTION_NUM_ADDR      1
#define SWITCH_MOTION_NUM_LENGTH    4

int16_t Read_Switch_Montion_Num(uint32_t *num);
int16_t Write_Switch_Montion_Num(uint32_t num);

#ifdef __cplusplus
}
#endif
#endif /*__memory_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT ZXDQ *****END OF FILE****/
