#include "app.h"

#include "gouble.h"

OS_TCB StartTaskTcb;													//������ƿ�

OS_TMR			Sys_StateChk_Tmr;
	
CPU_STK App_Start_Task_Stk[APP_START_STK_SIZE];										//�����ջ�ռ�

void App_Start_Task()
{   
    OS_ERR err;
    CPU_SR_ALLOC();

    CPU_Init();
    
    #if OS_CFG_STAT_TASK_EN > 0u
       OSStatTaskCPUUsageInit(&err);  											//ͳ������                
    #endif
    
    #ifdef CPU_CFG_INT_DIS_MEAS_EN											//���ʹ���˲����жϹر�ʱ��
        CPU_IntDisMeasMaxCurReset();	
    #endif
    
    #if	OS_CFG_SCHED_ROUND_ROBIN_EN  											//��ʹ��ʱ��Ƭ��ת��ʱ�� 
        OSSchedRoundRobinCfg(DEF_ENABLED, 1, &err); 								        //ʹ��ʱ��Ƭ��ת���ȹ���,ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5=5ms 
    #endif	
    
    OS_CRITICAL_ENTER();												//�����ٽ���  

    App_Led_TaskCreate();
    App_Usb_TaskCreate();
    App_ComEc_TaskCreate();
    App_ComDebug_TaskCreate();
    App_Fan_TaskCreate();
    App_SysOnOff_TaskCreate();
    App_PwrManager_TaskCreate();
    App_Temperature_TaskCreate();
    App_AdjVol_TaskCreate();
    
    OSTmrCreate(&Sys_StateChk_Tmr, "Sys_StateChk_Tmr", 1, 1, OS_OPT_TMR_PERIODIC, cb_Sys_StateChk_Tmr, 0, &err);	//������ʱ��10ms	
    OSTmrStart(&Sys_StateChk_Tmr, &err);

    OSTaskSuspend(&StartTaskTcb, &err);

    OS_CRITICAL_EXIT();													//�˳��ٽ���
}

void App_Start_Task_Create()
{
    OS_ERR err;
    
    OSTaskCreate((OS_TCB *		)&StartTaskTcb,								        //������ƿ� 
                 (CPU_CHAR *		)"App_Start_Task", 							        //��������
                 (OS_TASK_PTR		)App_Start_Task,							        //��������
                 (void *		)0,									        //���ݸ��������Ĳ���
                 (OS_PRIO		)APP_START_TASK_PRIO,							        //�������ȼ�
                 (CPU_STK *		)&App_Start_Task_Stk[0],						        //�����ջ����ַ
                 (CPU_STK_SIZE		)APP_START_STK_SIZE / 10,						        //�����ջ�����λ
                 (CPU_STK_SIZE		)APP_START_STK_SIZE,							        //�����ջ��С
                 (OS_MSG_QTY		)0,									        //�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK		)0,									        //��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ���
                 (void *		)0,									        //�û�����Ĵ洢��
                 (OS_OPT		)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,		                        //����ѡ��
                 (OS_ERR *		)&err);									        //��Ÿú�������ʱ�ķ���ֵ
}






