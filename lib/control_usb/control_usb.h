#ifndef _CONTROL_USB_
#define _CONTROL_USB_

#include <Arduino.h>


typedef struct {  
    bool USB_flag[6]={false,false,false,false,false,false};
    bool typec_flag;
}CONTROL; 

const int usb_control_pins[6] = {48,47,21,14,13,12};//usb1-6(右边开始为USB1)
const int typec_control_pins[1] = {11};

void Usb_Control_Write(bool USB);
void Input_Signal_Set(bool flag);
void Usb_Control_Init(bool type_flag);

#endif
