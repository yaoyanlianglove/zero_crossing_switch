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
#include "i2c.h"
#include "delay.h"

#define ADDR_AT24C512 0xA0


/*****************************************************************************
 Function    : AT24C02_Write_nBytes
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
int16_t AT24C512_Write_nBytes(uint8_t *data, uint16_t addr, uint16_t length)
{
    HAL_StatusTypeDef res = HAL_OK;
    res = HAL_I2C_Mem_Write( &hi2c1, ADDR_AT24C512, addr,
        I2C_MEMADD_SIZE_16BIT, data, length, 1000 );
    if(res == HAL_OK)
        return 0;
    else
        return -1;
}
/*****************************************************************************
 Function    : AT24C02_Read_nBytes
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/ 
int16_t AT24C512_Read_nBytes(uint8_t *data, uint16_t addr, uint16_t length)
{
    HAL_StatusTypeDef res = HAL_OK;
    res =HAL_I2C_Mem_Read( &hi2c1, ADDR_AT24C512, addr, 
        I2C_MEMADD_SIZE_16BIT, data, length, 1000 );
    if(res == HAL_OK)
        return 0;
    else
        return -1;
}
/*****************************************************************************
 Function    : Write_Data_To_Memory
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
int16_t Write_Data_To_Memory(uint8_t *data, uint16_t addr, uint16_t length)
{
    int16_t res = 0;
    uint16_t i = 0;
    uint16_t k = 128 - addr%128;
    uint16_t l = (length - k)/128;
    uint16_t j = (length - k)%128;
    if(addr + length > 65535)
        return -1;
    HAL_GPIO_WritePin(WP_GPIO_Port, WP_Pin, GPIO_PIN_RESET);
    if(length <= k)
        res = AT24C512_Write_nBytes(data, addr, length);
    else 
    {
        res = AT24C512_Write_nBytes(data, addr, k);
        if(res != 0)
            return -1;
        delay_ms(10);
        for(i = 0; i < l; i++)
        {
            res = AT24C512_Write_nBytes(data + k + i*128, addr + k + i*128, 128);
            if(res != 0)
                return -1;
            delay_ms(10);
        }
        res = AT24C512_Write_nBytes(data + k + l*128, addr + k + l*128, j);
    }
    HAL_GPIO_WritePin(WP_GPIO_Port, WP_Pin, GPIO_PIN_SET);
    delay_ms(10);
    return res;
}
/*****************************************************************************
 Function    : Read_Data_From_Memory
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/ 
int16_t Read_Data_From_Memory(uint8_t *data, uint16_t addr, uint16_t length)
{
    int16_t res = 0;
    if(addr + length > 65535)
        return -1;
    res = AT24C512_Read_nBytes(data, addr, length);
    return res;
}
/************************ZXDQ *****END OF FILE****/

