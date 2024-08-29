#ifndef _BOOL_
#define _BOOL_

#include <Arduino.h>

//bool A;

typedef struct {  
    bool control_sw_1;
    bool control_sw_2;
    bool control_sw_3;
    bool control_sw_4;
    bool control_sw_5;
    bool control_sw_6;

    bool change_usb_sw1;
    bool change_usb_sw2; 
}flag_control; 



#endif
