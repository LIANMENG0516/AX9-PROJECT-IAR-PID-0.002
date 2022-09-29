#include "app_adjvolhv2.h"

extern System_MsgStruct SysMsg;

OS_TCB AdjVolHv2Tcb;
CPU_STK App_AdjVolHv2_Task_Stk[APP_ADJVOLHV2_STK_SIZE];

void App_AdjVolHv2_Task()
{
    OS_ERR err;

    while(1)
    {	
        //粗调, 主要依靠硬件调压
        if(SysMsg.AdjVol.RoughAdjVolHv2Open == TRUE)                        
        {
            //单步调压
            while(SysMsg.AdjVol.P_McuDacHv2 != SysMsg.AdjVol.T_McuDacHv2 || SysMsg.AdjVol.P_SpiDacHv2 != SysMsg.AdjVol.T_SpiDacHv2)                                    //调节完成，不在需要调节
            {
                SysMsg.AdjVol.P_McuDacHv2 = Step_HvAdjVol_Calcuation(SysMsg.AdjVol.T_McuDacHv2, SysMsg.AdjVol.P_McuDacHv2, MCU_DAC);  
                SysMsg.AdjVol.P_SpiDacHv2 = Step_HvAdjVol_Calcuation(SysMsg.AdjVol.T_SpiDacHv2, SysMsg.AdjVol.P_SpiDacHv2, SPI_DAC);  
              
                //调节VPP2
                DAC_SetChannel2Data(DAC_Align_12b_R, SysMsg.AdjVol.P_McuDacHv2);                                               
                DAC_SoftwareTriggerCmd(DAC_Channel_2, ENABLE);                                                                
                
                //调节VNN2
                DacHv_Tlv5626cd_ValueSet(SysMsg.AdjVol.P_SpiDacHv1, SysMsg.AdjVol.P_SpiDacHv2);
            }
            
            //调节完成
            if(SysMsg.AdjVol.P_McuDacHv2 == SysMsg.AdjVol.T_McuDacHv2 && SysMsg.AdjVol.P_SpiDacHv2 == SysMsg.AdjVol.T_SpiDacHv2)                                    //调节完成，不在需要调节
            {
                //关闭粗调开关
                SysMsg.AdjVol.RoughAdjVolHv2Open = FALSE;  
                
                //计时清零, 打开计时开关
                SysMsg.AdjVol.Hv2Time = 0; 
                SysMsg.AdjVol.Hv2TimerOpen = TRUE; 
                
                //打开等待粗调结果开关
                SysMsg.AdjVol.WaitRoughAdjVolResultHv2Open = TRUE; 
            }
            
        }
        
        //等待粗调结果 
        if(SysMsg.AdjVol.WaitRoughAdjVolResultHv2Open == TRUE)
        {
            if(SysMsg.AdjVol.Hv2Time <= SysMsg.AdjVol.Hv2TimeOut)                                     
            {
                if(SysMsg.AdjVol.R_VPP2 >= SysMsg.AdjVol.MIN_VPP2 && SysMsg.AdjVol.R_VPP2 <= SysMsg.AdjVol.MAX_VPP2 &&
                   SysMsg.AdjVol.R_VNN2 >= SysMsg.AdjVol.MIN_VNN2 && SysMsg.AdjVol.R_VNN2 <= SysMsg.AdjVol.MAX_VNN2 )  
                {     
                    //关闭等待粗调结果开关
                    SysMsg.AdjVol.WaitRoughAdjVolResultHv2Open = FALSE;
                    
                    //打开微调开关
                    SysMsg.AdjVol.FineAdjVolHv2Open = TRUE;
                    
                    //清零微调次数
                    SysMsg.AdjVol.FineAdjVolHv2Cnt = 0;
                }
            }
            else
            {      
                //关闭等待粗调结果开关
                SysMsg.AdjVol.WaitRoughAdjVolResultHv2Open = FALSE;
                
                //打开微调开关
                SysMsg.AdjVol.FineAdjVolHv2Open = TRUE;
            }
        }

        //微调, 主要依靠固件调节, 调节幅度有限
        if(SysMsg.AdjVol.FineAdjVolHv2Open == TRUE)                         
        {
      
            if(++SysMsg.AdjVol.FineAdjVolHv2Cnt >= 20 || ((abs(SysMsg.AdjVol.R_VPP2 - SysMsg.AdjVol.T_VPP2) < RNAGE_MIN_VOL && abs(SysMsg.AdjVol.R_VNN2 - SysMsg.AdjVol.T_VNN2) < RNAGE_MIN_VOL )))
            {
                //清零微调次数
                SysMsg.AdjVol.FineAdjVolHv2Cnt = 0;
                    
                //计时清零, 关闭计时 
                SysMsg.AdjVol.Hv2Time = 0; 
                SysMsg.AdjVol.Hv2TimerOpen = FALSE;   
                
                //关闭微调开关
                SysMsg.AdjVol.FineAdjVolHv2Open = FALSE; 
                
                //设置HV1调压完成标志
                SysMsg.AdjVol.Hv2AdjVolCompleteFlag = IDLE;                 

                //打开高压监控开关
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
                    
                    DAC_SetChannel2Data(DAC_Align_12b_R, SysMsg.AdjVol.P_McuDacHv2);                 //调节VPP1
                    DAC_SoftwareTriggerCmd(DAC_Channel_2, ENABLE);                                   //软件触发DAC转换
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
        
        //监控
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







