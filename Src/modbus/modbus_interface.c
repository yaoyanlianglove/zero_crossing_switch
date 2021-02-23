/**
  ******************************************************************************
  * File Name          : modbus_interface.h
  * Description        : This file provides the function about interface of modbus.
  ******************************************************************************
  * @attention
  
  *
  ******************************************************************************
  */
#include "modbus_interface.h"
#include "modbus.h"

extern ModbusTypeDef modbus;
/*****************************************************************************
 Function    : Modbus_Interface_Init
 Description : None
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void Modbus_Interface_Init(SwitchTypeDef *sw)
{
	modbus.coilReg[0] = &sw->clearMotionNum;
    modbus.coilReg[1] = &sw->reboot;

    modbus.discreteInputReg[0] = &sw->ASwitchSignal;
    modbus.discreteInputReg[1] = &sw->BSwitchSignal;
    modbus.discreteInputReg[2] = &sw->CSwitchSignal;

    modbus.inputReg[0] = &sw->temp;
    modbus.inputReg[1] = &sw->motionNumH;
    modbus.inputReg[2] = &sw->motionNumL;

    Modbus_Start_Rec();
}
/************************ZXDQ *****END OF FILE****/
