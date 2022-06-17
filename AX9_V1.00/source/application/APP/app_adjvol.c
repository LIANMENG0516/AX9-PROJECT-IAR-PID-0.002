#include "app_adjvol.h"

OS_TCB AdjVolTcb;

CPU_STK App_AdjVol_Task_Stk[APP_ADJVOL_STK_SIZE];

OS_CPU_EXT __ALIGN_BEGIN uint8_t USB_Tx_Buffer[CDC_DATA_MAX_PACKET_SIZE] __ALIGN_END;
OS_CPU_EXT CDC_IF_Prop_TypeDef VCP_fops;

extern System_MsgStruct SysMsg;
extern CmdFrameStr SenFrameCmd;
extern Com_Buffer DebugComTX;

void AdjVol_Result_Send()
{
    SenFrameCmd.Cid = CMD_ADJUSTVOLTAGE_HV;
    SenFrameCmd.Len = 8;
    
    SenFrameCmd.Data[0] = SysMsg.AdjVol.R_VPP1 >> 8;
    SenFrameCmd.Data[1] = SysMsg.AdjVol.R_VPP1;
    SenFrameCmd.Data[2] = SysMsg.AdjVol.R_VNN1 >> 8;
    SenFrameCmd.Data[3] = SysMsg.AdjVol.R_VNN1;
    SenFrameCmd.Data[4] = SysMsg.AdjVol.R_VPP2 >> 8;
    SenFrameCmd.Data[5] = SysMsg.AdjVol.R_VPP2;
    SenFrameCmd.Data[6] = SysMsg.AdjVol.R_VNN2 >> 8;
    SenFrameCmd.Data[7] = SysMsg.AdjVol.R_VNN2;

    if(SysMsg.Cmd.Channel == USB_CHANNEL)
    {
        FrameCmdPackage(USB_Tx_Buffer);
        VCP_fops.pIf_DataTx(USB_Tx_Buffer, (USB_Tx_Buffer[3] + 6));
    }
}

void Calc_TarVol_AlowRange()
{    
    SysMsg.AdjVol.MAX_VPP1 = SysMsg.AdjVol.T_VPP1 + 100;
    SysMsg.AdjVol.MIN_VPP1 = SysMsg.AdjVol.T_VPP1 - 100;
    SysMsg.AdjVol.MAX_VNN1 = SysMsg.AdjVol.T_VPP1 + 100;
    SysMsg.AdjVol.MIN_VNN1 = SysMsg.AdjVol.T_VPP1 - 100;
    
    if(SysMsg.AdjVol.HvFlag == TRUE)
    {
        SysMsg.AdjVol.MAX_VPP2 = SysMsg.AdjVol.T_VPP2 + 100;
        SysMsg.AdjVol.MIN_VPP2 = SysMsg.AdjVol.T_VPP2 - 100;
        SysMsg.AdjVol.MAX_VNN2 = SysMsg.AdjVol.T_VPP2 + 100;
        SysMsg.AdjVol.MIN_VNN2 = SysMsg.AdjVol.T_VPP2 - 100;
    }
    
    if(SysMsg.AdjVol.CwFlag == TRUE)
    {
        SysMsg.AdjVol.MAX_VPP2 = SysMsg.AdjVol.T_VPP2 + 100;
        SysMsg.AdjVol.MIN_VPP2 = SysMsg.AdjVol.T_VPP2 - 100;
        SysMsg.AdjVol.MAX_VNN2 = SysMsg.AdjVol.T_VNN2 + 100;
        SysMsg.AdjVol.MIN_VNN2 = SysMsg.AdjVol.T_VNN2 - 100;
    }
}

uint16_t Step_HvAdjVol_Calcuation(uint16_t Target, uint16_t Precent, u8 DacState)       //������ѹֵ����
{
    uint16_t temp = 0, stepUp = 0, stepDown = 0;
    
    if(DacState == MCU_DAC)                                                             //Ƭ��MCU_DAC���ڲ���ֵ
    {
        stepUp = STEP_DACMCU_UP;
        stepDown = STEP_DACMCU_DOWN;
    }
    else                                                                                //Ƭ��SPI_DAC���ڲ���ֵ
    {
        stepUp = STEP_SPIMCU_UP;
        stepDown = STEP_SPIMCU_DOWN;
    }
  
    if(Target > Precent)
    {
        if(Target - Precent > stepUp)  
        {
            temp = Precent + stepUp;
        }
        else
        {
            temp = Target;
        }
    }
    else if(Precent > Target)
    {
        if(Precent - Target > stepDown)
        {
            temp = Precent - stepDown;
        }
        else
        {
            temp = Target;
        }
    }
    else
    {
        temp = Target;
    }

    return temp;
}



