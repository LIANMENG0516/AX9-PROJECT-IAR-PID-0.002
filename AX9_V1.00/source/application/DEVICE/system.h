#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "stm32f4xx.h"

#include "gouble.h"

#define PID_CTRL                0       

#define SYSTEM_OFF              0
#define SYSTEM_ON               1
#define SYSTEM_SLEEP            2

#define USB_CHANNEL             1
#define ECCOM_CHANNEL           2
#define DEBUGCOM_CHANNEL        3

#define FirmwareVersion_H       0x90
#define FirmwareVersion_L       0x00

#define HardwareVersion_H       0x90
#define HardwareVersion_L       0x00

#define IDLE                    0
#define BUSY                    1

typedef enum {FALSE = 0, TRUE = !FALSE} bool;

typedef struct
{    
    bool DebugMessage;                  //调试信息开关
  
    bool HvFlag;
    bool CwFlag;

    bool RoughAdjVolCwOpen;             //CW粗调开关
    bool RoughAdjVolHv1Open;            //HV1粗调开关
    bool RoughAdjVolHv2Open;            //HV2粗调开关
      
    bool WaitRoughAdjVolResultCwOpen;   //CW粗调结果等待开关
    bool WaitRoughAdjVolResultHv1Open;  //HV1粗调结果等待开关
    bool WaitRoughAdjVolResultHv2Open;  //HV2粗调结果等待开关
      
    bool FineAdjVolCwOpen;              //CW微调开关
    bool FineAdjVolHv1Open;             //HV1微调开关
    bool FineAdjVolHv2Open;             //HV2微调开关

    bool CwMinitorOpen;                 //CW高压监控开关 
    bool Hv1MinitorOpen;                //HV1高压监控开关   
    bool Hv2MinitorOpen;                //HV2高压监控开关

    bool CwTimerOpen;                   //CW计时开关
    bool Hv1TimerOpen;                  //HV1计时开关
    bool Hv2TimerOpen;                  //HV2计时开关
    
    bool TestTimerOpen;                 //测试计时开关

    uint8_t CwAdjVolCompleteFlag;       //CW低压调压完成标志位  0:调压完成 1:调压忙 
    uint8_t Hv1AdjVolCompleteFlag;      //HV1高压调压完成标志位 0:调压完成 1:调压忙
    uint8_t Hv2AdjVolCompleteFlag;      //HV2高压调压完成标志位 0:调压完成 1:调压忙 
    
    uint8_t FineAdjVolCwCnt;            //CW微调次数
    uint8_t FineAdjVolHv1Cnt;           //HV1微调次数
    uint8_t FineAdjVolHv2Cnt;           //HV2微调次数
    
    uint16_t CwTime;                    //调压时间
    uint16_t CwTimeOut;                 //调压超时时间

    uint16_t Hv1Time;                   //调压时间
    uint16_t Hv1TimeOut;                //调压超时时间
    
    uint16_t Hv2Time;                   //调压时间
    uint16_t Hv2TimeOut;                //调压超时时间
    
    uint16_t TestTime;                  //调压时间
    uint16_t TestTimeOut;               //调压超时时间

    uint16_t T_VPP1;
    uint16_t T_VNN1;
    uint16_t T_VPP2;
    uint16_t T_VNN2;
    
    uint16_t T_PCW;
    uint16_t T_NCW;
    
    uint16_t Old_T_VPP1;
    uint16_t Old_T_VNN1;
    uint16_t Old_T_VPP2;
    uint16_t Old_T_VNN2;
    
    uint16_t Old_T_PCW;
    uint16_t Old_T_NCW;
    
    uint16_t MAX_VPP1;
    uint16_t MIN_VPP1;
    uint16_t MAX_VNN1;
    uint16_t MIN_VNN1;
    
    uint16_t MAX_VPP2;
    uint16_t MIN_VPP2;
    uint16_t MAX_VNN2;
    uint16_t MIN_VNN2;
    
    uint16_t MAX_PCW;
    uint16_t MIN_PCW;
    uint16_t MAX_NCW;
    uint16_t MIN_NCW;
    
    uint16_t T_McuDacHv1;
    uint16_t T_SpiDacHv1;
    uint16_t T_McuDacHv2;
    uint16_t T_SpiDacHv2;
    uint16_t T_SpiDacPcw;
    uint16_t T_SpiDacNcw;
    
    uint16_t P_McuDacHv1;
    uint16_t P_SpiDacHv1;
    uint16_t P_McuDacHv2;
    uint16_t P_SpiDacHv2;
    uint16_t P_SpiDacPcw;
    uint16_t P_SpiDacNcw;

    uint16_t R_VPP1;
    uint16_t R_VNN1;
    uint16_t R_VPP2;
    uint16_t R_VNN2;
    uint16_t R_PCW;
    uint16_t R_NCW;
    
    uint16_t R_AP12V;
    uint16_t R_AN12V;
    uint16_t R_AP5V5_1;
    uint16_t R_AP5V5_2;
    uint16_t R_AN5V5;
    uint16_t R_A3V75;
    uint16_t R_A2V25;
    uint16_t R_D1V45;
    uint16_t R_INPUT;
    uint16_t R_D0V95;
       
    uint16_t R_IADP;
    
    #if PID_CTRL
    
    bool PidOpen;
    
    float OldOffSetVpp1;                //偏差
    float NowOffSetVpp1;
    uint16_t McuDacVpp1;
    
    float OldOffSetVnn1;                //偏差
    float NowOffSetVnn1;                //偏差
    uint16_t McuDacVnn1;

    #endif
    
}Ad_VolStruct;

