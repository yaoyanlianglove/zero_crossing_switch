/**
  ******************************************************************************
  * File Name          : memory.c
  * Description        : This file contains all functions about memory.
  ******************************************************************************
  * @attention
  * 
  *
  ******************************************************************************
  */
#include "at24c512.h"
#include "memory.h"

/*****************************************************************************
 Function    : Read_Switch_Montion_Num
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/ 
int16_t Read_Switch_Montion_Num(uint32_t *num)
{
    int16_t res = 0;
    uint8_t data[4] = {0};
    res = Read_Data_From_Memory(data, SWITCH_MOTION_NUM_ADDR, SWITCH_MOTION_NUM_LENGTH);
    *num = (data[0] << 24) + (data[1] << 16) + (data[2] << 8) + data[3];
    return res;
}
/*****************************************************************************
 Function    : Write_Switch_Montion_Num
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/ 
int16_t Write_Switch_Montion_Num(uint32_t num)
{
    int16_t res = 0;
    uint8_t data[4] = {0};
    data[0] =  (num >> 24) & 0xff;
    data[1] =  (num >> 16) & 0xff;
    data[2] =  (num >> 8)  & 0xff;
    data[3] =  (num )      & 0xff;
    res = Write_Data_To_Memory(data, SWITCH_MOTION_NUM_ADDR, SWITCH_MOTION_NUM_LENGTH);
    return res;
}
/************************ZXDQ *****END OF FILE****/

