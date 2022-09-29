#include "adjustvoltage.h"

#include "gouble.h"

extern System_MsgStruct SysMsg;

uint16_t Vpp_Calculate_AdjVol(uint16_t T_Data)
{
    float Adjvol;
    uint16_t Dac_Val;
    
    Adjvol = 2.096 - T_Data / 100.0 / 43.2;                                  //(1/43.2+1/3.48+1)*1.6=2.096
    Dac_Val = (int)((Adjvol / 3.3 * 4095)+ 0.5);

    return Dac_Val;
}

uint16_t Vnn_Calculate_AdjVol(uint16_t T_Data)
{
    float Adjvol;
    uint16_t Dac_Val;
    
    Adjvol = 2.098 - ((0.023 * T_Data) / 100);    
    
    Dac_Val = ((int)(Adjvol * 4096 / 2.048)) >> 4;               //四舍五入后取整数
    
    return Dac_Val;
}

uint16_t Pcw_Calculate_AdjVol(uint16_t T_Data)
{
    uint16_t Dac_Val;
    
    Dac_Val = (uint16_t)(279 - 28.4 * T_Data / 100);
    
    return Dac_Val;
}

uint16_t Ncw_Calculate_AdjVol(uint16_t T_Data)
{
    uint16_t Dac_Val;
    
    Dac_Val = (uint16_t)(318 - 29.2 * T_Data / 100);    
    
    return Dac_Val;
}

void Adjust_Voltage_Vpp1(uint16_t T_Vpp1)
{          
    if(T_Vpp1 != 0)
    {
        SysMsg.AdjVol.P_McuDacHv1 = SysMsg.AdjVol.T_McuDacHv1 = Vpp_Calculate_AdjVol(T_Vpp1);                         //计算要调节到目标值时HVADJ1的值
    }
    else
    {
        SysMsg.AdjVol.P_McuDacHv1 = VPP1_DAC_CLOSE;
    }
    DAC_SetChannel1Data(DAC_Align_12b_R, SysMsg.AdjVol.P_McuDacHv1);                                                    //调节VPP1至目标值
    DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);                                                                      //软件触发DAC转换
}

void Adjust_Voltage_Vpp2(uint16_t T_Vpp2)
{
    if(T_Vpp2 != 0)
    {
        SysMsg.AdjVol.P_McuDacHv2 = SysMsg.AdjVol.T_McuDacHv2 = Vpp_Calculate_AdjVol(T_Vpp2);                           //计算要调节到目标值时HVADJ3的值
    }
    else
    {
        SysMsg.AdjVol.P_McuDacHv2 = VPP2_DAC_CLOSE;
    }
    DAC_SetChannel2Data(DAC_Align_12b_R, SysMsg.AdjVol.P_McuDacHv2);                                                    //调节VPP2至目标值
    DAC_SoftwareTriggerCmd(DAC_Channel_2, ENABLE);                                                                      //软件触发DAC转换
}

void Adjust_Voltage_Vnn1_Vnn2(uint16_t T_Vnn1, uint16_t T_Vnn2)                                           
{
    if(T_Vnn1 != 0)
    {
        SysMsg.AdjVol.P_SpiDacHv1 = SysMsg.AdjVol.T_SpiDacHv1 = Vnn_Calculate_AdjVol(T_Vnn1);
    }
    else
    {
        SysMsg.AdjVol.P_SpiDacHv1 = VNN1_DAC_CLOSE;
    }

    if(T_Vnn2 != 0)
    {
        SysMsg.AdjVol.P_SpiDacHv2 = SysMsg.AdjVol.T_SpiDacHv2 = Vnn_Calculate_AdjVol(T_Vnn2);
    }
    else
    {
        SysMsg.AdjVol.P_SpiDacHv2 = VNN2_DAC_CLOSE;
    }
    
    DacHv_Tlv5626cd_ValueSet(SysMsg.AdjVol.P_SpiDacHv1, SysMsg.AdjVol.P_SpiDacHv2);
}

void Adjust_Voltage_Pcw_Ncw(uint16_t Pcw, uint16_t Ncw)                                           
{
    SysMsg.AdjVol.P_SpiDacPcw = SysMsg.AdjVol.T_SpiDacPcw = Pcw_Calculate_AdjVol(Pcw);
    SysMsg.AdjVol.P_SpiDacNcw = SysMsg.AdjVol.T_SpiDacNcw = Ncw_Calculate_AdjVol(Ncw);
    
    DacCw_Tlv5626cd_ValueSet(SysMsg.AdjVol.P_SpiDacPcw, SysMsg.AdjVol.P_SpiDacNcw);
}

void Adjust_Hv_Reset()
{
    DAC_SetChannel1Data(DAC_Align_12b_R, VPP1_DAC_CLOSE);                       //调节VPP1至目标值
    DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);                              //软件触发DAC转换
    
    DAC_SetChannel2Data(DAC_Align_12b_R, VPP2_DAC_CLOSE);                       //调节VPP2至目标值
    DAC_SoftwareTriggerCmd(DAC_Channel_2, ENABLE);                              //软件触发DAC转换
    
    DacHv_Tlv5626cd_ValueSet(VNN1_DAC_CLOSE, VNN2_DAC_CLOSE);
}

