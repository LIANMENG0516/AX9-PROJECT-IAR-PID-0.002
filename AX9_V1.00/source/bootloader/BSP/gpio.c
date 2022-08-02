#include "gpio.h"

static void Gpio_Init(GPIO_TypeDef* GPIOx, uint16_t Gpio_Pin, GPIOMode_TypeDef GPIO_Mode, GPIOOType_TypeDef GPIO_OType, GPIOPuPd_TypeDef GPIO_PuPd)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    GPIO_InitStruct.GPIO_Pin = Gpio_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode;				
    GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;		
    GPIO_InitStruct.GPIO_OType = GPIO_OType;				
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd;			
    GPIO_Init(GPIOx, &GPIO_InitStruct);	
}

void Gpio_Config()
{	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG, ENABLE);                                   
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);                         //使能PWR时钟
    PWR_BackupAccessCmd(ENABLE);                                                //使能后备寄存器访问
    RCC_LSEConfig(RCC_LSE_OFF);                                                 //关闭外部低速外部时钟, 关闭后PC14 PC15才可以当普通IO用。
    PWR_BackupAccessCmd(DISABLE);                                               //禁止修改后备寄存器
    
    //PBUS_ON
    Gpio_Init(PBUS_ON_PORT, PBUS_ON_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    PBUS_ON(1); 
    
    //PWR_CTL
    Gpio_Init(PWR_CTL_PORT, PWR_CTL_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    PWR_CTL(1);
    
    //PWR_BTN_COM
    Gpio_Init(PWR_BTN_COM_PORT, PWR_BTN_COM_PIN, GPIO_Mode_OUT, GPIO_OType_OD, GPIO_PuPd_NOPULL);
    PWR_BTN_COM(1);
    
    //PWR_OK_COM
    Gpio_Init(PWR_OK_COM_PORT, PWR_OK_COM_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    PWR_OK_COM(1);
    
    //C_P12V
    Gpio_Init(C_P12V_PORT, C_P12V_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    CTL_P12V_EN(1);
     
     //C_P5V5_1
    Gpio_Init(C_P5V5_1_PORT, C_P5V5_1_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    CTL_P5V5_1_EN(1);
    
    //C_N12V_5V5
    Gpio_Init(C_N12V_5V5_PORT, C_N12V_5V5_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    CTL_N12V_5V5_EN(1);
    
    //C_P5V5_2
    Gpio_Init(C_P5V5_2_PORT, C_P5V5_2_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    CTL_P5V5_2_EN(1);
    
    //C_P3V75
    Gpio_Init(C_P3V75_PORT, C_P3V75_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    CTL_P3V75_EN(1); 
    
    //C_P2V25
    Gpio_Init(C_P2V25_PORT, C_P2V25_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    CTL_P2V25_EN(1);
    
    //C_D0V95
    Gpio_Init(C_D0V95_PORT, C_D0V95_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    CTL_D0V95_EN(1);
    
    //C_VDD_P5V
    Gpio_Init(C_VDD_P5V_PORT, C_VDD_P5V_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    CTL_VDD_P5V_EN(1);
    
    //C_D1V45
    Gpio_Init(C_D1V45_PORT, C_D1V45_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    CTL_D1V45_EN(1);
    
    //EN_FRONT
    Gpio_Init(EN_FRONT_PORT, EN_FRONT_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    EN_FRONT(1);
    
    //EN_FPGA_01
    Gpio_Init(EN_FPGA_01_PORT, EN_FPGA_01_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    EN_FPGA_01(1);
    
    //AFE_EN1
    Gpio_Init(AFE_EN1_PORT, AFE_EN1_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    AFE_EN1(1);
    
    //EN_FPGA_02
    Gpio_Init(EN_FPGA_02_PORT, EN_FPGA_02_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    EN_FPGA_02(1);
    
    //AFE_EN2
    Gpio_Init(AFE_EN2_PORT, AFE_EN2_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    AFE_EN2(1);
    
    //SUS_S4
    Gpio_Init(SUS_S4_PORT, SUS_S4_PIN, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL);

    //SUS_S3
    Gpio_Init(SUS_S3_PORT, SUS_S3_PIN, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL);

    //PD10
    Gpio_Init(PD10_PORT, PD10_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    CTL_MCU_LED(1);

    //PWR_KEY
    Gpio_Init(PWR_KEY_PORT, PWR_KEY_PIN, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_DOWN);

    //SYS_LED
    Gpio_Init(SYS_LED_PORT, SYS_LED_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    SYS_LED(1);
    
    //USB_CTRL
    Gpio_Init(USB_CTRL_PORT, USB_CTRL_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    USB_CTRL_EN(1);    

    //USART4_DEBUG_COM
    GPIO_PinAFConfig(DEBUG_COM_TX_PORT, GPIO_PinSource0, GPIO_AF_UART4);
    GPIO_PinAFConfig(DEBUG_COM_RX_PORT, GPIO_PinSource1, GPIO_AF_UART4);
    Gpio_Init(DEBUG_COM_TX_PORT, DEBUG_COM_TX_PIN, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    Gpio_Init(DEBUG_COM_RX_PORT, DEBUG_COM_RX_PIN, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    
    //USART2_COMM_COM
    GPIO_PinAFConfig(COMM_COM_TX_PORT, GPIO_PinSource5, GPIO_AF_USART2);
    GPIO_PinAFConfig(COMM_COM_RX_PORT, GPIO_PinSource6, GPIO_AF_USART2);
    Gpio_Init(COMM_COM_TX_PORT, COMM_COM_TX_PIN, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    Gpio_Init(COMM_COM_RX_PORT, COMM_COM_RX_PIN, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_NOPULL);

    //C_VNN2_VPP2
    Gpio_Init(C_VPP2_VNN2_PORT, C_VPP2_VNN2_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_DOWN);
    CTL_VPP2_VNN2_EN(0);

    //C_VNN1_VPP1
    Gpio_Init(C_VPP1_VNN1_PORT, C_VPP1_VNN1_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_DOWN); 
    CTL_VPP1_VNN1_EN(0);    
}























