#include "ds2431.h"

#include "gouble.h"

void US_PWR_ID_OUT()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;				
    GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;		
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;				
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;			
    GPIO_Init(GPIOE, &GPIO_InitStruct);	
}

void US_PWR_ID_IN()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;				
    GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;		
    GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;				
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;			
    GPIO_Init(GPIOE, &GPIO_InitStruct);	
    
    GPIO_SetBits(GPIOE, GPIO_Pin_11);
}



uint8_t DS2431_Reset()
{
    uint8_t result;

    US_PWR_ID_OUT(); US_PWR_ID_1(); delay_us_os(200);
    US_PWR_ID_0();                                      //拉低总线600us产生复位脉冲
    delay_us_os(600);
    US_PWR_ID_IN();                                     //释放总线
    delay_us_os(60);
    result = US_PWR_ID_READ();                          //接收应答
    delay_us_os(300);

    return result;
}

void DS2431_WriteByte(uint8_t data)
{
    US_PWR_ID_OUT();
    
    for(int i=0; i<8; i++)
    {
        US_PWR_ID_1(); 
        delay_us_os(2); 
        US_PWR_ID_0();
        delay_us_os(10);
        if(data & 0x01)
        {
            US_PWR_ID_1();
        }
        else
        {
            US_PWR_ID_0();
        }
        delay_us_os(60);

        data = data >> 1;
    }
}

uint8_t DS2431_ReadByte()
{
    uint8_t data = 0, mask = 0x01;

    for(int i=0; i<8; i++)
    {
        US_PWR_ID_OUT(); 
        US_PWR_ID_1(); 
        delay_us_os(2);
        US_PWR_ID_0();
        delay_us_os(2);
        US_PWR_ID_IN();
        delay_us_os(5);
        if(US_PWR_ID_READ())
        {
            data |= mask;
        }
        else
        {
            data &= ~mask;
        }
        delay_us_os(60);

        mask = mask << 1;
    }
    
    return data;
}

uint8_t state, crch, crcl;

uint8_t DS2431_WirteData(uint16_t addr, uint8_t *pBuf)
{     
    if(DS2431_Reset())                                  //写草稿
    {
        return 1;
    }
    DS2431_WriteByte(0xCC);
    DS2431_WriteByte(0x0F);
    DS2431_WriteByte(addr & 0xFF);
    DS2431_WriteByte(addr >> 8);
    for(int i=0; i<8; i++)
    {
        DS2431_WriteByte(pBuf[i]);
    }
    
    crch = DS2431_ReadByte();
    crcl = DS2431_ReadByte();
    

    if(DS2431_Reset())                                  //读草稿
    {
        return 1;
    }
    DS2431_WriteByte(0xCC);
    DS2431_WriteByte(0xAA);
    state = DS2431_ReadByte();
    if(state != addr & 0xFF)
    {
        return 1;
    }
    state = DS2431_ReadByte();
    if(state != (addr >> 8))
    {
        return 1;
    }
    state = DS2431_ReadByte();
    if(state != 0x07)
    {
        return 1;
    }
    for(int i=0; i<8; i++)
    {
        state = DS2431_ReadByte();
        if(state != pBuf[i])
        {
            return 1;
        }
    }
    crch = DS2431_ReadByte();
    crcl = DS2431_ReadByte();
    
    if(DS2431_Reset())                                  //复制草稿到寄存器
    {
        return 1; 
    }
    DS2431_WriteByte(0xCC);
    DS2431_WriteByte(0x55);
    DS2431_WriteByte(addr & 0xFF);
    DS2431_WriteByte(addr >> 8);
    DS2431_WriteByte(0x07);
    
    US_PWR_ID_IN();
    Delay_ms(10);
    
    state = DS2431_ReadByte();
    
    if(state != 0xAA)
    {
        return 1;
    }
    
    return 0;  
}

uint8_t DS2431_ReadData(uint8_t addr, uint8_t *pBuf, uint8_t len)
{
    if(DS2431_Reset())
    {
        return 1;
    }
    DS2431_WriteByte(0xCC);
    DS2431_WriteByte(0xF0);
    DS2431_WriteByte(addr & 0xFF);
    DS2431_WriteByte(addr >> 8);
    
    for(uint8_t i=0; i<len; i++)
    {
        pBuf[i] = DS2431_ReadByte();
    }
    
    if(DS2431_Reset())
    {
        return 1;
    }
    
    return 0;
}


void Write_UsPowerInfo(uint8_t addr, uint8_t *pBuf)
{
    DS2431_WirteData(addr, pBuf);
}

void Read_UsPowerInfo(uint8_t addr, uint8_t *pBuf, uint8_t len)
{
    DS2431_ReadData(addr, pBuf, len);
}








