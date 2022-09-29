#include "board.h"

#include "gouble.h"

extern System_MsgStruct SysMsg;

extern DataBufStruct DebugComRX;
extern DataBufStruct DebugComTX;

extern Com_Buffer CommuComRX;
extern Com_Buffer CommuComTX;

extern uint8_t	RcvData[100];
extern uint8_t	SenData[100];

void Debug_Com_Config()
{
    Usart_Init(DEBUG_COM, 115200);	

    USART_ITConfig(DEBUG_COM, USART_IT_RXNE, DISABLE);								//�ر�RXNE�ж� 
    USART_ITConfig(DEBUG_COM, USART_IT_TXE, DISABLE);								//�ر�TXE�ж�
    USART_ITConfig(DEBUG_COM, USART_IT_IDLE, ENABLE);								//����IDLE�ж�

    USART_DMACmd(DEBUG_COM, USART_DMAReq_Rx, ENABLE);								//����USART_DMA����ͨ��
    USART_DMACmd(DEBUG_COM, USART_DMAReq_Tx, ENABLE);								//����USART_DMA����ͨ��

    Dma_Config(DEBUG_COM_DMAY_STREAMX_RX, DEBUG_COM_DMA_CHANNEL_RX, (uint32_t)&DEBUG_COM->DR, (uint32_t)&DebugComRX.Data[0], DMA_DIR_PeripheralToMemory, sizeof(RcvData), DMA_PeripheralDataSize_Byte, DMA_MemoryDataSize_Byte, DMA_Mode_Circular, DMA_Priority_VeryHigh);      //����DEBUG_COM_RX_DMAͨ��                                                                     
    Dma_Config(DEBUG_COM_DMAY_STREAMX_TX, DEBUG_COM_DMA_CHANNEL_TX, (uint32_t)&DEBUG_COM->DR, (uint32_t)&DebugComTX.Data[0], DMA_DIR_MemoryToPeripheral, sizeof(SenData), DMA_PeripheralDataSize_Byte, DMA_MemoryDataSize_Byte, DMA_Mode_Circular, DMA_Priority_VeryHigh);      //����DEBUG_COM_TX_DMAͨ��  

    DMA_Cmd(DEBUG_COM_DMAY_STREAMX_RX, ENABLE);                                                                 //ʹ��DMA����
    DMA_Cmd(DEBUG_COM_DMAY_STREAMX_TX, DISABLE);                                                                //�ر�DMA����


    DMA_ITConfig(DEBUG_COM_DMAY_STREAMX_TX, DMA_IT_TC, ENABLE);						        //����DMA�����ж�	
}

void Commu_Com_Config()
{
    Usart_Init(COMMU_COM, 115200);	

    USART_ITConfig(COMMU_COM, USART_IT_RXNE, DISABLE);								//�ر�RXNE�ж� 
    USART_ITConfig(COMMU_COM, USART_IT_TXE, DISABLE);								//�ر�TXE�ж�
    USART_ITConfig(COMMU_COM, USART_IT_IDLE, ENABLE);								//����IDLE�ж�

    USART_DMACmd(COMMU_COM, USART_DMAReq_Rx, ENABLE);								//����USART_DMA����ͨ��
    USART_DMACmd(COMMU_COM, USART_DMAReq_Tx, ENABLE);								//����USART_DMA����ͨ��

    Dma_Config(COMMU_COM_DMAY_STREAMX_RX, COMMU_COM_DMA_CHANNEL_RX, (uint32_t)&COMMU_COM->DR, (uint32_t)&CommuComRX.Data[0], DMA_DIR_PeripheralToMemory, sizeof(RcvData), DMA_PeripheralDataSize_Byte, DMA_MemoryDataSize_Byte, DMA_Mode_Circular, DMA_Priority_VeryHigh);      //����DEBUG_COM_RX_DMAͨ��                                                                     
    Dma_Config(COMMU_COM_DMAY_STREAMX_TX, COMMU_COM_DMA_CHANNEL_TX, (uint32_t)&COMMU_COM->DR, (uint32_t)&CommuComTX.Data[0], DMA_DIR_MemoryToPeripheral, sizeof(SenData), DMA_PeripheralDataSize_Byte, DMA_MemoryDataSize_Byte, DMA_Mode_Circular, DMA_Priority_VeryHigh);      //����DEBUG_COM_TX_DMAͨ��  

    DMA_Cmd(COMMU_COM_DMAY_STREAMX_RX, ENABLE);                                                                 //ʹ��DMA����
    DMA_Cmd(COMMU_COM_DMAY_STREAMX_TX, DISABLE);                                                                //�ر�DMA����

    DMA_ITConfig(COMMU_COM_DMAY_STREAMX_TX, DMA_IT_TC, ENABLE);						        //����DMA�����ж�	
}



