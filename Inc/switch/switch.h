/**
  ******************************************************************************
  * File Name          : switch.h
  * Description        : This file provides code about switch.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __switch_H
#define __switch_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

	 
#define LOW   0
#define HIGH  1  
#define REMOTE_SIGNAL_DELAY 10 //MS



#define A_SWITCH_STATUS HAL_GPIO_ReadPin(DI3_GPIO_Port, DI3_Pin)
#define B_SWITCH_STATUS HAL_GPIO_ReadPin(DI2_GPIO_Port, DI2_Pin)
#define C_SWITCH_STATUS HAL_GPIO_ReadPin(DI1_GPIO_Port, DI1_Pin)

#define OPEN_STATUS  HAL_GPIO_ReadPin(DI4_GPIO_Port, DI4_Pin)
#define CLOSE_STATUS HAL_GPIO_ReadPin(DI5_GPIO_Port, DI5_Pin)

#define ZERO_U_STATUS HAL_GPIO_ReadPin(DI_ZERO_U_GPIO_Port, DI_ZERO_U_Pin)
#define ZERO_I_STATUS HAL_GPIO_ReadPin(DI_ZERO_I_GPIO_Port, DI_ZERO_I_Pin)

#define SECOND_DELAY_TIME      (5)     //ms 延时5ms后合闸C相
#define CONTROL_DELAY_TIME     (80)    //ms
#define WAIT_CHANG_SELECT_TIME (100)   //ms

#define FAULT_TIME             (2000)  //ms 
#define READ_RS_TIMEOUT        (90)    //ms   延时需要改动，2000是手动延时
#define SPACE_TIME             (1000)  //ms
#define FALUT_TYPE_DIF         (0x01)  //不一致故障
#define FALUT_TYPE_REF         (0x02)  //拒动故障    


typedef enum {FALSE = 0,TRUE = 1} bool;
/**
  * @brief  Current step status definition
  */
typedef enum
{
    FIRST                 = 0x00U,
    FIRST_DELAY           = 0x01U,
    SECOND                = 0x02U,
    SECOND_DELAY          = 0x03U,
    THIRD                 = 0x04U,
    WAIT_TO_END           = 0x05U,
}CurrentStepStatusTypeDef;

/**
  * @brief  Current switch status definition
  */
//CLOSE 合闸， OPEN 分闸，NONE 没有命令。
typedef enum
{
    NONE                 = 0x00U,
    OPEN                 = 0x01U,
    CLOSE                = 0x02U,
}CurrentSwitchStatusTypeDef;


/**
  * @brief  Switch structures definition
  */
typedef struct 
{
    CurrentStepStatusTypeDef   step                ;    //当前步骤
    CurrentSwitchStatusTypeDef AControlStatus      ;    //A相开关状态
    CurrentSwitchStatusTypeDef BControlStatus      ;    //B相开关状态
    CurrentSwitchStatusTypeDef CControlStatus      ;    //C相开关状态
    CurrentSwitchStatusTypeDef currentCmd          ;    //当前命令状态
    uint8_t ASwitchSignal; 
    uint8_t BSwitchSignal;
    uint8_t CSwitchSignal;       
    uint8_t closeSignal;
    uint8_t openSignal;
    uint8_t switchSignal;                               //0 无状态，1 合闸 2 分闸
    uint8_t lock;                                       //1 闭锁 0 正常
    uint8_t zeroULastLevel;                             //过零点电压检测上一次电平
    uint8_t zeroILastLevel;                             //过零点电流检测上一次电平
    bool zeroUFlag        ;                             //电压过零点标志
    bool zeroIFlag        ;                             //电流过零点标志
    bool isEnd            ;                             //是否结束标志
    bool changeSelectFlag ;                             //选择开关状态切换标志
    bool waitChangeSelectFlag;
    bool spaceFlag;
    bool isInit;
    uint16_t  closeCount;                               //合闸延时计数
    uint16_t  openCount;                                //分闸延时计数
    uint16_t  cmdTimeoutCount  ;                        //分合闸命令超时计数
    uint16_t  firstDelayCount  ;                        //第一步延时计数
    uint16_t  secondDelayCount ;                        //第二步延时计数
    uint16_t  AControlCount     ;                       //A相选择遥信计数
    uint16_t  BControlCount     ;                       //B相选择遥信计数
    uint16_t  CControlCount     ;                       //C相选择遥信计数
    uint16_t  AswitchCount     ;                        //A相遥信计数
    uint16_t  BswitchCount     ;                        //B相遥信计数
    uint16_t  CswitchCount     ;                        //C相遥信计数
    uint16_t  faultCount       ;                        //故障延时计数
    uint16_t  rsTimeoutCount   ;                        //遥信超时计数，在规定的时间内没有读到想要的反馈
    uint16_t  waitChangeSelectCount;
    uint16_t  sapceCount;
    uint16_t  faultType;                                //0 正常 第1位 三相开关不一致故障，第2位开关拒动故障，其他位保留
    uint16_t  motionNumH;                               //开关动作次数高
    uint16_t  motionNumL;                               //开关动作次数低
    uint8_t   clearMotionNum;                           //清除动作次数命令
    uint8_t   reboot;                                   //重启
    uint16_t  temp;                                     //温度
    uint8_t switchDelayH;                               //合作开关延时
    uint8_t switchDelayF;                               //分闸开关延时
}SwitchTypeDef;

void Switch_Goto_Pre(void);
void Switch_Init(void);
void Switch_TIM_Work(void);

#ifdef __cplusplus
}
#endif
#endif /*__ task_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT ZXDQ *****END OF FILE****/
