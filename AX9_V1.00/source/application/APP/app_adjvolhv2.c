#include "app_adjvolhv2.h"

extern System_MsgStruct SysMsg;

OS_TCB AdjVolHv2Tcb;
CPU_STK App_AdjVolHv2_Task_Stk[APP_ADJVOLHV2_STK_SIZE];

void App_AdjVolHv2_Task()
{
    OS_ERR err;

    while(1)
    {	
        //�ֵ�, ��Ҫ����Ӳ����ѹ
        if(SysMsg.AdjVol.RoughAdjVolHv2Open == TRUE)                        
        {
            //������ѹ
            while(SysMsg.AdjVol.P_McuDacHv2 != SysMsg.AdjVol.T_McuDacHv2 || SysMsg.AdjVol.P_SpiDacHv2 != SysMsg.AdjVol.T_SpiDacHv2)                                    //������ɣ�������Ҫ����
            {
                SysMsg.AdjVol.P_McuDacHv2 = Step_HvAdjVol_Calcuation(SysMsg.AdjVol.T_McuDacHv2, SysMsg.AdjVol.P_McuDacHv2, MCU_DAC);  
                SysMsg.AdjVol.P_SpiDacHv2 = Step_HvAdjVol_Calcuation(SysMsg.AdjVol.T_SpiDacHv2, SysMsg.AdjVol.P_SpiDacHv2, SPI_DAC);  
              
                //����VPP2
                DAC_SetChannel2Data(DAC_Align_12b_R, SysMsg.AdjVol.P_McuDacHv2);                                               
                DAC_SoftwareTriggerCmd(DAC_Channel_2, ENABLE);                                                                
                
                //����VNN2
                DacHv_Tlv5626cd_ValueSet(SysMsg.AdjVol.P_SpiDacHv1, SysMsg.AdjVol.P_SpiDacHv2);
            }
            
            //�������
            if(SysMsg.AdjVol.P_McuDacHv2 == SysMsg.AdjVol.T_McuDacHv2 && SysMsg.AdjVol.P_SpiDacHv2 == SysMsg.AdjVol.T_SpiDacHv2)                                    //������ɣ�������Ҫ����
            {
                //�رմֵ�����
                SysMsg.AdjVol.RoughAdjVolHv2Open = FALSE;  
                
                //��ʱ����, �򿪼�ʱ����
                SysMsg.AdjVol.Hv2Time = 0; 
                SysMsg.AdjVol.Hv2TimerOpen = TRUE; 
                
                //�򿪵ȴ��ֵ��������
                SysMsg.AdjVol.WaitRoughAdjVolResultHv2Open = TRUE; 
            }
            
        }
        
        //�ȴ��ֵ���� 
        if(SysMsg.AdjVol.WaitRoughAdjVolResultHv2Open == TRUE)
        {
            if(SysMsg.AdjVol.Hv2Time <= SysMsg.AdjVol.Hv2TimeOut)                                     
            {
                if(SysMsg.AdjVol.R_VPP2 >= SysMsg.AdjVol.MIN_VPP2 && SysMsg.AdjVol.R_VPP2 <= SysMsg.AdjVol.MAX_VPP2 &&
                   SysMsg.AdjVol.R_VNN2 >= SysMsg.AdjVol.MIN_VNN2 && SysMsg.AdjVol.R_VNN2 <= SysMsg.AdjVol.MAX_VNN2 )  
                {     
                    //�رյȴ��ֵ��������
                    SysMsg.AdjVol.WaitRoughAdjVolResultHv2Open = FALSE;
                    
                    //��΢������
                    SysMsg.AdjVol.FineAdjVolHv2Open = TRUE;
                    
                    //����΢������
                    SysMsg.AdjVol.FineAdjVolHv2Cnt = 0;
                }
            }
            else
            {      
                //�رյȴ��ֵ��������
                SysMsg.AdjVol.WaitRoughAdjVolResultHv2Open = FALSE;
                
                //��΢������
                SysMsg.AdjVol.FineAdjVolHv2Open = TRUE;
            }
        }

        //΢��, ��Ҫ�����̼�����, ���ڷ�������
        if(SysMsg.AdjVol.FineAdjVolHv2Open == TRUE)                         
        {
      
            if(++SysMsg.AdjVol.FineAdjVolHv2Cnt >= 20 || ((abs(SysMsg.AdjVol.R_VPP2 - SysMsg.AdjVol.T_VPP2) < RNAGE_MIN_VOL && abs(SysMsg.AdjVol.R_VNN2 - SysMsg.AdjVol.T_VNN2) < RNAGE_MIN_VOL )))
            {
                //����΢������
                SysMsg.AdjVol.FineAdjVolHv2Cnt = 0;
                    
                //��ʱ����, �رռ�ʱ 
                SysMsg.AdjVol.Hv2Time = 0; 
                SysMsg.AdjVol.Hv2TimerOpen = FALSE;   
                
                //�ر�΢������
                SysMsg.AdjVol.FineAdjVolHv2Open = FALSE; 
                
                //����HV1��ѹ��ɱ�־
                SysMsg.AdjVol.Hv2AdjVolCompleteFlag = IDLE;                 

                //�򿪸�ѹ��ؿ���
                SysMsg.AdjVol.Hv2MinitorOpen = TRUE;
            }
            else
            {
                if(abs(SysMsg.AdjVol.R_VPP2 - SysMsg.AdjVol.T_VPP2) > RNAGE_MIN_VOL)           
                {
                    int16_t DesVol;
                    
                    DesVol = SysMsg.AdjVol.R_VPP2 - SysMsg.AdjVol.T_VPP2;
                    
                    if(DesVol > 0)
                    {
                        if(SysMsg.AdjVol.P_McuDacHv2 + 3 >= 2457)
                        {
                            SysMsg.AdjVol.P_McuDacHv2 = 2457; 
                        }
                        else
                        {
                            SysMsg.AdjVol.P_McuDacHv2 += 3; 
                        }
                    }
                    
                    if(DesVol < 0)
                    {       
                        if(SysMsg.AdjVol.P_McuDacHv2 - 3 <= 447)
                        {
                            SysMsg.AdjVol.P_McuDacHv2 = 447;
                        }
                        else
                        {
                            SysMsg.AdjVol.P_McuDacHv2 -= 3;
                        }
                    }   
                    
                    DAC_SetChannel2Data(DAC_Align_12b_R, SysMsg.AdjVol.P_McuDacHv2);                 //����VPP1
                    DAC_SoftwareTriggerCmd(DAC_Channel_2, ENABLE);                                   //�������DACת��
                }
            
                if(abs(SysMsg.AdjVol.R_VNN2 - SysMsg.AdjVol.T_VNN2) > RNAGE_MIN_VOL)           
                {
                    int16_t DesVol;
                    
                    DesVol = SysMsg.AdjVol.R_VNN2 - SysMsg.AdjVol.T_VNN2;
                    
                    if(DesVol > 0)
                    {
                        if(SysMsg.AdjVol.P_SpiDacHv2 + 2 >= 247)
                        {
                            SysMsg.AdjVol.P_SpiDacHv2 = 247;
                        }
                        else
                        {
                            SysMsg.AdjVol.P_SpiDacHv2 += 2; 
                        }
                    }
                    if(DesVol < 0)
                    {
                        
                        if(SysMsg.AdjVol.P_SpiDacHv2 - 2 <= 46)
                        {
                            SysMsg.AdjVol.P_SpiDacHv2 = 46;
                        }
                        else
                        {
                            SysMsg.AdjVol.P_SpiDacHv2 -= 2;
                        }
                    }
                    
                    DacHv_Tlv5626cd_ValueSet(SysMsg.AdjVol.P_SpiDacHv1, SysMsg.AdjVol.P_SpiDacHv2);
                }
            }
        }
        
        OSTimeDlyHMSM(0, 0, 0, 80, OS_OPT_TIME_PERIODIC, &err);
        
        //���
        if(SysMsg.AdjVol.Hv2MinitorOpen == TRUE)                            
        {
            if(SysMsg.AdjVol.R_VPP2 >= SysMsg.AdjVol.MAX_VPP2 || SysMsg.AdjVol.R_VNN2 >= SysMsg.AdjVol.MAX_VNN2 ) 
            {
                SysMsg.AdjVol.Hv2MinitorOpen = FALSE;
                UploadErrorCode3();                                         
                Adjust_Voltage_Close();                                     
            }
            
            if(SysMsg.AdjVol.R_VPP1 < (SysMsg.AdjVol.R_VPP2 - 150) || SysMsg.AdjVol.R_VNN1 < (SysMsg.AdjVol.R_VNN2 - 150))
            {
                SysMsg.AdjVol.Hv2MinitorOpen = FALSE;
                UploadErrorCode4();                                         
                Adjust_Voltage_Close();                                     
            }
        }   
    }
}




void App_AdjVolHv2_TaskCreate()
{
    OS_ERR err;
    
    OSTaskCreate((OS_TCB *		)&AdjVolHv2Tcb, 
                 (CPU_CHAR *		)"App_AdjVolHv2_Task", 
                 (OS_TASK_PTR		)App_AdjVolHv2_Task,
                 (void *		)0,
                 (OS_PRIO		)APP_ADJVOLHV2_TASK_PRIO,
                 (CPU_STK *		)&App_AdjVolHv2_Task_Stk[0],
                 (CPU_STK_SIZE		)APP_ADJVOLHV2_STK_SIZE / 10,
                 (CPU_STK_SIZE		)APP_ADJVOLHV2_STK_SIZE,
                 (OS_MSG_QTY		)0,
                 (OS_TICK		)0,
                 (void *		)0,
                 (OS_OPT		)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
                 (OS_ERR *		)&err);
}







