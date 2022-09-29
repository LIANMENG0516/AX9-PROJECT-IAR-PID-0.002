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
    bool DebugMessage;                  //������Ϣ����
  
    bool HvFlag;
    bool CwFlag;

    bool RoughAdjVolCwOpen;             //CW�ֵ�����
    bool RoughAdjVolHv1Open;            //HV1�ֵ�����
    bool RoughAdjVolHv2Open;            //HV2�ֵ�����
      
    bool WaitRoughAdjVolResultCwOpen;   //CW�ֵ�����ȴ�����
    bool WaitRoughAdjVolResultHv1Open;  //HV1�ֵ�����ȴ�����
    bool WaitRoughAdjVolResultHv2Open;  //HV2�ֵ�����ȴ�����
      
    bool FineAdjVolCwOpen;              //CW΢������
    bool FineAdjVolHv1Open;             //HV1΢������
    bool FineAdjVolHv2Open;             //HV2΢������

    bool CwMinitorOpen;                 //CW��ѹ��ؿ��� 
    bool Hv1MinitorOpen;                //HV1��ѹ��ؿ���   
    bool Hv2MinitorOpen;                //HV2��ѹ��ؿ���

    bool CwTimerOpen;                   //CW��ʱ����
    bool Hv1TimerOpen;                  //HV1��ʱ����
    bool Hv2TimerOpen;                  //HV2��ʱ����
    
    bool TestTimerOpen;                 //���Լ�ʱ����

    uint8_t CwAdjVolCompleteFlag;       //CW��ѹ��ѹ��ɱ�־λ  0:��ѹ��� 1:��ѹæ 
    uint8_t Hv1AdjVolCompleteFlag;      //HV1��ѹ��ѹ��ɱ�־λ 0:��ѹ��� 1:��ѹæ
    uint8_t Hv2AdjVolCompleteFlag;      //HV2��ѹ��ѹ��ɱ�־λ 0:��ѹ��� 1:��ѹæ 
    
    uint8_t FineAdjVolCwCnt;            //CW΢������
    uint8_t FineAdjVolHv1Cnt;           //HV1΢������
    uint8_t FineAdjVolHv2Cnt;           //HV2΢������
    
    uint16_t CwTime;                    //��ѹʱ��
    uint16_t CwTimeOut;                 //��ѹ��ʱʱ��

    uint16_t Hv1Time;                   //��ѹʱ��
    uint16_t Hv1TimeOut;                //��ѹ��ʱʱ��
    
    uint16_t Hv2Time;                   //��ѹʱ��
    uint16_t Hv2TimeOut;                //��ѹ��ʱʱ��
    
    uint16_t TestTime;                  //��ѹʱ��
    uint16_t TestTimeOut;               //��ѹ��ʱʱ��

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
    
    float OldOffSetVpp1;                //ƫ��
    float NowOffSetVpp1;
    uint16_t McuDacVpp1;
    
    float OldOffSetVnn1;                //ƫ��
    float NowOffSetVnn1;                //ƫ��
    uint16_t McuDacVnn1;

    #endif
    
}Ad_VolStruct;

typedef struct
{    
    bool    DebugMessage;                                                       //������Ϣ����
    
    uint8_t FPGA;
    uint8_t AFE58;
    uint8_t CPU;
    uint8_t MCU;
    
}SysTemper;

typedef struct
{    
    bool     DebugMessage;                                                      //������Ϣ����
    
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