void Adc3_Config()
{
    Adc_Init(ADC3, ADC3_CHANNEL_NUM);

    ADC_RegularChannelConfig(ADC3, CHANNEL_VPP1,    SAMPLE_VPP1_SEQUENCE,    ADC_SampleTime_480Cycles);
    ADC_RegularChannelConfig(ADC3, CHANNEL_VNN1,    SAMPLE_VNN1_SEQUENCE,    ADC_SampleTime_480Cycles);
    ADC_RegularChannelConfig(ADC3, CHANNEL_VPP2,    SAMPLE_VPP2_SEQUENCE,    ADC_SampleTime_480Cycles);
    ADC_RegularChannelConfig(ADC3, CHANNEL_VNN2,    SAMPLE_VNN2_SEQUENCE,    ADC_SampleTime_480Cycles);
    ADC_RegularChannelConfig(ADC3, CHANNEL_A3V75,   SAMPLE_A3V75_SEQUENCE,   ADC_SampleTime_480Cycles);
    ADC_RegularChannelConfig(ADC3, CHANNEL_A2V25,   SAMPLE_A2V25_SEQUENCE,   ADC_SampleTime_480Cycles);
    ADC_RegularChannelConfig(ADC3, CHANNEL_AP12V,   SAMPLE_AP12V_SEQUENCE,   ADC_SampleTime_480Cycles);
    ADC_RegularChannelConfig(ADC3, CHANNEL_AN12V,   SAMPLE_AN12V_SEQUENCE,   ADC_SampleTime_480Cycles);
    ADC_RegularChannelConfig(ADC3, CHANNEL_AP5V5_1, SAMPLE_AP5V5_1_SEQUENCE, ADC_SampleTime_480Cycles);
    ADC_RegularChannelConfig(ADC3, CHANNEL_AP5V5_2, SAMPLE_AP5V5_2_SEQUENCE, ADC_SampleTime_480Cycles);
    ADC_RegularChannelConfig(ADC3, CHANNEL_AN5V5,   SAMPLE_AN5V5_SEQUENCE,   ADC_SampleTime_480Cycles);
    ADC_RegularChannelConfig(ADC3, CHANNEL_INPUT,   SAMPLE_INPUT_SEQUENCE,   ADC_SampleTime_480Cycles);
    ADC_RegularChannelConfig(ADC3, CHANNEL_D0V95,   SAMPLE_D0V95_SEQUENCE,   ADC_SampleTime_480Cycles);
    ADC_RegularChannelConfig(ADC3, CHANNEL_D1V45,   SAMPLE_D1V45_SEQUENCE,   ADC_SampleTime_480Cycles);
}

void Adc1_Config()
{
    Adc_Init(ADC1, ADC1_CHANNEL_NUM);
    
    ADC_TempSensorVrefintCmd(ENABLE);
    ADC_RegularChannelConfig(ADC1, CHANNEL_IADP, SAMPLE_IADP_SEQUENCE,  ADC_SampleTime_480Cycles);
    ADC_RegularChannelConfig(ADC1, CHANNEL_TEMP, SAMPLE_TEMP_SEQUENCE,  ADC_SampleTime_480Cycles);
}



extern uint16_t  Adc_3_ConValue[ADC_SAMPLE_NUM][ADC3_CHANNEL_NUM];

extern uint16_t  Adc_1_ConValue[ADC_SAMPLE_NUM][ADC1_CHANNEL_NUM];

void V_AdcDma_Config()
{
    Adc3_Config();                                                         
    Dma_Config(ADC_DMAY_STREAMX_V, ADC_DMA_CHANNEL_V, (uint32_t)&ADC3->DR, (uint32_t)Adc_3_ConValue, DMA_DIR_PeripheralToMemory, ADC_SAMPLE_NUM * ADC3_CHANNEL_NUM, DMA_PeripheralDataSize_HalfWord, DMA_MemoryDataSize_HalfWord, DMA_Mode_Circular, DMA_Priority_VeryHigh);                                                                                                                                                                                                                  
    DMA_Cmd(ADC_DMAY_STREAMX_V, ENABLE); 
    ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);                         //�����������ֻ����һ��DMA�ж�
    ADC_DMACmd(ADC3, ENABLE);
    ADC_SoftwareStartConv(ADC3);	
}

void I_AdcDma_Config()
{
    Adc1_Config();
    Dma_Config(ADC_DMAY_STREAMX_I, ADC_DMA_CHANNEL_I, (uint32_t)&ADC1->DR, (uint32_t)Adc_1_ConValue, DMA_DIR_PeripheralToMemory, ADC_SAMPLE_NUM * ADC1_CHANNEL_NUM, DMA_PeripheralDataSize_HalfWord, DMA_MemoryDataSize_HalfWord, DMA_Mode_Circular, DMA_Priority_VeryHigh);                                                                                                                                                                                                                  
    DMA_Cmd(ADC_DMAY_STREAMX_I, ENABLE); 
    ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);                         //�����������ֻ����һ��DMA�ж�
    ADC_DMACmd(ADC1, ENABLE);
    ADC_SoftwareStartConv(ADC1);	
}

void Fan_Config()
{
    Fan_Emc2305_Init();
}

void Board_Bsp_Init()
{
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x20000);

    Nvic_Config();
    SysTick_Iint();
    Gpio_Config();

    Debug_Com_Config();                     //���Դ��ڳ�ʼ��
    Commu_Com_Config();                     //ͨѶ���ڳ�ʼ��--��ECͨѶ
    
    V_AdcDma_Config();                      //��ѹ����ͨ����ʼ��--��14·��ѹ����, ȫ��ʹ��ADC3
    I_AdcDma_Config();                      //����������Ƭ���¶Ȳ���ͨ����ʼ��--��2·��������, ʹ��ADC1

    Dac_config(DAC_Channel_1);
    Dac_config(DAC_Channel_2);
    
    Spi_Dac_Config();

    Fan_Config();
    TimerConfig();
    
    Adjust_Voltage_Init();
}



