#include <esp_adc_cal.h>
#include <esp32-hal-adc.h>
#include <Arduino.h> 
#include "adc_usb.h"



uint16_t adc_value[6]={0};//采样值
float adc_voltage[6]={0};//电压值
int adc_set_pin[6]={8,18,17,16,15,7};
uint16_t sum[6]={0};
// void read_adc(void) // 定义一个函数用于读取ADC采样值和电压值
// {

//   // 根据采样值计算电压值并存储到adc_voltage变量中

//   adc_usb.adc_value_2 = analogRead(adc_usb.adc_usb_2); // 从模拟输入引脚读取采样值并存储到adc_value变量中
//   adc_usb.adc_voltage_2 = adc_usb.adc_value_2 * (3.3 / 4095); // 根据采样值计算电压值并存储到adc_voltage变量中

//   adc_usb.adc_value_3 = analogRead(adc_usb.adc_usb_3); // 从模拟输入引脚读取采样值并存储到adc_value变量中
//   adc_usb.adc_voltage_3 = adc_usb.adc_value_3 * (3.3 / 4095); // 根据采样值计算电压值并存储到adc_voltage变量中

//   adc_usb.adc_value_4 = analogRead(adc_usb.adc_usb_4); // 从模拟输入引脚读取采样值并存储到adc_value变量中
//   adc_usb.adc_voltage_4 = adc_usb.adc_value_4 * (3.3 / 4095); // 根据采样值计算电压值并存储到adc_voltage变量中

//   adc_usb.adc_value_5 = analogRead(adc_usb.adc_usb_5); // 从模拟输入引脚读取采样值并存储到adc_value变量中
//   adc_usb.adc_voltage_5 = adc_usb.adc_value_5 * (3.3 / 4095); // 根据采样值计算电压值并存储到adc_voltage变量中

//   adc_usb.adc_value_6 = analogRead(adc_usb.adc_usb_6); // 从模拟输入引脚读取采样值并存储到adc_value变量中
//   adc_usb.adc_voltage_6 = adc_usb.adc_value_6 * (3.3 / 4095); // 根据采样值计算电压值并存储到adc_voltage变量中


//   // Serial.printf("采样值：%d 电压值：%.2f", adc_value_1, adc_voltage_1); // 通过串口打印采样值和电压值
//   // Serial.println(); // 换行
//   // delay(200); // 延时500毫秒
// }

/*
算术平均滤波
*/
#ifdef AVERAGE
extern uint16_t sum[6];

#define N 12
void filtration_1(void)
{
  int i=0;
  analogReadResolution(12);
  uint16_t count=0;
  for(i=0;i<6;i++)
  {
    sum[i]=0;
  }
  for(i=0;i<6;i++)
  {
    for(count = 0;count<N;count++)
    {
      sum[i] += analogRead(adc_set_pin[i]);//采样值
    }
    adc_value[i]=sum[i]/N;
    adc_voltage[i]=adc_value[i]*(3.3 / 4095);
  }
}
#endif


