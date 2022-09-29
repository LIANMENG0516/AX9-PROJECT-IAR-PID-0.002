#include "app_adjvolcw.h"

extern System_MsgStruct SysMsg;

OS_TCB AdjVolCwTcb;
CPU_STK App_AdjVolCw_Task_Stk[APP_ADJVOLCW_STK_SIZE];

void App_AdjVolCw_Task()
{
    OS_ERR err;

    while(1)
    {	
        if(SysMsg.AdjVol.RoughAdjVolCwOpen == TRUE)
        {
            Adjust_Voltage_CW();
            
            SysMsg.AdjVol.RoughAdjVolCwOpen = FALSE;

            SysMsg.AdjVol.CwTime = 0; 
            SysMsg.AdjVol.CwTimerOpen = TRUE; 
            
            SysMsg.AdjVol.WaitRoughAdjVolResultCwOpen = TRUE; 
        }
        if(SysMsg.AdjVol.WaitRoughAdjVolResultCwOpen == TRUE)
        {
            if(SysMsg.AdjVol.CwTime <= SysMsg.AdjVol.CwTimeOut)  
            {
                if(SysMsg.AdjVol.R_VPP2 >= SysMsg.AdjVol.MIN_PCW && SysMsg.AdjVol.R_VPP2 <= SysMsg.AdjVol.MAX_PCW &&
                   SysMsg.AdjVol.R_VNN2 >= SysMsg.AdjVol.MIN_NCW && SysMsg.AdjVol.R_VNN2 <= SysMsg.AdjVol.MAX_NCW )  
                {     
                    //关闭等待粗调结果开关
                    SysMsg.AdjVol.WaitRoughAdjVolResultCwOpen = FALSE;
                    
                    //打开微调开关
                    SysMsg.AdjVol.FineAdjVolCwOpen = TRUE;
                    
                    //清零微调次数
                    SysMsg.AdjVol.FineAdjVolCwCnt = 0;                                 
                }
            }
            else
            {      
                //关闭等待粗调结果开关
                SysMsg.AdjVol.WaitRoughAdjVolResultCwOpen = FALSE;
                
                //打开微调开关
                SysMsg.AdjVol.FineAdjVolCwOpen = TRUE;
            }
        }
        if(SysMsg.AdjVol.FineAdjVolCwOpen == TRUE)  
        {
            if(++SysMsg.AdjVol.FineAdjVolCwCnt >= 20 || ((abs(SysMsg.AdjVol.R_VPP2 - SysMsg.AdjVol.T_PCW) < RNAGE_MIN_VOL && abs(SysMsg.AdjVol.R_VNN2 - SysMsg.AdjVol.T_NCW) < RNAGE_MIN_VOL )))
            {
                //清零微调次数
                SysMsg.AdjVol.FineAdjVolCwCnt = 0;
                    
                //计时清零, 关闭计时开关  
                SysMsg.AdjVol.CwTime = 0; 
                SysMsg.AdjVol.CwTimerOpen = FALSE; 
                
                //关闭微调开关
                SysMsg.AdjVol.FineAdjVolCwOpen = FALSE;   
                
                //设置HV1调压完成标志
                SysMsg.AdjVol.CwAdjVolCompleteFlag = IDLE;                 

                //打开高压监控开关
                SysMsg.AdjVol.CwMinitorOpen = TRUE;
            }
            else
            {
                if(abs(SysMsg.AdjVol.R_VPP2 - SysMsg.AdjVol.T_VPP2) > RNAGE_MIN_VOL)
                {
                    int16_t DesVol;
                    
                    DesVol = SysMsg.AdjVol.R_VPP2 - SysMsg.AdjVol.T_VPP2;
                    
                    if(DesVol > 0)
                    {
                        if(SysMsg.AdjVol.P_SpiDacPcw + 1 >= 208)
                        {
                            SysMsg.AdjVol.P_SpiDacPcw = 208;
                        }
                        else
                        {
                            SysMsg.AdjVol.P_SpiDacPcw += 1;
                        }
                        
                    }
                    if(DesVol < 0)
                    {
                        if(SysMsg.AdjVol.P_SpiDacPcw - 1 <= 137)
                        {
                            SysMsg.AdjVol.P_SpiDacPcw = 137;
                        }
                        else
                        {
                            SysMsg.AdjVol.P_SpiDacPcw -= 1;
                        }
                    }
                }
                
                if(abs(SysMsg.AdjVol.R_VNN2 - SysMsg.AdjVol.T_VNN2) > RNAGE_MIN_VOL)
                {
                    int16_t DesVol;
                    
                    DesVol = SysMsg.AdjVol.R_VNN2 - SysMsg.AdjVol.T_VNN2;
                    
                    if(DesVol > 0)
                    {
                        if(SysMsg.AdjVol.P_SpiDacNcw + 1 >= 245)
                        {
                            SysMsg.AdjVol.P_SpiDacNcw = 245;
                        }
                        else
                        {
                            SysMsg.AdjVol.P_SpiDacNcw += 1;
                        }
                    }
                    if(DesVol < 0)
                    {
                        if(SysMsg.AdjVol.P_SpiDacNcw - 1 <= 72)
                        {
                            SysMsg.AdjVol.P_SpiDacNcw = 72;
                        }
                        else
                        {
                            SysMsg.AdjVol.P_SpiDacNcw -= 1;
                        }
                        
                    }
                }

                DacCw_Tlv5626cd_ValueSet(SysMsg.AdjVol.P_SpiDacPcw, SysMsg.AdjVol.P_SpiDacNcw);  
            }
        }
        
        if(SysMsg.AdjVol.CwMinitorOpen == TRUE)                            
        {
            if(SysMsg.AdjVol.R_VPP2 >= SysMsg.AdjVol.MAX_PCW || SysMsg.AdjVol.R_VNN2 >= SysMsg.AdjVol.MAX_NCW ) 
            {
                SysMsg.AdjVol.CwMinitorOpen = FALSE;
                UploadErrorCode3();                                         
                Adjust_Voltage_Close();                                     
            }
            
            if(SysMsg.AdjVol.R_VPP1 < (SysMsg.AdjVol.R_VPP2 - 150) || SysMsg.AdjVol.R_VNN1 < (SysMsg.AdjVol.R_VNN2 - 150))
            {
                SysMsg.AdjVol.CwMinitorOpen = FALSE;
                UploadErrorCode4();                                         
                Adjust_Voltage_Close();                                     
            }
        }
      
        OSTimeDlyHMSM(0, 0, 0, 80, OS_OPT_TIME_PERIODIC, &err);
    }
}




void App_AdjVolCw_TaskCreate()
{
    OS_ERR err;
    
    OSTaskCreate((OS_TCB *		)&AdjVolCwTcb, 
                 (CPU_CHAR *		)"App_AdjVolCw_Task", 
                 (OS_TASK_PTR		)App_AdjVolCw_Task,
                 (void *		)0,
                 (OS_PRIO		)APP_ADJVOLCW_TASK_PRIO,
                 (CPU_STK *		)&App_AdjVolCw_Task_Stk[0],
                 (CPU_STK_SIZE		)APP_ADJVOLCW_STK_SIZE / 10,
                 (CPU_STK_SIZE		)APP_ADJVOLCW_STK_SIZE,
                 (OS_MSG_QTY		)0,
                 (OS_TICK		)0,
                 (void *		)0,
                 (OS_OPT		)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
                 (OS_ERR *		)&err);
}






