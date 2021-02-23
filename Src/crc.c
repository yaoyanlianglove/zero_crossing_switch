/**
  ******************************************************************************
  * File Name          : crc.c
  * Description        : This file contains all functions about crc16.
  ******************************************************************************
  * @attention
  * 
  *
  ******************************************************************************
  */

/*****************************************************************************
 Function    : CRC_16
 Description : Calculate CRC16 checksums for input data.
 Input       : puchMsg, the pointer of data
               usDataLen, the length of data
 Output      : None
 Return      : None
 *****************************************************************************/   
#include "crc.h"

uint16_t CRC_16(uint8_t* puchMsg, uint16_t usDataLen)
{
    uint8_t uchCRCHi;
    uint8_t uchCRCLo;
    unsigned uIndex;
    uchCRCHi = 0xFF;
    uchCRCLo = 0xFF;
    while ( usDataLen-- )
    {
        uIndex = uchCRCHi ^ (uint8_t)( *puchMsg++ );
        uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex];
        uchCRCLo = auchCRCLo[uIndex]; 
    }
    return ( uchCRCHi << 8 | uchCRCLo );
}



/************************ZXDQ *****END OF FILE****/
