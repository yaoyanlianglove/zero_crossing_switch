/**
  ******************************************************************************
  * File Name          : switch.c
  * Description        : This file provides code about switch.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#include "switch.h"
#include "memory.h"
#include "delay.h"

SwitchTypeDef sw;

/*****************************************************************************
 Function    : A_Select_Open_Close
 Description : A相开关选择方向
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void A_Select_Open_Close(uint8_t cmd)
{
    if(cmd == LOW)
        HAL_GPIO_WritePin(DO3_GPIO_Port, DO3_Pin, GPIO_PIN_RESET);
    else if(cmd == HIGH)
        HAL_GPIO_WritePin(DO3_GPIO_Port, DO3_Pin, GPIO_PIN_SET);
}

/*****************************************************************************
 Function    : B_Select_Open_Close
 Description : B相开关选择方向
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void B_Select_Open_Close(uint8_t cmd)
{
    if(cmd == LOW)
        HAL_GPIO_WritePin(DO2_GPIO_Port, DO2_Pin, GPIO_PIN_RESET);
    else if(cmd == HIGH)
        HAL_GPIO_WritePin(DO2_GPIO_Port, DO2_Pin, GPIO_PIN_SET);
}

/*****************************************************************************
 Function    : C_Select_Open_Close
 Description : C相开关选择方向
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void C_Select_Open_Close(uint8_t cmd)
{
    if(cmd == LOW)
        HAL_GPIO_WritePin(DO1_GPIO_Port, DO1_Pin, GPIO_PIN_RESET);
    else if(cmd == HIGH)
        HAL_GPIO_WritePin(DO1_GPIO_Port, DO1_Pin, GPIO_PIN_SET);
}

/*****************************************************************************
 Function    : A_Open
 Description : 打开A相开关
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void A_Open(void)
{
    HAL_GPIO_WritePin(DO6_GPIO_Port, DO6_Pin, GPIO_PIN_SET);
}

/*****************************************************************************
 Function    : A_Close
 Description : 关闭A相开关
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void A_Close(void)
{
    HAL_GPIO_WritePin(DO6_GPIO_Port, DO6_Pin, GPIO_PIN_RESET);
}

/*****************************************************************************
 Function    : B_Open
 Description : 打开B相开关
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void B_Open(void)
{
    HAL_GPIO_WritePin(DO5_GPIO_Port, DO5_Pin, GPIO_PIN_SET);
}

/*****************************************************************************
 Function    : B_Close
 Description : 关闭B相开关
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void B_Close(void)
{
    HAL_GPIO_WritePin(DO5_GPIO_Port, DO5_Pin, GPIO_PIN_RESET);
}

/*****************************************************************************
 Function    : C_Open
 Description : 打开C相开关
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void C_Open(void)
{
    HAL_GPIO_WritePin(DO4_GPIO_Port, DO4_Pin, GPIO_PIN_SET);
}

/*****************************************************************************
 Function    : C_Close
 Description : 关闭C相开关
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void C_Close(void)
{
    HAL_GPIO_WritePin(DO4_GPIO_Port, DO4_Pin, GPIO_PIN_RESET);
}

/*****************************************************************************
 Function    : Read_DI
 Description : 读遥信
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void Read_DI(void)
{
    if(sw.ASwitchSignal == A_SWITCH_STATUS)
    {
        if(sw.AswitchCount < REMOTE_SIGNAL_DELAY)
            sw.AswitchCount++;
        else
        {
            sw.ASwitchSignal = A_SWITCH_STATUS ^ 1;
        }
    }
    else 
        sw.AswitchCount = 0;

    if(sw.BSwitchSignal == B_SWITCH_STATUS)
    {
        if(sw.BswitchCount < REMOTE_SIGNAL_DELAY)
            sw.BswitchCount++;
        else
        {
            sw.BSwitchSignal = B_SWITCH_STATUS ^ 1;
        }
    }
    else 
        sw.BswitchCount = 0;

    if(sw.CSwitchSignal == C_SWITCH_STATUS)
    {
        if(sw.CswitchCount < REMOTE_SIGNAL_DELAY)
            sw.CswitchCount++;
        else
        {
            sw.CSwitchSignal = C_SWITCH_STATUS ^ 1;
        }
    }
    else 
        sw.CswitchCount = 0;

    if(sw.closeSignal == CLOSE_STATUS)
    {
        if(sw.closeCount < REMOTE_SIGNAL_DELAY)
            sw.closeCount++;
        else
        {
            sw.closeSignal = CLOSE_STATUS ^ 1;
        }
    }
    else 
        sw.closeCount = 0;

    if(sw.openSignal == OPEN_STATUS)
    {
        if(sw.openCount < REMOTE_SIGNAL_DELAY)
            sw.openCount++;
        else
        {
            sw.openSignal = OPEN_STATUS ^ 1;
        }
    }
    else 
        sw.openCount = 0;

    if(sw.ASwitchSignal == 1 && sw.BSwitchSignal == 1 && sw.CSwitchSignal == 1)
    {
        if(sw.faultType == FALUT_TYPE_DIF)
        {
            sw.lock = 0;//? 从不一致故障中恢复，需不需要解锁 
        }
        sw.faultType &= 0xFFFF << 1;
        sw.faultCount   = 0;
        sw.switchSignal = 1; //合闸
    }
    else if(sw.ASwitchSignal == 0 && sw.BSwitchSignal == 0 && sw.CSwitchSignal == 0)
    {
        if(sw.faultType == FALUT_TYPE_DIF)
        {
            sw.lock = 0;//? 从不一致故障中恢复，需不需要解锁 
        }
        sw.faultType &= 0xFFFF << 1;
        sw.faultCount   = 0;
        sw.switchSignal = 2; //分闸
    }
    else
    {
        sw.switchSignal = 0;
        if(sw.lock == 0)
        {
            if(sw.faultCount < FAULT_TIME)
                sw.faultCount++;
            else
            {
                sw.faultType |= FALUT_TYPE_DIF;
                sw.lock = 1;
            }
        }  
    }
}
/*****************************************************************************
 Function    : Switch_Goto_Pre
 Description : 选择开关去预判方向
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void Switch_Goto_Pre(void)
{
    delay_ms(100);
    while(sw.switchSignal == 0)
    {
        ;//一直读开关遥信，直到正确读到遥信
    }
    if(sw.lock == 0)
    {
        if(sw.switchSignal == 1)
        {
            A_Select_Open_Close(HIGH);
            B_Select_Open_Close(HIGH);
            C_Select_Open_Close(HIGH);
        }
        else if(sw.switchSignal == 2)
        {
            A_Select_Open_Close(LOW);
            B_Select_Open_Close(LOW);
            C_Select_Open_Close(LOW);
        }
        delay_ms(SPACE_TIME);
        sw.isInit = TRUE;
    }
}
/*****************************************************************************
 Function    : Switch_Init
 Description : 开关参数初始化
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void Switch_Init(void)
{
    uint32_t  num = 0;
    sw.step                  = FIRST;         //第一次上电
    sw.AControlStatus        = NONE;          //A相开关状态
    sw.BControlStatus        = NONE;          //B相开关状态
    sw.CControlStatus        = NONE;          //C相开关状态
    sw.currentCmd            = NONE;          //当前命令状态
    sw.ASwitchSignal         = 0;
    sw.BSwitchSignal         = 0;
    sw.CSwitchSignal         = 0;
    sw.closeSignal           = 0;
    sw.openSignal            = 0;
    sw.switchSignal          = 0;
    sw.lock                  = 0;
    sw.zeroULastLevel        = 2;
    sw.zeroILastLevel        = 2;

    sw.zeroUFlag             = FALSE;         //电压过零点标志
    sw.isEnd                 = FALSE;         //是否结束标志
    sw.changeSelectFlag      = FALSE;         //选择开关状态切换标志
    sw.waitChangeSelectFlag  = FALSE;
    sw.spaceFlag             = FALSE;
    sw.isInit                = FALSE;

    sw.closeCount            = 0;              //合闸延时计数
    sw.openCount             = 0;              //分闸延时计数
    sw.cmdTimeoutCount       = 0;              //分合闸命令超时计数
    sw.firstDelayCount       = 0;              //第一步延时计数
    sw.secondDelayCount      = 0;              //第二步延时计数
    sw.AControlCount         = 0;              //A相选择遥信计数
    sw.BControlCount         = 0;              //B相选择遥信计数
    sw.CControlCount         = 0;              //C相选择遥信计数 
    sw.AswitchCount          = 0;              //A相遥信计数
    sw.BswitchCount          = 0;              //B相遥信计数
    sw.CswitchCount          = 0;              //C相遥信计数
    sw.faultCount            = 0;
    sw.faultType             = 0;
    sw.rsTimeoutCount        = 0;              //遥信命令超时计数
    sw.waitChangeSelectCount = 0;
    sw.sapceCount            = 0;
    sw.temp                  = 0.0;
    sw.switchDelayH          = 21;
    sw.switchDelayF          = 16;

    sw.clearMotionNum        = 0;

    Read_Switch_Montion_Num(&num);
    sw.motionNumH = num >> 16;
    sw.motionNumL = num & 0xFFFF;
}
/*****************************************************************************
 Function    : Get_Zero_Crossing
 Description : 获取过零点
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void Get_Zero_Crossing(void)
{
    uint8_t currentULevel = 0;
    uint8_t currentILevel = 0;
    currentULevel = ZERO_U_STATUS;
    currentILevel = ZERO_I_STATUS;
    if(sw.zeroULastLevel == 2)
        sw.zeroULastLevel = currentULevel;
    else if(sw.zeroULastLevel != currentULevel)
    {
        sw.zeroULastLevel = currentULevel;
        sw.zeroUFlag = TRUE;
    }
    else
    {
        sw.zeroUFlag = FALSE;
    }

    if(sw.zeroILastLevel == 2)
        sw.zeroILastLevel = currentILevel;
    else if(sw.zeroILastLevel != currentILevel)
    {
        sw.zeroILastLevel = currentILevel;
        sw.zeroIFlag = TRUE;
    }
    else
    {
        sw.zeroIFlag = FALSE;
    }
}
/*****************************************************************************
 Function    : Step_First
 Description : 开关控制第一步
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void Step_First(void)
{
    if(sw.currentCmd == NONE)
    {
        if(sw.closeSignal == 1 && sw.openSignal == 0  && sw.switchSignal == 2)  //读取合闸命令
        {
            sw.currentCmd = CLOSE;
        }
        else if(sw.closeSignal == 0 && sw.openSignal == 1 && sw.switchSignal == 1)//读取分闸命令
        {
            sw.currentCmd = OPEN;
        }
    }
    //等待过零点，如果50ms内未出现过零点，此次命令失效+++++++++++++++++++++++
    else 
    {
        if(sw.cmdTimeoutCount < 50)
            sw.cmdTimeoutCount ++;
        else
        {
            sw.cmdTimeoutCount = 0;
            sw.currentCmd      = NONE;
        }
        Get_Zero_Crossing();
        if(sw.currentCmd == CLOSE)
        {
            if(sw.zeroUFlag == TRUE)
            {
                sw.cmdTimeoutCount  = 0;
                sw.zeroUFlag        = FALSE;
                sw.step             = FIRST_DELAY;
            }
        }
        else if(sw.currentCmd == OPEN)
        {
            if(sw.zeroIFlag == TRUE)
            {
                sw.cmdTimeoutCount  = 0;
                sw.zeroIFlag        = FALSE;
                sw.step             = FIRST_DELAY;
            }
        }  
    }
    //等待过零点，如果50ms内未出现过零点，此次命令失效+++++++++++++++++++++++ 
}
/*****************************************************************************
 Function    : Step_Second
 Description : 开关控制第二步
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void Step_Second(void)
{
    if(sw.currentCmd == CLOSE)
    {
        A_Open();
        sw.AControlStatus = OPEN;
        B_Open();
        sw.BControlStatus = OPEN;
    }
    else if(sw.currentCmd == OPEN)
    {
        A_Open();
        sw.AControlStatus = OPEN;
    }
    sw.step = SECOND_DELAY;
}
/*****************************************************************************
 Function    : Timeout_To_Close_Control
 Description : 强制关闭控制开关
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void Timeout_To_Close_Control(void)
{
    //80MS关闭控制开关+++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
    if(sw.AControlStatus == OPEN)
    {
        if(sw.AControlCount < CONTROL_DELAY_TIME)
            sw.AControlCount++;
        else
        {
            sw.AControlCount = 0;
            A_Close();
            sw.AControlStatus = CLOSE;
        }
    }
    if(sw.BControlStatus == OPEN)
    {
        if(sw.BControlCount < CONTROL_DELAY_TIME)
            sw.BControlCount++;
        else
        {
            sw.BControlCount = 0;
            B_Close();
            sw.BControlStatus = CLOSE;
        }
    }
    if(sw.CControlStatus == OPEN)
    {
        if(sw.CControlCount < CONTROL_DELAY_TIME)
            sw.CControlCount++;
        else
        {
            sw.CControlCount = 0;
            C_Close();
            sw.CControlStatus = CLOSE;
        }
    }
    //80MS关闭控制开关+++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
}
/*****************************************************************************
 Function    : Change_Select
 Description : 改变方向开关方向
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void Change_Select(void)
{
    if(sw.waitChangeSelectFlag == FALSE)
    {
        if(sw.switchSignal == 1 && sw.currentCmd == CLOSE)
        {
            sw.rsTimeoutCount  = 0;
            sw.waitChangeSelectFlag = TRUE;
        }
        else if(sw.switchSignal == 2 && sw.currentCmd == OPEN)
        {
            sw.rsTimeoutCount  = 0;
            sw.waitChangeSelectFlag = TRUE;
        }
        else
        {
            if(sw.rsTimeoutCount < READ_RS_TIMEOUT)
                sw.rsTimeoutCount++;
            else
            {
                sw.rsTimeoutCount  = 0;
                sw.faultType |= FALUT_TYPE_REF;
                sw.lock       = 1;
                sw.changeSelectFlag = TRUE;
            }
        }
    }
    else if(sw.changeSelectFlag == FALSE)
    {
        if(sw.waitChangeSelectCount < WAIT_CHANG_SELECT_TIME)
            sw.waitChangeSelectCount++;
        else
        {
            sw.waitChangeSelectCount = 0;
            if(sw.currentCmd == CLOSE)
            {
                A_Select_Open_Close(HIGH);
                B_Select_Open_Close(HIGH);
                C_Select_Open_Close(HIGH);
            }
            else if(sw.currentCmd == OPEN)
            {
                A_Select_Open_Close(LOW);
                B_Select_Open_Close(LOW);
                C_Select_Open_Close(LOW);
            }
            sw.changeSelectFlag = TRUE;
        }
    }
    else
    {
        if(sw.sapceCount < SPACE_TIME)
            sw.sapceCount++;
        else
        {
            sw.sapceCount = 0;
            sw.spaceFlag  = TRUE;
        }
    }
}
/*****************************************************************************
 Function    : Switch_TIM_Work
 Description : 定时器中断开关任务
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void Switch_TIM_Work(void)
{
    Read_DI();
    if(sw.lock == 1 || sw.isInit == FALSE)
        return;
    if(sw.step == FIRST)//第一步 读开关控制信息，等待过零点，进入第一步的延时等待
    {
        Step_First();
    }
    else if(sw.step == FIRST_DELAY)//第一步的延时等待，延时时间到进入第二步
    {
        if(sw.currentCmd == CLOSE)
        {
            if(sw.firstDelayCount < sw.switchDelayH)
                sw.firstDelayCount++;
            else
            {
                sw.firstDelayCount = 0;
                sw.step = SECOND;
            }
        }
        else if(sw.currentCmd == OPEN)
        {
            if(sw.firstDelayCount < sw.switchDelayF)
                sw.firstDelayCount++;
            else
            {
                sw.firstDelayCount = 0;
                sw.step = SECOND;
            }
        }
        
    }
    else if(sw.step == SECOND)//第二步AB开关先动作，进入第二步的延时等待
    {
        Step_Second();
    }
    else if(sw.step == SECOND_DELAY)//第二步的延时等待，延时时间到进入第三步
    {
        if(sw.secondDelayCount < (SECOND_DELAY_TIME - 2))
            sw.secondDelayCount++;
        else
        {
            sw.secondDelayCount = 0;
            sw.step = THIRD;
        }
    }
    else if(sw.step == THIRD)//第三步C开关动作，进入等待结束标志
    {
        if(sw.currentCmd == CLOSE)
        {
            C_Open();
            sw.CControlStatus = OPEN;
        }
        else if(sw.currentCmd == OPEN)
        {
            B_Open();
            sw.BControlStatus = OPEN;
            C_Open();
            sw.CControlStatus = OPEN;
        }
        sw.step = WAIT_TO_END;
    }
    else if(sw.step == WAIT_TO_END)//等待结束标志，然后回到第一步
    {
        if(sw.isEnd == TRUE)
        {
            sw.isEnd = FALSE;
            sw.step = FIRST;
        }
    }

    Timeout_To_Close_Control();
    //100MS改变方向选择开关方向+++++++++++++++++++++++++++++++++++++++++++++++ 
    if(sw.step == WAIT_TO_END)
    {
        Change_Select();
    }
    //100MS改变方向选择开关方向+++++++++++++++++++++++++++++++++++++++++++++++ 
    
    if(sw.AControlStatus == CLOSE && sw.BControlStatus == CLOSE && 
        sw.CControlStatus == CLOSE && sw.spaceFlag == TRUE) //一次调压结束，标志位复位
    {
        sw.isEnd            = TRUE;
        sw.currentCmd       = NONE;
        sw.spaceFlag        = FALSE;
        sw.zeroULastLevel   = 2;
        sw.zeroILastLevel   = 2;
        sw.zeroUFlag        = FALSE;
        sw.zeroIFlag        = FALSE;
        sw.waitChangeSelectFlag = FALSE;
        sw.changeSelectFlag = FALSE;
        if(sw.motionNumL < 0xFFFF)
            sw.motionNumL = sw.motionNumL + 1;
        else if(sw.motionNumH < 0xFFFF)
            sw.motionNumH = sw.motionNumH + 1;
        Write_Switch_Montion_Num(sw.motionNumH*0xFFFF + sw.motionNumL);
    }
}
/************************ZXDQ *****END OF FILE****/



