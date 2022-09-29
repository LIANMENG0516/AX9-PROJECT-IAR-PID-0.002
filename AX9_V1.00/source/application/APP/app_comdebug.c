#include "app_comdebug.h"

extern System_MsgStruct SysMsg;

extern uint8_t RcvData[100];
extern DataBufStruct DebugComRX;

OS_TCB ComDebugTaskTcb;
CPU_STK App_ComDebug_Task_Stk[APP_COMDEBUG_STK_SIZE];

void App_ComDebug_Task()
{
    OS_ERR err;

    while(1)
    {	        
        if(ReceiveFrameAnalysis(DebugComRX.Data, sizeof(RcvData), &DebugComRX.pBufIn, &DebugComRX.pBufOut) == SUCCESS)
        {
            SysMsg.Cmd.Channel = DEBUGCOM_CHANNEL;
            Cmd_Process();                                                  //√¸¡Ó¥¶¿Ì 
        }

        OSTimeDlyHMSM(0, 0, 0, 5, OS_OPT_TIME_PERIODIC, &err);
    }
}

void App_ComDebug_TaskCreate()
{
    OS_ERR err;
    
    OSTaskCreate((OS_TCB *              )&ComDebugTaskTcb, 
                 (CPU_CHAR *		)"App_ComDebug_Task", 
                 (OS_TASK_PTR		)App_ComDebug_Task,
                 (void *		)0,
                 (OS_PRIO		)APP_COMDEBUG_TASK_PRIO,
                 (CPU_STK *		)&App_ComDebug_Task_Stk[0],
                 (CPU_STK_SIZE		)APP_COMDEBUG_STK_SIZE / 10,
                 (CPU_STK_SIZE		)APP_COMDEBUG_STK_SIZE,
                 (OS_MSG_QTY		)0,
                 (OS_TICK		)0,
                 (void *		)0,
                 (OS_OPT		)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
                 (OS_ERR *		)&err);
}