void Pid_AdjVolHv(uint8_t *buffer)
{
    SysMsg.AdjVol.T_VPP1 = (buffer[0] << 8) | buffer[1];                                                    //��ȡĿ���ѹ
    SysMsg.AdjVol.T_VNN1 = (buffer[2] << 8) | buffer[3];
    SysMsg.AdjVol.T_VPP2 = (buffer[4] << 8) | buffer[5];
    SysMsg.AdjVol.T_VNN2 = (buffer[6] << 8) | buffer[7];
}

void Get_AdjHvMsg(uint8_t *buffer)
{      
    SysMsg.AdjVol.T_VPP1 = (buffer[0] << 8) | buffer[1];                                                    //��ȡĿ���ѹ
    SysMsg.AdjVol.T_VNN1 = (buffer[2] << 8) | buffer[3];
    SysMsg.AdjVol.T_VPP2 = (buffer[4] << 8) | buffer[5];
    SysMsg.AdjVol.T_VNN2 = (buffer[6] << 8) | buffer[7];
    
    if(SysMsg.AdjVol.T_VPP1 <= HIGHSET_HV1 && SysMsg.AdjVol.T_VPP1 >= LOOWSET_HV1 &&                        //�������ѹ��Χ֮��
       SysMsg.AdjVol.T_VNN1 <= HIGHSET_HV1 && SysMsg.AdjVol.T_VNN1 >= LOOWSET_HV1 && 
       SysMsg.AdjVol.T_VPP2 <= HIGHSET_HV2 && SysMsg.AdjVol.T_VPP2 >= LOOWSET_HV2 && 
       SysMsg.AdjVol.T_VNN2 <= HIGHSET_HV2 && SysMsg.AdjVol.T_VNN2 >= LOOWSET_HV2 )
    {
        SysMsg.AdjVol.HV1NeedChange = TRUE;     
        SysMsg.AdjVol.HV2NeedChange = TRUE;     
        
        if(SysMsg.AdjVol.HV1NeedChange == TRUE || SysMsg.AdjVol.HV2NeedChange == TRUE)
        {
            if((SysMsg.AdjVol.T_VPP1 >= SysMsg.AdjVol.Old_T_VPP1 && SysMsg.AdjVol.T_VNN1 >= SysMsg.AdjVol.Old_T_VNN1) ||        //����ѹ�ж�           
               (SysMsg.AdjVol.T_VPP2 >= SysMsg.AdjVol.Old_T_VPP2 && SysMsg.AdjVol.T_VNN2 >= SysMsg.AdjVol.Old_T_VNN2)  )
            {
                DEBUG_PRINTF(SysMsg.AdjVol.DebugMessage, "Up Vol \r\n");            
                SysMsg.AdjVol.TimeOut = HV_CHANGE_UP_TIMEOUT;                                                                    //���ε�ѹΪ��ѹ
            }
            else
            {
                DEBUG_PRINTF(SysMsg.AdjVol.DebugMessage, "Down Vol \r\n");
                SysMsg.AdjVol.TimeOut = HV_CHANGE_DOWN_TIMEOUT;                                                                  //���ε�ѹΪ��ѹ
            }
            
            SysMsg.AdjVol.Old_T_VPP1 = SysMsg.AdjVol.T_VPP1;    
            SysMsg.AdjVol.Old_T_VNN1 = SysMsg.AdjVol.T_VNN1; 
            SysMsg.AdjVol.Old_T_VPP2 = SysMsg.AdjVol.T_VPP2;    
            SysMsg.AdjVol.Old_T_VNN2 = SysMsg.AdjVol.T_VNN2;
            
            Calc_TarVol_AlowRange();                                                                                             //�������������ѹ��Χ
        
            #if SWITCH_ADJVOL_MODULE
            
            CTL_VPP1_VNN1_EN(1);                                                                                                 //�򿪸�ѹ���
            CTL_VPP2_VNN2_EN(1);
            
            SysMsg.AdjVol.T_McuDacHv1 = Vpp_Calculate_AdjVol(SysMsg.AdjVol.T_VPP1);                                              //����Ҫ���ڵ�Ŀ���ѹʱ, Ŀ��DAC��ֵ
            SysMsg.AdjVol.T_SpiDacHv1 = Vnn_Calculate_AdjVol(SysMsg.AdjVol.T_VNN1);
            SysMsg.AdjVol.T_McuDacHv2 = Vpp_Calculate_AdjVol(SysMsg.AdjVol.T_VPP2);                
            SysMsg.AdjVol.T_SpiDacHv2 = Vnn_Calculate_AdjVol(SysMsg.AdjVol.T_VNN2);
                            
            while(SysMsg.AdjVol.HV1NeedChange == TRUE || SysMsg.AdjVol.HV2NeedChange == TRUE)
            {
                if(SysMsg.AdjVol.HV1NeedChange == TRUE)
                {
                    SysMsg.AdjVol.P_McuDacHv1 = Step_HvAdjVol_Calcuation(SysMsg.AdjVol.T_McuDacHv1, SysMsg.AdjVol.P_McuDacHv1, MCU_DAC);  
                    SysMsg.AdjVol.P_SpiDacHv1 = Step_HvAdjVol_Calcuation(SysMsg.AdjVol.T_SpiDacHv1, SysMsg.AdjVol.P_SpiDacHv1, SPI_DAC);  
                  
                    DAC_SetChannel1Data(DAC_Align_12b_R, SysMsg.AdjVol.P_McuDacHv1);                                                //����VPP1��Ŀ��ֵ
                    DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);                                                                  //�������DACת��
                    
                    DacHv_Tlv5626cd_ValueSet(SysMsg.AdjVol.P_SpiDacHv1, SysMsg.AdjVol.T_SpiDacHv2);                                 //����VNN1ת��

                    if(SysMsg.AdjVol.P_McuDacHv1 == SysMsg.AdjVol.T_McuDacHv1 && SysMsg.AdjVol.P_SpiDacHv1 == SysMsg.AdjVol.T_SpiDacHv1)                                    //������ɣ�������Ҫ����
                    {
                        SysMsg.AdjVol.HV1NeedChange = FALSE;
                    }
                }
                
                if(SysMsg.AdjVol.HV2NeedChange == TRUE)
                {
                    SysMsg.AdjVol.P_McuDacHv2 = Step_HvAdjVol_Calcuation(SysMsg.AdjVol.T_McuDacHv2, SysMsg.AdjVol.P_McuDacHv2, MCU_DAC);  
                    SysMsg.AdjVol.P_SpiDacHv2 = Step_HvAdjVol_Calcuation(SysMsg.AdjVol.T_SpiDacHv2, SysMsg.AdjVol.P_SpiDacHv2, SPI_DAC);
                
                    DAC_SetChannel2Data(DAC_Align_12b_R, SysMsg.AdjVol.T_McuDacHv2);                                                //����VPP2��Ŀ��ֵ
                    DAC_SoftwareTriggerCmd(DAC_Channel_2, ENABLE);                                                                  //�������DACת��
                    
                    DacHv_Tlv5626cd_ValueSet(SysMsg.AdjVol.P_SpiDacHv1, SysMsg.AdjVol.T_SpiDacHv2);                                 //����VNN2ת��

                    if(SysMsg.AdjVol.P_McuDacHv2 == SysMsg.AdjVol.T_McuDacHv2 && SysMsg.AdjVol.P_SpiDacHv2 == SysMsg.AdjVol.T_SpiDacHv2)                                    //������ɣ�������Ҫ����
                    {
                        SysMsg.AdjVol.HV2NeedChange = FALSE;
                    }
                }
            }       
            
            #else
             
            Adjust_Voltage_HV();                                                //ִ�и�ѹ��ѹ����, �õ�ѹ����ΪӲ��һ���Ե�ѹ
            
            #endif

            SysMsg.AdjVol.AdjVolOpen = TRUE;                                    //��ѹ����
            SysMsg.AdjVol.VolMinitor = FALSE;                                   //�رռ��
            SysMsg.AdjVol.MinAdjVolCnt = 0;                                     //΢������
        } 
    }
    else
    {
                    //�����쳣�رո�ѹ
                    //�رո�ѹ
    
    
    }
    
}

