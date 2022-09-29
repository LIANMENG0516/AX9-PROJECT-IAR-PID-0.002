#include "app_com.h"

extern System_MsgStruct SysMsg;

extern uint8_t RcvData[100];
extern DataBufStruct CommuComRX;

OS_TCB ComEcTaskTcb;
CPU_STK App_ComEc_Task_Stk[APP_COMEC_STK_SIZE];

void App_ComEc_Task()
{
    OS_ERR err;

    while(1)
    {	
        if(ReceiveFrameAnalysis(CommuComRX.Data, sizeof(RcvData), &CommuComRX.pBufIn, &CommuComRX.pBufOut) == SUCCESS)
        {
            SysMsg.Cmd.Channel = ECCOM_CHANNEL;
            Cmd_Process();                                                  //√¸¡Ó¥¶¿Ì 
        } 
        
        OSTimeDlyHMSM(0, 0, 0, 5, OS_OPT_TIME_PERIODIC, &err);
    }
}

void App_ComEc_TaskCreate()
{
    OS_ERR err;
    
    OSTaskCreate((OS_TCB *              )&ComEcTaskTcb, 
                 (CPU_CHAR *		)"App_ComEc_Task", 
                 (OS_TASK_PTR		)App_ComEc_Task,
                 (void *		)0,
                 (OS_PRIO		)APP_COMEC_TASK_PRIO,
                 (CPU_STK *		)&App_ComEc_Task_Stk[0],
                 (CPU_STK_SIZE		)APP_COMEC_STK_SIZE / 10,
                 (CPU_STK_SIZE		)APP_COMEC_STK_SIZE,
                 (OS_MSG_QTY		)0,
                 (OS_TICK		)0,
                 (void *		)0,
                 (OS_OPT		)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
                 (OS_ERR *		)&err);
}





