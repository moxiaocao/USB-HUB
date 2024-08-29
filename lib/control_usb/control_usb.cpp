#include <Arduino.h>
#include "../control_usb/control_usb.h"

CONTROL USB_FLAG;

/*初始化usb引脚和type控制引脚*/
/*
初始化输出引脚，初始化的时候usb控制脚为低电平，即默认关闭，等设置的时候再拉高
参数：true为开启type-c A，false为开启type-c B,在setup中只要调用下面函数就能同时初始化usb控制和type上行控制。但是设置还是要调用Input_Signal_Set。
*/
void Usb_Control_Init(bool type_flag)
{
    pinMode(typec_control_pins[1], OUTPUT);
    int i=0;
    for(i=0;i<6;i++)
    {
        pinMode(usb_control_pins[i], OUTPUT);
        digitalWrite(usb_control_pins[i], LOW);
    }
    Input_Signal_Set(type_flag);
}

void Input_Signal_Set(bool flag)
{
    
    switch (flag)
    {
    case true:
        digitalWrite(typec_control_pins[1], HIGH);
        break;
    case false:
        digitalWrite(typec_control_pins[1], LOW);
        break;
    }
}

/*开关控制usb的falg为真/假，此函数检测真假情况，根据开关状态设置电平高低*/
void Usb_Control_Write(bool USB)
{
    int i=0;
    for(i=0;i<6;i++)
    {
        if(USB_FLAG.USB_flag[i]==true)
        {
            digitalWrite(usb_control_pins[i], HIGH);
        }
        else if (USB_FLAG.USB_flag[i]==false)
        {
            digitalWrite(usb_control_pins[i], LOW);
        }
        
    }
}