void Get_AdjCwMsg(uint8_t *buffer)
{
    SysMsg.AdjVol.T_VPP1 = (buffer[0] << 8) | buffer[1];
    SysMsg.AdjVol.T_VNN1 = (buffer[2] << 8) | buffer[3];
    SysMsg.AdjVol.T_VPP2 = (buffer[4] << 8) | buffer[5];
    SysMsg.AdjVol.T_VNN2 = (buffer[6] << 8) | buffer[7];
    
    if(SysMsg.AdjVol.T_VPP1 <= HIGHSET_HV1 && SysMsg.AdjVol.T_VPP1 >= LOOWSET_HV1 &&                                            //�������ѹ��Χ֮��
       SysMsg.AdjVol.T_VNN1 <= HIGHSET_HV1 && SysMsg.AdjVol.T_VNN1 >= LOOWSET_HV1 && 
       SysMsg.AdjVol.T_VPP2 <= HIGHSET_CW  && SysMsg.AdjVol.T_VPP2 >= LOOWSET_CW  && 
       SysMsg.AdjVol.T_VNN2 <= HIGHSET_CW  && SysMsg.AdjVol.T_VNN2 >= LOOWSET_CW  )
    {
        if(SysMsg.AdjVol.T_VPP1 != SysMsg.AdjVol.Old_T_VPP1 || SysMsg.AdjVol.T_VNN1 != SysMsg.AdjVol.Old_T_VNN1)                //���ε�ѹĿ��ֵ���ϴβ�ͬ
        {
            SysMsg.AdjVol.HV1NeedChange = TRUE;                                                                                //HV1��Ҫ��ѹ
        }
        else
        {
            SysMsg.AdjVol.HV1NeedChange = FALSE; 
        }
        
        if(SysMsg.AdjVol.T_VPP2 != SysMsg.AdjVol.Old_T_VPP2 || SysMsg.AdjVol.T_VNN2 != SysMsg.AdjVol.Old_T_VNN2)                //���ε�ѹĿ��ֵ���ϴβ�ͬ
        {
            SysMsg.AdjVol.HV2NeedChange = TRUE;                                                                                 //HV2��Ҫ��ѹ
        }
        else
        {
            SysMsg.AdjVol.HV2NeedChange = FALSE;
        }
        
        SysMsg.AdjVol.HV1NeedChange = TRUE;     //DEBUG
        SysMsg.AdjVol.HV2NeedChange = TRUE;     //DEBUG
    
        if(SysMsg.AdjVol.HV1NeedChange == TRUE || SysMsg.AdjVol.HV2NeedChange == TRUE)
        {
            if((SysMsg.AdjVol.T_VPP1 > SysMsg.AdjVol.Old_T_VPP1 && SysMsg.AdjVol.T_VNN1 > SysMsg.AdjVol.Old_T_VNN1) ||           //����ѹ�ж�           
               (SysMsg.AdjVol.T_VPP2 > SysMsg.AdjVol.Old_T_VPP2 && SysMsg.AdjVol.T_VNN2 > SysMsg.AdjVol.Old_T_VNN2) )
            {
                DEBUG_PRINTF(SysMsg.AdjVol.DebugMessage, "Up Vol \r\n");            
                SysMsg.AdjVol.TimeOut = HV_CHANGE_UP_TIMEOUT;                                                                    //���ε�ѹΪ��ѹ
            }
            else if(SysMsg.AdjVol.T_VPP1 == SysMsg.AdjVol.Old_T_VPP1 && SysMsg.AdjVol.T_VNN1 == SysMsg.AdjVol.Old_T_VNN1 &&      //����ѹ�ж�           
                    SysMsg.AdjVol.T_VPP2 == SysMsg.AdjVol.Old_T_VPP2 && SysMsg.AdjVol.T_VNN2 == SysMsg.AdjVol.Old_T_VNN2 )
            {
                DEBUG_PRINTF(SysMsg.AdjVol.DebugMessage, "Equal Vol \r\n");            
            }
            else
            {
                DEBUG_PRINTF(SysMsg.AdjVol.DebugMessage, "Down Vol \r\n");
                SysMsg.AdjVol.TimeOut = HV_CHANGE_DOWN_TIMEOUT;                                                                   //���ε�ѹΪ��ѹ
            }
            
            SysMsg.AdjVol.Old_T_VPP1 = SysMsg.AdjVol.T_VPP1;    
            SysMsg.AdjVol.Old_T_VNN1 = SysMsg.AdjVol.T_VNN1; 
            SysMsg.AdjVol.Old_T_VPP2 = SysMsg.AdjVol.T_VPP2;    
            SysMsg.AdjVol.Old_T_VNN2 = SysMsg.AdjVol.T_VNN2;
            
            Calc_TarVol_AlowRange();                                                                                                //�������������Χ
            
            SysMsg.AdjVol.P_McuDacHv1 = SysMsg.AdjVol.T_McuDacHv1 = Vpp_Calculate_AdjVol(SysMsg.AdjVol.T_VPP1);                                                  //����Ҫ���ڵ�Ŀ���ѹʱ, Ŀ��DAC��ֵ
            SysMsg.AdjVol.P_SpiDacHv1 = SysMsg.AdjVol.T_SpiDacHv1 = Vnn_Calculate_AdjVol(SysMsg.AdjVol.T_VNN1);
            SysMsg.AdjVol.P_SpiDacPcw = SysMsg.AdjVol.T_SpiDacPcw = Pcw_Calculate_AdjVol(SysMsg.AdjVol.T_VPP2);
            SysMsg.AdjVol.P_SpiDacNcw = SysMsg.AdjVol.T_SpiDacNcw = Ncw_Calculate_AdjVol(SysMsg.AdjVol.T_VNN2);
            
            
        }
        
        Adjust_Voltage_CW();                                                    //ִ�е�ѹ��ѹ����
        DEBUG_PRINTF(SysMsg.AdjVol.DebugMessage, "DacVol Target : %d %d %d %d \r\n", SysMsg.AdjVol.T_McuDacHv1, SysMsg.AdjVol.T_SpiDacHv1, SysMsg.AdjVol.T_SpiDacPcw, SysMsg.AdjVol.T_SpiDacNcw);  
      
        SysMsg.AdjVol.AdjVolOpen = TRUE;                                        //��ѹ����
        SysMsg.AdjVol.VolMinitor = FALSE;        
        SysMsg.AdjVol.MinAdjVolCnt = 0;                                         //΢������
    }
    else
    {   
                    //�����쳣
                    //�رո�ѹ
    }
}

