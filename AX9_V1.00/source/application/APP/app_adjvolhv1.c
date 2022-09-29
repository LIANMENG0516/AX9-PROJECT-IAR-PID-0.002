#include "app_adjvolhv1.h"

extern System_MsgStruct SysMsg;

OS_TCB AdjVolHv1Tcb;
CPU_STK App_AdjVolHv1_Task_Stk[APP_ADJVOLHV1_STK_SIZE];

void App_AdjVolHv1_Task()
{
    OS_ERR err;

    while(1)
    {	
        //粗调, 主要依靠硬件调压
        if(SysMsg.AdjVol.RoughAdjVolHv1Open == TRUE)                        
        {
            while(SysMsg.AdjVol.P_McuDacHv1 != SysMsg.AdjVol.T_McuDacHv1 || SysMsg.AdjVol.P_SpiDacHv1 != SysMsg.AdjVol.T_SpiDacHv1)                                    //调节完成，不在需要调节
            {
                SysMsg.AdjVol.P_McuDacHv1 = Step_HvAdjVol_Calcuation(SysMsg.AdjVol.T_McuDacHv1, SysMsg.AdjVol.P_McuDacHv1, MCU_DAC);  
                SysMsg.AdjVol.P_SpiDacHv1 = Step_HvAdjVol_Calcuation(SysMsg.AdjVol.T_SpiDacHv1, SysMsg.AdjVol.P_SpiDacHv1, SPI_DAC);  
              
                //调节VPP1
                DAC_SetChannel1Data(DAC_Align_12b_R, SysMsg.AdjVol.P_McuDacHv1);                                                
                DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);                                                                  
                
                //调节VNN1
                DacHv_Tlv5626cd_ValueSet(SysMsg.AdjVol.P_SpiDacHv1, SysMsg.AdjVol.P_SpiDacHv2);                                 
            }
            
            //调节完成
            if(SysMsg.AdjVol.P_McuDacHv1 == SysMsg.AdjVol.T_McuDacHv1 && SysMsg.AdjVol.P_SpiDacHv1 == SysMsg.AdjVol.T_SpiDacHv1)                                    //调节完成，不在需要调节
            {
                //关闭粗调开关
                SysMsg.AdjVol.RoughAdjVolHv1Open = FALSE;  
                
                //计时清零, 打开计时开关
                SysMsg.AdjVol.Hv1Time = 0; 
                SysMsg.AdjVol.Hv1TimerOpen = TRUE; 
                
                //打开等待粗调结果开关
                SysMsg.AdjVol.WaitRoughAdjVolResultHv1Open = TRUE; 
            }
        }
        
        //等待粗调结果 
        if(SysMsg.AdjVol.WaitRoughAdjVolResultHv1Open == TRUE)
        {
            if(SysMsg.AdjVol.Hv1Time <= SysMsg.AdjVol.Hv1TimeOut)                                     
            {
                if(SysMsg.AdjVol.R_VPP1 >= SysMsg.AdjVol.MIN_VPP1 && SysMsg.AdjVol.R_VPP1 <= SysMsg.AdjVol.MAX_VPP1 &&
                   SysMsg.AdjVol.R_VNN1 >= SysMsg.AdjVol.MIN_VNN1 && SysMsg.AdjVol.R_VNN1 <= SysMsg.AdjVol.MAX_VNN1 )  
                {     
                    //关闭等待粗调结果开关
                    SysMsg.AdjVol.WaitRoughAdjVolResultHv1Open = FALSE;
                    
                    //打开微调开关
                    SysMsg.AdjVol.FineAdjVolHv1Open = TRUE;
                    
                    //清零微调次数
                    SysMsg.AdjVol.FineAdjVolHv1Cnt = 0;                               
                }
            }
            else
            {      
                //关闭等待粗调结果开关
                SysMsg.AdjVol.WaitRoughAdjVolResultHv1Open = FALSE;
                
                //打开微调开关
                SysMsg.AdjVol.FineAdjVolHv1Open = TRUE;
            }
        }

        //微调, 主要依靠固件调节, 调节幅度有限
        if(SysMsg.AdjVol.FineAdjVolHv1Open == TRUE)                         
        {
      
            if(++SysMsg.AdjVol.FineAdjVolHv1Cnt >= 20 || ((abs(SysMsg.AdjVol.R_VPP1 - SysMsg.AdjVol.T_VPP1) < RNAGE_MIN_VOL && abs(SysMsg.AdjVol.R_VNN1 - SysMsg.AdjVol.T_VNN1) < RNAGE_MIN_VOL )))
            {
                //清零微调次数
                SysMsg.AdjVol.FineAdjVolHv1Cnt = 0;
                    
                //计时清零, 关闭计时开关  
                SysMsg.AdjVol.Hv1Time = 0; 
                SysMsg.AdjVol.Hv1TimerOpen = FALSE; 
                
                //关闭微调开关
                SysMsg.AdjVol.FineAdjVolHv1Open = FALSE;   
                
                //设置HV1调压完成标志
                SysMsg.AdjVol.Hv1AdjVolCompleteFlag = IDLE;                 

                //打开高压监控开关
                SysMsg.AdjVol.Hv1MinitorOpen = TRUE;
            }
            else
            {
                if(abs(SysMsg.AdjVol.R_VPP1 - SysMsg.AdjVol.T_VPP1) > RNAGE_MIN_VOL)           
                {
                    int16_t DesVol;
                    
                    DesVol = SysMsg.AdjVol.R_VPP1 - SysMsg.AdjVol.T_VPP1;
                    
                    if(DesVol > 0)
                    {
                        if(SysMsg.AdjVol.P_McuDacHv1 + 3 >= 2457)
                        {
                            SysMsg.AdjVol.P_McuDacHv1 = 2457;
                        }
                        else
                        {
                            SysMsg.AdjVol.P_McuDacHv1 += 3;
                        }
                    }
                    
                    if(DesVol < 0)
                    {                
                        if(SysMsg.AdjVol.P_McuDacHv1 - 3 <= 447)
                        {
                            SysMsg.AdjVol.P_McuDacHv1 = 447;
                        }
                        else
                        {
                            SysMsg.AdjVol.P_McuDacHv1 -= 3;
                        }
                           
                    }   
                    
                    DAC_SetChannel1Data(DAC_Align_12b_R, SysMsg.AdjVol.P_McuDacHv1);                 //调节VPP1
                    DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);                                   //软件触发DAC转换
                }
            
                if(abs(SysMsg.AdjVol.R_VNN1 - SysMsg.AdjVol.T_VNN1) > RNAGE_MIN_VOL)           
                {
                    int16_t DesVol;
                    
                    DesVol = SysMsg.AdjVol.R_VNN1 - SysMsg.AdjVol.T_VNN1;
                    
                    if(DesVol > 0)
                    {
                        if(SysMsg.AdjVol.P_SpiDacHv1 + 2 >= 247)
                        {
                            SysMsg.AdjVol.P_SpiDacHv1 = 247; 
                        }
                        else
                        {
                            SysMsg.AdjVol.P_SpiDacHv1 += 2; 
                        }
                    }
                    if(DesVol < 0)
                    {
                        if(SysMsg.AdjVol.P_SpiDacHv1 - 2 <= 46)
                        {
                            SysMsg.AdjVol.P_SpiDacHv1 = 46;
                        }
                        else
                        {
                            SysMsg.AdjVol.P_SpiDacHv1 -= 2; 
                        }
                    }
                    
                    DacHv_Tlv5626cd_ValueSet(SysMsg.AdjVol.P_SpiDacHv1, SysMsg.AdjVol.P_SpiDacHv2);
                }
            }
        }
        
        OSTimeDlyHMSM(0, 0, 0, 80, OS_OPT_TIME_PERIODIC, &err);
        
        //监控
        if(SysMsg.AdjVol.Hv1MinitorOpen == TRUE)                            
        {
            if(SysMsg.AdjVol.R_VPP1 >= SysMsg.AdjVol.MAX_VPP1 || SysMsg.AdjVol.R_VNN1 >= SysMsg.AdjVol.MAX_VNN1 ) 
            {
                SysMsg.AdjVol.Hv1MinitorOpen = FALSE;
                UploadErrorCode3();                                         
                Adjust_Voltage_Close();                                     
            }
            
            if(SysMsg.AdjVol.R_VPP1 < (SysMsg.AdjVol.R_VPP2 - 150) || SysMsg.AdjVol.R_VNN1 < (SysMsg.AdjVol.R_VNN2 - 150))
            {
                SysMsg.AdjVol.Hv1MinitorOpen = FALSE;
                UploadErrorCode4();                                         
                Adjust_Voltage_Close();                                     
            }
            
        }
    }
}




void App_AdjVolHv1_TaskCreate()
{
    OS_ERR err;
    
    OSTaskCreate((OS_TCB *		)&AdjVolHv1Tcb, 
                 (CPU_CHAR *		)"App_AdjVolHv1_Task", 
                 (OS_TASK_PTR		)App_AdjVolHv1_Task,
                 (void *		)0,
                 (OS_PRIO		)APP_ADJVOLHV1_TASK_PRIO,
                 (CPU_STK *		)&App_AdjVolHv1_Task_Stk[0],
                 (CPU_STK_SIZE		)APP_ADJVOLHV1_STK_SIZE / 10,
                 (CPU_STK_SIZE		)APP_ADJVOLHV1_STK_SIZE,
                 (OS_MSG_QTY		)0,
                 (OS_TICK		)0,
                 (void *		)0,
                 (OS_OPT		)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
                 (OS_ERR *		)&err);
}