typedef struct
{    
    bool    DebugMessage;                                                       //调试信息开关
    
    uint8_t FPGA;
    uint8_t AFE58;
    uint8_t CPU;
    uint8_t MCU;
    
}SysTemper;

typedef struct
{    
    bool     DebugMessage;                                                      //调试信息开关
    
    uint8_t  CntlMode;
    
    uint8_t Duty1;
    uint8_t Duty2;
    uint8_t Duty3;
    uint8_t Duty4;
    uint8_t Duty5;
    
    uint16_t Rpm1;
    uint16_t Rpm2;
    uint16_t Rpm3;
    uint16_t Rpm4;
    uint16_t Rpm5;
}FanStrc;

typedef struct
{    
    bool            DebugMessage;                                               //调试信息开关
    
    bool            Timeout;
    bool            HV_Send;
    bool            CW_Send;
    bool            Firmware_Send;
    bool            CompileInfo_Send;
    bool            Voltage_Send;
    bool            FanInfo_Send;
    bool            PwrInfo_Send;
    bool            Vpp1Vnn1En_Send;
    bool            Vpp1Vnn1Dis_Send;
    bool            Vpp2Vnn2En_Send;
    bool            Vpp2Vnn2Dis_Send;
    bool            EcInfo_Send;
    bool            WriteBoardOk_Send;      //写响应
    bool            BoardInfo_Send;         //读响应
    uint8_t         Channel;                //命令通道, 是指程序接收到的命令从USB、ECCOM、DEBUGCOM哪个通道进入
}Command_Deal;

typedef struct
{    
    bool            DebugMessage;          //调试信息开关    
    
    bool            Ac_Insert;                  //AC接入标志
    bool            BatPak_Insert;              //电池包接入标志
    bool            Bat1_Insert;
    bool            Bat2_Insert;
    uint8_t         Bat1_Power;                 //电池电量
    uint8_t         Bat2_Power;                 //电池电量
    uint8_t         Bat1_Tempature;             //电池温度
    uint8_t         Bat2_Tempature;             //电池温度
    uint8_t         Bat1_State;                 //电池故障标志
    uint8_t         Bat2_State;                 //电池故障标志
    
}PwrInfoStruct;

typedef struct
{
    Ad_VolStruct    AdjVol;
    SysTemper       Temperature;
    FanStrc         Fan;
    Command_Deal    Cmd;
    PwrInfoStruct   PwrInfo;
    uint8_t         SystemState;
    bool            KeyState;
    bool            PowerOnReq;
    bool            ShutDownReq;
    bool            System_S3_Change;
    bool            System_S4_Change;
    bool            S3_State;
    bool            S4_State;
    
    bool            DebugMessage;            //调试信息开关
}System_MsgStruct;

void Delay_Nop(uint16_t count);

bool System_PwrKey_Minitor(void);

bool System_S3_State_Minitor(void);

void SystemStateInit(void);

#endif
