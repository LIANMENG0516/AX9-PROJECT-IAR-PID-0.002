#include "power.h"

extern System_MsgStruct SysMsg;

void GetPowerRelatePara()
{
    SysMsg.PwrInfo.Ac_Insert = (SysMsg.AdjVol.R_INPUT > 1750 && SysMsg.AdjVol.R_INPUT <= 2000) ? TRUE : FALSE;                  //�����ѹ��17.5V~20Vʱ����ΪAC����������
    SysMsg.PwrInfo.BatPak_Insert = (SysMsg.AdjVol.R_INPUT > 1200 && SysMsg.AdjVol.R_INPUT <= 1750) ? TRUE : FALSE;              //�����ѹ��12V~17.5Vʱ����Ϊ��ذ�����  
    SysMsg.PwrInfo.Bat1_Insert = BAT1_INSERT_CHK() ? FALSE : TRUE;
    SysMsg.PwrInfo.Bat2_Insert = BAT2_INSERT_CHK() ? FALSE : TRUE;
}

uint8_t CheckBatteryState()
{
    uint8_t batState;
    
    batState = (BAT_STAT1() << 1) + BAT_STAT2();
    
    return batState;
}

void ChargeManagent()
{
    uint8_t batState;
    static uint16_t bat1ChargeRecoverCnt = 0, bat2ChargeRecoverCnt = 0;

    DEBUG_PRINTF(SysMsg.PwrInfo.DebugMessage, "SysMsg.PwrInfo.Bat1_Insert = %d \r\n", SysMsg.PwrInfo.Bat1_Insert);
    DEBUG_PRINTF(SysMsg.PwrInfo.DebugMessage, "SysMsg.PwrInfo.Bat1_Power = %d \r\n", SysMsg.PwrInfo.Bat1_Power);
    DEBUG_PRINTF(SysMsg.PwrInfo.DebugMessage, "SysMsg.PwrInfo.Bat1_Tempature = %d \r\n", SysMsg.PwrInfo.Bat1_Tempature);
    DEBUG_PRINTF(SysMsg.PwrInfo.DebugMessage, "SysMsg.PwrInfo.Bat1_State = %d \r\n", SysMsg.PwrInfo.Bat1_State);
    
    DEBUG_PRINTF(SysMsg.PwrInfo.DebugMessage, "SysMsg.PwrInfo.Bat2_Insert = %d \r\n", SysMsg.PwrInfo.Bat2_Insert);
    DEBUG_PRINTF(SysMsg.PwrInfo.DebugMessage, "SysMsg.PwrInfo.Bat2_Power = %d \r\n", SysMsg.PwrInfo.Bat2_Power);
    DEBUG_PRINTF(SysMsg.PwrInfo.DebugMessage, "SysMsg.PwrInfo.Bat2_Tempature = %d \r\n", SysMsg.PwrInfo.Bat2_Tempature);
    DEBUG_PRINTF(SysMsg.PwrInfo.DebugMessage, "SysMsg.PwrInfo.Bat2_State = %d \r\n", SysMsg.PwrInfo.Bat2_State);
    
    batState = CheckBatteryState();

    if(SysMsg.PwrInfo.Bat1_Insert == FALSE)
    {
        SysMsg.PwrInfo.Bat1_Power = 0;
        SysMsg.PwrInfo.Bat1_Tempature = 0;
        SysMsg.PwrInfo.Bat1_State = BAT_STATE_ERROR;
        bat1ChargeRecoverCnt = 0;
        BAT1_C_SHIFT_EN(0);
    }
    
    if(SysMsg.PwrInfo.Bat2_Insert == FALSE)
    {
        SysMsg.PwrInfo.Bat2_Power = 0;
        SysMsg.PwrInfo.Bat2_Tempature = 0;
        SysMsg.PwrInfo.Bat2_State = BAT_STATE_ERROR;
        bat2ChargeRecoverCnt = 0;
        BAT2_C_SHIFT_EN(0);
    }
    
    if(SysMsg.PwrInfo.Ac_Insert == TRUE)
    {
        if(SysMsg.PwrInfo.Bat1_Insert == TRUE || SysMsg.PwrInfo.Bat2_Insert == TRUE)
        {
            if(SysMsg.PwrInfo.Bat1_Power != 100 || SysMsg.PwrInfo.Bat1_State == BAT_STATE_CHARGE)           //���1���ڳ��
            {
                BAT2_C_SHIFT_EN(0);
                
                if(SysMsg.PwrInfo.Bat1_Power == 100)
                {
                    if(batState == BAT_STATE_FULL || batState == BAT_STATE_ERROR)
                    {
                        CHARGE_EN(0);
                        CHARGE_CTL(0);
                        BAT1_C_SHIFT_EN(0);
                        SysMsg.PwrInfo.Bat1_State = BAT_STATE_FULL;
                    }
                }
                else if(SysMsg.PwrInfo.Bat1_Power != 100 && batState == BAT_STATE_ERROR)
                {
                    if(++bat1ChargeRecoverCnt >= 100)
                    {
                        CHARGE_EN(0);
                        CHARGE_CTL(0);
                        BAT1_C_SHIFT_EN(0);
                        SysMsg.PwrInfo.Bat1_State = BAT_STATE_ERROR;
                    }
                    else
                    {
                        CHARGE_EN(1);
                        if(SysMsg.SystemState == SYSTEM_ON)
                        {
                            CHARGE_CTL(0);
                        }
                        else
                        {
                            CHARGE_CTL(1);
                        }
                        BAT1_C_SHIFT_EN(1);
                        SysMsg.PwrInfo.Bat1_State = BAT_STATE_CHARGE;
                    }
                }
                else if(SysMsg.PwrInfo.Bat1_Power != 100 && batState == BAT_STATE_CHARGE)
                {
                    CHARGE_EN(1);
                    if(SysMsg.SystemState == SYSTEM_ON)
                    {
                        CHARGE_CTL(0);
                    }
                    else
                    {
                        CHARGE_CTL(1);
                    }
                    BAT1_C_SHIFT_EN(1);
                    SysMsg.PwrInfo.Bat1_State = BAT_STATE_CHARGE;
                }
                else
                {
                    CHARGE_EN(0);
                    CHARGE_CTL(0);
                    BAT1_C_SHIFT_EN(0);
                    SysMsg.PwrInfo.Bat1_State = BAT_STATE_ERROR;
                }
            }
            else
            {
                BAT1_C_SHIFT_EN(0);                                                                         
                
                if(SysMsg.PwrInfo.Bat2_Power == 100)
                {
                    if(batState == BAT_STATE_FULL || batState == BAT_STATE_ERROR)
                    {
                        CHARGE_EN(0);
                        CHARGE_CTL(0);
                        BAT2_C_SHIFT_EN(0);
                        SysMsg.PwrInfo.Bat2_State = BAT_STATE_FULL;
                        bat2ChargeRecoverCnt = 0;
                    }
                }
                else if(SysMsg.PwrInfo.Bat2_Power != 100 && batState == BAT_STATE_ERROR)
                {
                    if(++bat2ChargeRecoverCnt >= 100)
                    {
                        CHARGE_EN(0);
                        CHARGE_CTL(0);
                        BAT2_C_SHIFT_EN(0);
                        SysMsg.PwrInfo.Bat2_State = BAT_STATE_ERROR;
                    }
                    else
                    {
                        CHARGE_EN(1);
                        if(SysMsg.SystemState == SYSTEM_ON)
                        {
                            CHARGE_CTL(0);
                        }
                        else
                        {
                            CHARGE_CTL(1);
                        }
                        BAT2_C_SHIFT_EN(1);
                        SysMsg.PwrInfo.Bat2_State = BAT_STATE_CHARGE;
                    }
                }
                else if(SysMsg.PwrInfo.Bat2_Power != 100 && batState == BAT_STATE_CHARGE)
                {
                    CHARGE_EN(1);
                    if(SysMsg.SystemState == SYSTEM_ON)
                    {
                        CHARGE_CTL(0);
                    }
                    else
                    {
                        CHARGE_CTL(1);
                    }
                    BAT2_C_SHIFT_EN(1);
                    SysMsg.PwrInfo.Bat2_State = BAT_STATE_CHARGE;
                    bat2ChargeRecoverCnt = 0;
                }
                else
                {
                    CHARGE_EN(0);
                    CHARGE_CTL(0);
                    BAT2_C_SHIFT_EN(0);
                    SysMsg.PwrInfo.Bat2_State = BAT_STATE_ERROR;
                    bat2ChargeRecoverCnt = 0;
                }
            }
        }
    }
    else
    {
        SysMsg.PwrInfo.Bat1_State = BAT_STATE_ERROR;
        SysMsg.PwrInfo.Bat2_State = BAT_STATE_ERROR;
        bat1ChargeRecoverCnt = 0;
        bat2ChargeRecoverCnt = 0;
        BAT1_C_SHIFT_EN(0);
        BAT2_C_SHIFT_EN(0);
        CHARGE_CTL(0);
        CHARGE_EN(0);
    }
}



