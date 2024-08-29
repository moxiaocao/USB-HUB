#ifndef _ADC_USB_
#define _ADC_USB_

#include <Arduino.h>

void read_adc(void);

// typedef struct {
//     int adc_usb_1=8;
//     int adc_usb_2=18;
//     int adc_usb_3=17;
//     int adc_usb_4=16;
//     int adc_usb_5=15;
//     int adc_usb_6=7;

//     uint16_t adc_value_1 = 0; // 定义一个16位无符号整数变量用于存储ADC采样值
//     float adc_voltage_1 = 0.0; // 定义一个浮点数变量用于存储ADC电压值

//     uint16_t adc_value_2 = 0; // 定义一个16位无符号整数变量用于存储ADC采样值
//     float adc_voltage_2 = 0.0; // 定义一个浮点数变量用于存储ADC电压值

//     uint16_t adc_value_3 = 0; // 定义一个16位无符号整数变量用于存储ADC采样值
//     float adc_voltage_3 = 0.0; // 定义一个浮点数变量用于存储ADC电压值

//     uint16_t adc_value_4 = 0; // 定义一个16位无符号整数变量用于存储ADC采样值
//     float adc_voltage_4 = 0.0; // 定义一个浮点数变量用于存储ADC电压值

//     uint16_t adc_value_5 = 0; // 定义一个16位无符号整数变量用于存储ADC采样值
//     float adc_voltage_5 = 0.0; // 定义一个浮点数变量用于存储ADC电压值

//     uint16_t adc_value_6 = 0; // 定义一个16位无符号整数变量用于存储ADC采样值
//     float adc_voltage_6 = 0.0; // 定义一个浮点数变量用于存储ADC电压值

// }ADC_USB;

// uint16_t adc_value[6]={0};//采样值
// float adc_voltage[6]={0};//电压值
// int adc_set_pin[6]={8,18,17,16,15,7};

#define AVERAGE 1

#ifdef AVERAGE
/*
算术平均滤波
*/
// uint16_t sum[6]={0};
void filtration_1(void);

#endif


#endif