void App_AdjVol_Task()
{
    OS_ERR err;

    while(1)
    {	
      
        if(SysMsg.AdjVol.MinAdjVolOpen)                                         //΢������                                 
        {
            if(++SysMsg.AdjVol.MinAdjVolCnt >= 20)
            {
                DEBUG_PRINTF(SysMsg.AdjVol.DebugMessage, "MinAdjVol %d Times - SysMsg.AdjVol.Time = %d - MinAdjVol Finish : %d %d %d %d \r\n", SysMsg.AdjVol.MinAdjVolCnt, SysMsg.AdjVol.Time, SysMsg.AdjVol.R_VPP1, SysMsg.AdjVol.R_VNN1, SysMsg.AdjVol.R_VPP2, SysMsg.AdjVol.R_VNN2);            
                DEBUG_PRINTF(SysMsg.AdjVol.DebugMessage, "MinAdjVol Finish \r\n"); 
                
                SysMsg.AdjVol.Time = 0; 
                SysMsg.AdjVol.TimeFlag = FALSE;                                 //�رռ�ʱ  
                SysMsg.AdjVol.MinAdjVolCnt = 51;
                SysMsg.AdjVol.MinAdjVolOpen = FALSE;                            //΢������
                SysMsg.AdjVol.VolMinitor = TRUE;                                //�������
            } 
            else
            {
                if(abs(SysMsg.AdjVol.R_VPP1 - SysMsg.AdjVol.T_VPP1) > RNAGE_MIN_VOL)           
                {
                    int16_t DesVol;
                    
                    DesVol = SysMsg.AdjVol.R_VPP1 - SysMsg.AdjVol.T_VPP1;
                    
                    if(DesVol > 0)
                    {
                        if(SysMsg.AdjVol.P_McuDacHv1 + 20 > 4095)
                        {
                            SysMsg.AdjVol.P_McuDacHv1 = 4095;
                        }
                        else
                        {
                            if(DesVol > 30)
                            {
                                SysMsg.AdjVol.P_McuDacHv1 += 10; 
                            }
                            else
                            {
                                SysMsg.AdjVol.P_McuDacHv1 += 5; 
                            }
                        }

                        DAC_SetChannel1Data(DAC_Align_12b_R, SysMsg.AdjVol.P_McuDacHv1);                 //����VPP1
                        DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);                                   //�������DACת��
                    }
                    
                    if(DesVol < 0)
                    {                      
                        if(SysMsg.AdjVol.P_McuDacHv1 < 20)
                        {
                            SysMsg.AdjVol.P_McuDacHv1 = 0;
                        }
                        else
                        {
                            if(DesVol < -30)
                            {
                                SysMsg.AdjVol.P_McuDacHv1 -= 10; 
                            }
                            else
                            {
                                SysMsg.AdjVol.P_McuDacHv1 -= 5; 
                            }
                        }
                        
                        DAC_SetChannel1Data(DAC_Align_12b_R, SysMsg.AdjVol.P_McuDacHv1);                 //����VPP1
                        DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);                                   //�������DACת��
                    }           
                }
                
                if(abs(SysMsg.AdjVol.R_VNN1 - SysMsg.AdjVol.T_VNN1) > RNAGE_MIN_VOL)           
                {
                    int16_t DesVol;
                    
                    DesVol = SysMsg.AdjVol.R_VNN1 - SysMsg.AdjVol.T_VNN1;
                    
                    if(DesVol > 0)
                    {
                        if(SysMsg.AdjVol.P_SpiDacHv1 + 3 > 255)
                        {
                            SysMsg.AdjVol.P_SpiDacHv1 = 255;
                        }
                        else
                        {
                            if(DesVol > 30)
                            {
                                SysMsg.AdjVol.P_SpiDacHv1 += 2; 
                            }
                            else
                            {
                                SysMsg.AdjVol.P_SpiDacHv1 += 1; 
                            }
                        }
                 
                        DacHv_Tlv5626cd_ValueSet(SysMsg.AdjVol.P_SpiDacHv1, SysMsg.AdjVol.P_SpiDacHv2);
                    }
                    if(DesVol < 0)
                    {
                        if(SysMsg.AdjVol.P_SpiDacHv1 < 3)
                        {
                            SysMsg.AdjVol.P_SpiDacHv1 = 0;
                        }
                        else
                        {                    
                            if(DesVol < -30)
                            {
                                SysMsg.AdjVol.P_SpiDacHv1 -= 2; 
                            }
                            else
                            {
                                SysMsg.AdjVol.P_SpiDacHv1 -= 1; 
                            }
                        }

                        DacHv_Tlv5626cd_ValueSet(SysMsg.AdjVol.P_SpiDacHv1, SysMsg.AdjVol.P_SpiDacHv2);
                    }
                }
                
                if(SysMsg.AdjVol.HvFlag)
                {                
                    if(abs(SysMsg.AdjVol.R_VPP2 - SysMsg.AdjVol.T_VPP2) > RNAGE_MIN_VOL)           
                    {
                        int16_t DesVol;
                        
                        DesVol = SysMsg.AdjVol.R_VPP2 - SysMsg.AdjVol.T_VPP2;
                        
                        if(DesVol > 0)
                        {
                            if(SysMsg.AdjVol.P_McuDacHv2 + 20 > 4095)
                            {
                                SysMsg.AdjVol.P_McuDacHv2 = 4095;
                            }
                            else
                            {
                                if(DesVol > 30)
                                {
                                    SysMsg.AdjVol.P_McuDacHv2 += 10; 
                                }
                                else
                                {
                                    SysMsg.AdjVol.P_McuDacHv2 += 5; 
                                }
                            }

                            DAC_SetChannel2Data(DAC_Align_12b_R, SysMsg.AdjVol.P_McuDacHv2);                   //����VPP2
                            DAC_SoftwareTriggerCmd(DAC_Channel_2, ENABLE);
                        }
                        
                        if(DesVol < 0)
                        {
                            if(SysMsg.AdjVol.P_McuDacHv2 < 20)
                            {
                                SysMsg.AdjVol.P_McuDacHv2 = 0;
                            }
                            else
                            {
                                if(DesVol < -30)
                                {
                                    SysMsg.AdjVol.P_McuDacHv2 -= 10; 
                                }
                                else
                                {
                                    SysMsg.AdjVol.P_McuDacHv2 -= 5; 
                                }
                            }
                        
                            DAC_SetChannel2Data(DAC_Align_12b_R, SysMsg.AdjVol.P_McuDacHv2);                   //����VPP2
                            DAC_SoftwareTriggerCmd(DAC_Channel_2, ENABLE);
                        }
                    }

                    if(abs(SysMsg.AdjVol.R_VNN2 - SysMsg.AdjVol.T_VNN2) > RNAGE_MIN_VOL)           
                    {
                        int16_t DesVol;
                        
                        DesVol = SysMsg.AdjVol.R_VNN2 - SysMsg.AdjVol.T_VNN2;

                        if(DesVol > 0)
                        {                            
                            if(SysMsg.AdjVol.P_SpiDacHv2 + 3 > 255)
                            {
                                SysMsg.AdjVol.P_SpiDacHv2 = 255;
                            }
                            else
                            {
                                if(DesVol > 30)
                                {
                                    SysMsg.AdjVol.P_SpiDacHv2 += 2; 
                                }
                                else
                                {
                                    SysMsg.AdjVol.P_SpiDacHv2 += 1; 
                                }
                            }
        
                            DacHv_Tlv5626cd_ValueSet(SysMsg.AdjVol.P_SpiDacHv1, SysMsg.AdjVol.P_SpiDacHv2);
                        }
                        if(DesVol < 0)
                        {
                            if(SysMsg.AdjVol.P_SpiDacHv2 < 3)
                            {
                                SysMsg.AdjVol.P_SpiDacHv2 = 0;
                            }
                            else
                            {
                                if(DesVol < -30)
                                {
                                    SysMsg.AdjVol.P_SpiDacHv2 -= 2; 
                                }
                                else
                                {
                                    SysMsg.AdjVol.P_SpiDacHv2 -= 1; 
                                }
                            }
           
                            DacHv_Tlv5626cd_ValueSet(SysMsg.AdjVol.P_SpiDacHv1, SysMsg.AdjVol.P_SpiDacHv2);
                        }
                    }
                }
                
#if MINICWVOL
                if(SysMsg.AdjVol.CwFlag)
                {
                    if(abs(SysMsg.AdjVol.R_VPP2 - SysMsg.AdjVol.T_VPP2) > RNAGE_MIN_VOL)           
                    {
                        int16_t DesVol;
                        
                        DesVol = SysMsg.AdjVol.R_VPP2 - SysMsg.AdjVol.T_VPP2;
                        
                        if(DesVol > 0)
                        {
                            if(SysMsg.AdjVol.P_SpiDacPcw + 3 > 255)
                            {
                                SysMsg.AdjVol.P_SpiDacPcw = 255;
                            }
                            else
                            {
                                SysMsg.AdjVol.P_SpiDacPcw += 1;                         //0.3V���ҵĵ���   
                            }
                          
                            DacCw_Tlv5626cd_ValueSet(SysMsg.AdjVol.P_SpiDacPcw, SysMsg.AdjVol.P_SpiDacNcw);
                        }
                        
                        if(DesVol < 0)
                        {
                            if(SysMsg.AdjVol.P_SpiDacNcw < 3)
                            {
                                SysMsg.AdjVol.P_SpiDacNcw = 0;
                            }
                            else
                            {
                                SysMsg.AdjVol.P_SpiDacNcw -= 1;                         //0.3V���ҵĵ��� 
                            }
                        
                            DacCw_Tlv5626cd_ValueSet(SysMsg.AdjVol.P_SpiDacPcw, SysMsg.AdjVol.P_SpiDacNcw);
                        }
                    }
                    
                    if(abs(SysMsg.AdjVol.R_VNN2 - SysMsg.AdjVol.T_VNN2) > RNAGE_MIN_VOL)           
                    {
                        int16_t DesVol;
                        
                        DesVol = SysMsg.AdjVol.R_VNN2 - SysMsg.AdjVol.T_VNN2;
                        
                        if(DesVol > 0)
                        {
                            SysMsg.AdjVol.P_SpiDacNcw = SysMsg.AdjVol.P_SpiDacNcw + 1;                          
                            DacCw_Tlv5626cd_ValueSet(SysMsg.AdjVol.P_SpiDacPcw, SysMsg.AdjVol.P_SpiDacNcw);
                        }
                        if(DesVol < 0)
                        {
                            SysMsg.AdjVol.P_SpiDacNcw = SysMsg.AdjVol.P_SpiDacNcw - 1;                          
                            DacCw_Tlv5626cd_ValueSet(SysMsg.AdjVol.P_SpiDacPcw, SysMsg.AdjVol.P_SpiDacNcw);
                        }
                    }
                }
#endif
                    
                OSTimeDlyHMSM(0, 0, 0, 80, OS_OPT_TIME_PERIODIC, &err);                         //�ȴ���ѹ�ȶ�
                
                if(SysMsg.AdjVol.R_VPP1 >= SysMsg.AdjVol.MIN_VPP1 && SysMsg.AdjVol.R_VPP1 <= SysMsg.AdjVol.MAX_VPP1 &&
                   SysMsg.AdjVol.R_VNN1 >= SysMsg.AdjVol.MIN_VNN1 && SysMsg.AdjVol.R_VNN1 <= SysMsg.AdjVol.MAX_VNN1 &&
                   SysMsg.AdjVol.R_VPP2 >= SysMsg.AdjVol.MIN_VPP2 && SysMsg.AdjVol.R_VPP2 <= SysMsg.AdjVol.MAX_VPP2 &&
                   SysMsg.AdjVol.R_VNN2 >= SysMsg.AdjVol.MIN_VNN2 && SysMsg.AdjVol.R_VNN2 <= SysMsg.AdjVol.MAX_VNN2 )  
                {
                    AdjVol_Result_Send();                                                       //�ϴ���ѹ 
                    DEBUG_PRINTF(SysMsg.AdjVol.DebugMessage, "MinAdjVol %d Times - SysMsg.AdjVol.Time = %d - MinAdjVol Success : %d %d %d %d \r\n", SysMsg.AdjVol.MinAdjVolCnt, SysMsg.AdjVol.Time, SysMsg.AdjVol.R_VPP1, SysMsg.AdjVol.R_VNN1, SysMsg.AdjVol.R_VPP2, SysMsg.AdjVol.R_VNN2);            
                }
                else
                {
                    DEBUG_PRINTF(SysMsg.AdjVol.DebugMessage, "MinAdjVol %d Times - SysMsg.AdjVol.Time = %d - MinAdjVol Fail : %d %d %d %d \r\n", SysMsg.AdjVol.MinAdjVolCnt, SysMsg.AdjVol.Time, SysMsg.AdjVol.R_VPP1, SysMsg.AdjVol.R_VNN1, SysMsg.AdjVol.R_VPP2, SysMsg.AdjVol.R_VNN2);            
                }
            }
        }
        
        if(SysMsg.AdjVol.VolMinitor)
        {
            if(SysMsg.AdjVol.R_VPP1 <= SysMsg.AdjVol.MIN_VPP1 || SysMsg.AdjVol.R_VPP1 >= SysMsg.AdjVol.MAX_VPP1 ||
               SysMsg.AdjVol.R_VNN1 <= SysMsg.AdjVol.MIN_VNN1 || SysMsg.AdjVol.R_VNN1 >= SysMsg.AdjVol.MAX_VNN1 ||
               SysMsg.AdjVol.R_VPP2 <= SysMsg.AdjVol.MIN_VPP2 || SysMsg.AdjVol.R_VPP2 >= SysMsg.AdjVol.MAX_VPP2 ||
               SysMsg.AdjVol.R_VNN2 <= SysMsg.AdjVol.MIN_VNN2 || SysMsg.AdjVol.R_VNN2 >= SysMsg.AdjVol.MAX_VNN2 ) 
            {
                DEBUG_PRINTF(SysMsg.AdjVol.DebugMessage, "Voltage output is out range : %d %d %d %d \r\n", SysMsg.AdjVol.R_VPP1, SysMsg.AdjVol.R_VNN1, SysMsg.AdjVol.R_VPP2, SysMsg.AdjVol.R_VNN2);            
                SysMsg.AdjVol.VolMinitor = FALSE;
//                Adjust_Voltage_Close();
            }
            
            if(SysMsg.AdjVol.R_VPP1 < (SysMsg.AdjVol.R_VPP2 - 200) || SysMsg.AdjVol.R_VNN1 < (SysMsg.AdjVol.R_VNN2 - 200))
            {
                DEBUG_PRINTF(SysMsg.AdjVol.DebugMessage, "HV1 < HV2 : %d %d %d %d \r\n", SysMsg.AdjVol.R_VPP1, SysMsg.AdjVol.R_VNN1, SysMsg.AdjVol.R_VPP2, SysMsg.AdjVol.R_VNN2);            
                SysMsg.AdjVol.VolMinitor = FALSE;
//                Adjust_Voltage_Close();
            }
        }
        
        if(SysMsg.AdjVol.AdjVolOpen)
        {
            if(SysMsg.AdjVol.Time <= SysMsg.AdjVol.TimeOut)                                     //δ��ʱ
            {
                if(SysMsg.AdjVol.R_VPP1 >= SysMsg.AdjVol.MIN_VPP1 && SysMsg.AdjVol.R_VPP1 <= SysMsg.AdjVol.MAX_VPP1 &&
                   SysMsg.AdjVol.R_VNN1 >= SysMsg.AdjVol.MIN_VNN1 && SysMsg.AdjVol.R_VNN1 <= SysMsg.AdjVol.MAX_VNN1 &&
                   SysMsg.AdjVol.R_VPP2 >= SysMsg.AdjVol.MIN_VPP2 && SysMsg.AdjVol.R_VPP2 <= SysMsg.AdjVol.MAX_VPP2 &&
                   SysMsg.AdjVol.R_VNN2 >= SysMsg.AdjVol.MIN_VNN2 && SysMsg.AdjVol.R_VNN2 <= SysMsg.AdjVol.MAX_VNN2 )  
                {
                    DEBUG_PRINTF(SysMsg.AdjVol.DebugMessage, "SysMsg.AdjVol.Time = %d, AdjVol Success : %d %d %d %d \r\n", SysMsg.AdjVol.Time, SysMsg.AdjVol.R_VPP1, SysMsg.AdjVol.R_VNN1, SysMsg.AdjVol.R_VPP2, SysMsg.AdjVol.R_VNN2);            
                    
                    SysMsg.AdjVol.AdjVolOpen = FALSE;                                           //���ε�ѹ����
                    SysMsg.AdjVol.MinAdjVolOpen = TRUE;                                         //΢������
                    SysMsg.AdjVol.VolMinitor = FALSE;                                           //����ݲ�����
                    AdjVol_Result_Send();                                                       //�ϴ���ѹ 
                }
            }
            else
            {
                DEBUG_PRINTF(SysMsg.AdjVol.DebugMessage, "SysMsg.AdjVol.Time = %d, AdjVol Timeout : %d %d %d %d \r\n", SysMsg.AdjVol.Time, SysMsg.AdjVol.R_VPP1, SysMsg.AdjVol.R_VNN1, SysMsg.AdjVol.R_VPP2, SysMsg.AdjVol.R_VNN2);            
                                               
                SysMsg.AdjVol.AdjVolOpen = FALSE;                                               //���ε�ѹ����  
                SysMsg.AdjVol.MinAdjVolOpen = TRUE;                                             //΢������
                SysMsg.AdjVol.VolMinitor = FALSE;                                               //����ݲ�����
            }
        }
        
        OSTimeDlyHMSM(0, 0, 0, 5, OS_OPT_TIME_PERIODIC, &err);
    }
}





void App_AdjVol_TaskCreate()
{
    OS_ERR err;
    
    OSTaskCreate((OS_TCB *		)&AdjVolTcb, 
                 (CPU_CHAR *		)"App_AdjVol_Task", 
                 (OS_TASK_PTR		)App_AdjVol_Task,
                 (void *		)0,
                 (OS_PRIO		)APP_ADJVOL_TASK_PRIO,
                 (CPU_STK *		)&App_AdjVol_Task_Stk[0],
                 (CPU_STK_SIZE		)APP_ADJVOL_STK_SIZE / 10,
                 (CPU_STK_SIZE		)APP_ADJVOL_STK_SIZE,
                 (OS_MSG_QTY		)0,
                 (OS_TICK		)0,
                 (void *		)0,
                 (OS_OPT		)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
                 (OS_ERR *		)&err);
}

