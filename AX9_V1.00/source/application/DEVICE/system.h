#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "stm32f4xx.h"

#include "gouble.h"

#define PID_CTRL                0       //����PID���ڿ���

#define SYSTEM_OFF              0
#define SYSTEM_ON               1
#define SYSTEM_SLEEP            2

#define USB_CHANNEL             1
#define ECCOM_CHANNEL           2
#define DEBUGCOM_CHANNEL        3

#define FirmwareVersion_H 0x90
#define FirmwareVersion_L 0x00

#define HardwareVersion_H 0x90
#define HardwareVersion_L 0x00

typedef enum {FALSE = 0, TRUE = !FALSE} bool;

typedef struct
{    
    bool DebugMessage;    //������Ϣ����
  
    bool HvFlag;
    bool CwFlag;

    bool VolInit;               //��ѹ��ʼ����־λ, ������ɺ���λ, ������˱�־λ���и�ѹ���ֵĳ�ʼ��
    bool VolMinitor;            //��ѹ��ر�־λ
    
    bool AdjVolOpen;            //���ε�ѹ����/�رձ�־
    bool AdjVolSuccess;         //���ε�ѹ�ɹ�����־
    bool MinAdjVolOpen;         //΢������/�رձ�־
    
    bool TimeFlag;              //��ʱ��־
    
    bool HV1NeedChange;         
    bool HV2NeedChange;
    
    #if PID_CTRL
    
    bool PidOpen;
    
    float OldOffSetVpp1;        //ƫ��
    float NowOffSetVpp1;
    uint16_t McuDacVpp1;
    
    float OldOffSetVnn1;        //ƫ��
    float NowOffSetVnn1;        //ƫ��
    uint16_t McuDacVnn1;

    #endif

    uint8_t  MinAdjVolCnt;      //΢������
      
    uint16_t Time;              //��ѹʱ��
    uint16_t TimeOut;           //��ѹ��ʱʱ��

    uint16_t T_VPP1;
    uint16_t T_VNN1;
    uint16_t T_VPP2;
    uint16_t T_VNN2;
    
    uint16_t Old_T_VPP1;
    uint16_t Old_T_VNN1;
    uint16_t Old_T_VPP2;
    uint16_t Old_T_VNN2;
    
    uint16_t MAX_VPP1;
    uint16_t MIN_VPP1;
    uint16_t MAX_VNN1;
    uint16_t MIN_VNN1;
    
    uint16_t MAX_VPP2;
    uint16_t MIN_VPP2;
    uint16_t MAX_VNN2;
    uint16_t MIN_VNN2;
    
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
}Ad_VolStruct;

typedef struct
{    
    bool    DebugMessage;                                                       //������Ϣ����
    
    uint8_t FPGA;
    uint8_t MCU;
}SysTemper;

typedef struct
{    
    bool     DebugMessage;                                                      //������Ϣ����
    
    uint16_t Rpm1;
    uint16_t Rpm2;
    uint16_t Rpm3;
    uint16_t Rpm4;
    uint16_t Rpm5;
}FanStrc;

typedef struct
{    
    bool            DebugMessage;                                               //������Ϣ����
    
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
    bool            WriteBoardOk_Send;      //д��Ӧ
    bool            BoardInfo_Send;         //����Ӧ
    uint8_t         Channel;                //����ͨ��, ��ָ������յ��������USB��ECCOM��DEBUGCOM�ĸ�ͨ������
}Command_Deal;

typedef struct
{    
    bool            DebugMessage;          //������Ϣ����    
    
    bool            Ac_Insert;                  //AC�����־
    bool            BatPak_Insert;              //��ذ������־
    bool            Bat1_Insert;
    bool            Bat2_Insert;
    uint8_t         Bat1_Power;                 //��ص���
    uint8_t         Bat2_Power;                 //��ص���
    uint8_t         Bat1_Tempature;             //����¶�
    uint8_t         Bat2_Tempature;             //����¶�
    uint8_t         Bat1_State;                 //��ع��ϱ�־
    uint8_t         Bat2_State;                 //��ع��ϱ�־
    
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
    
    bool            DebugMessage;            //������Ϣ����
}System_MsgStruct;

void Delay_Nop(uint16_t count);

bool System_PwrKey_Minitor(void);

bool System_S3_State_Minitor(void);

void SystemStateInit(void);

#endif
