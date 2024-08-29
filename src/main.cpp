#include <Arduino.h>
 
/*Using LVGL with Arduino requires some extra steps:
 *Be sure to read the docs here: https://docs.lvgl.io/master/get-started/platforms/arduino.html  */
 
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <../src/demos/lv_demos.h>

#include "..\..\lvgl\src\porting\lv_port_indev.h"
#include "..\src\generated\events_init.h"
#include "encoder.h"
#include "weather.h"

#include "adc_usb.h"
#include "usb_control.h"
extern float adc_voltage[6];
extern uint16_t adc_value[6];
 
extern Usb usb;


/*To use the built-in examples and demos of LVGL uncomment the includes below respectively.
 *You also need to copy `lvgl/examples` to `lvgl/src/examples`. Similarly for the demos `lvgl/demos` to `lvgl/src/demos`.
 Note that the `lv_examples` library is for LVGL v7 and you shouldn't install it for this version (since LVGL v8)
 as the examples and demos are now part of the main LVGL library. */
 
/*Change to your screen resolution*/
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 240;
 
static lv_disp_draw_buf_t draw_buf_dsc_2;
static lv_color_t buf_1[ screenWidth * 60 ];
static lv_color_t buf_2[ screenWidth * 60 ];
 
TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */


lv_ui guider_ui;
hw_timer_t *timer = NULL;
hw_timer_t *timer1 = NULL;
void timer_interrupt();
void timer_interrupt_1() ;
 
/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );
 
    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();
 
    lv_disp_flush_ready( disp );
}
 

void setup()
{
    Serial.begin( 9600 ); /* prepare for possible serial debug */
    lv_init();

    /*定时器100ms*/
    timer = timerBegin(0, 1000, true);
    timerAttachInterrupt(timer, timer_interrupt, true);
    timerAlarmWrite(timer, 8000, true);
    timerAlarmEnable(timer);
    /*定时器3000ms*/
    timer1 = timerBegin(1, 1000, true);//psc
    timerAttachInterrupt(timer1, timer_interrupt_1, true);
    timerAlarmWrite(timer1, 8000, true);//arr
    timerAlarmEnable(timer1);
 
    tft.begin();          /* TFT init */
    tft.setRotation( 1 ); /* Landscape orientation, flipped */
    tft.invertDisplay(0);
    lv_disp_draw_buf_init( &draw_buf_dsc_2, buf_1, buf_2, screenWidth * 60 );
    
    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf_dsc_2;
    disp_drv.full_refresh=0;//定义为非全局刷新
    lv_disp_drv_register( &disp_drv );
 
    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    lv_indev_drv_register( &indev_drv );


    lv_port_indev_init();
 
    setup_ui(&guider_ui);
    events_init(&guider_ui);
    ec11_init();

    weather_init();
    Usb_Control_Init(&usb);
    Input_Signal_Set(typec1);
    pinMode(40,OUTPUT);
    digitalWrite(40,HIGH);
}
 
void loop()
{

  lv_timer_handler(); /* let the GUI do its work */
  ec11_scan();
  Usb_Control_Set(&usb);

}
 

void timer_interrupt() 
{
/*********** usbadc数据刷新 ***********/
  filtration_1();

}

void timer_interrupt_1() 
{
  // if(digitalRead(21)==HIGH)
  // {
  //   digitalWrite(21,LOW);
  // }
  // else if(digitalRead(21)==LOW)
  // {
  //   digitalWrite(21,HIGH);
  // }
  // weather_scanf();
}