void Adjust_Hv1_Reset()
{
    DAC_SetChannel1Data(DAC_Align_12b_R, VPP1_DAC_CLOSE);                       //调节VPP1至目标值
    DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);                              //软件触发DAC转换
    DacHv_Tlv5626cd_ValueSet(VNN1_DAC_CLOSE, SysMsg.AdjVol.P_SpiDacHv2);
}

void Adjust_Hv2_Reset()
{
    DAC_SetChannel2Data(DAC_Align_12b_R, VPP2_DAC_CLOSE);                       //调节VPP2至目标值
    DAC_SoftwareTriggerCmd(DAC_Channel_2, ENABLE);                              //软件触发DAC转换
    DacHv_Tlv5626cd_ValueSet(SysMsg.AdjVol.P_SpiDacHv1, VNN2_DAC_CLOSE);
}

void Adjust_Cw_Reset()
{
    DacCw_Tlv5626cd_ValueSet(PCW_DAC_CLOSE, NCW_DAC_CLOSE);
}

void Adjust_Voltage_Init()
{  
    Adjust_Hv_Reset();
    Adjust_Cw_Reset();
    CTL_VPP1_VNN1_EN(0);                                                        
    CTL_VPP2_VNN2_EN(0);
}

void Adjust_Voltage_Close()
{
    Adjust_Hv_Reset();
    Adjust_Cw_Reset();
}

void Adjust_Voltage_HV()                                                        //高压调压处理流程
{     
    CTL_VPP1_VNN1_EN(1);                                                        //打开高压输出
    CTL_VPP2_VNN2_EN(1);
    Adjust_Voltage_Vpp1(SysMsg.AdjVol.T_VPP1);                                  //调节VPP1至目标值
    Adjust_Voltage_Vpp2(SysMsg.AdjVol.T_VPP2);                                  //调节VPP2至目标值
    Adjust_Voltage_Vnn1_Vnn2(SysMsg.AdjVol.T_VNN1, SysMsg.AdjVol.T_VNN2);       //调节VNN1, VNN2至目标值
}

void Adjust_Voltage_CW()                                                        //低压调压处理流程
{
    CTL_VPP1_VNN1_EN(1);                                                        //打开高压输出
    CTL_VPP2_VNN2_EN(1);
    Adjust_Voltage_Vpp1(SysMsg.AdjVol.T_VPP1);                                  //调节VPP1至目标值   
    Adjust_Voltage_Vpp2(SysMsg.AdjVol.T_VPP2);                                  //关闭VPP2
    Adjust_Voltage_Vnn1_Vnn2(SysMsg.AdjVol.T_VNN1, SysMsg.AdjVol.T_VNN2);       //调节VNN1至目标值, 关闭VNN2
    Adjust_Voltage_Pcw_Ncw(SysMsg.AdjVol.T_PCW, SysMsg.AdjVol.T_NCW);           
}

uint16_t Step_HvAdjVol_Calcuation(uint16_t Target, uint16_t Precent, u8 DacState)       //步进调压值计算
{
    uint16_t temp = 0, stepUp = 0, stepDown = 0;
    
    if(DacState == MCU_DAC)                                                             //片内MCU_DAC调节步进值
    {
        stepUp = STEP_DACMCU_UP;
        stepDown = STEP_DACMCU_DOWN;
    }
    else                                                                                //片外SPI_DAC调节步进值
    {
        stepUp = STEP_SPIMCU_UP;
        stepDown = STEP_SPIMCU_DOWN;
    }
  
    if(Target > Precent)
    {
        if(Target - Precent > stepUp)  
        {
            temp = Precent + stepUp;
        }
        else
        {
            temp = Target;
        }
    }
    else if(Precent > Target)
    {
        if(Precent - Target > stepDown)
        {
            temp = Precent - stepDown;
        }
        else
        {
            temp = Target;
        }
    }
    else
    {
        temp = Target;
    }

    return temp;
}

void Calc_TarVolCw_AlowRange()
{    
    SysMsg.AdjVol.MAX_PCW = SysMsg.AdjVol.T_PCW + 100;
    SysMsg.AdjVol.MIN_PCW = SysMsg.AdjVol.T_PCW - 100;
    SysMsg.AdjVol.MAX_NCW = SysMsg.AdjVol.T_NCW + 100;
    SysMsg.AdjVol.MIN_NCW = SysMsg.AdjVol.T_NCW - 100;
}

void Calc_TarVolHv1_AlowRange()
{    
    SysMsg.AdjVol.MAX_VPP1 = SysMsg.AdjVol.T_VPP1 + 100;
    SysMsg.AdjVol.MIN_VPP1 = SysMsg.AdjVol.T_VPP1 - 100;
    SysMsg.AdjVol.MAX_VNN1 = SysMsg.AdjVol.T_VPP1 + 100;
    SysMsg.AdjVol.MIN_VNN1 = SysMsg.AdjVol.T_VPP1 - 100;
}

void Calc_TarVolHv2_AlowRange()
{    
    SysMsg.AdjVol.MAX_VPP2 = SysMsg.AdjVol.T_VPP2 + 100;
    SysMsg.AdjVol.MIN_VPP2 = SysMsg.AdjVol.T_VPP2 - 100;
    SysMsg.AdjVol.MAX_VNN2 = SysMsg.AdjVol.T_VPP2 + 100;
    SysMsg.AdjVol.MIN_VNN2 = SysMsg.AdjVol.T_VPP2 - 100;
}





