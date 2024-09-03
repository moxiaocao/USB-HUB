/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/
#include <Arduino.h>
#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "stdio.h"
#if LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


#include "../Bool/Bool.h"
#include "../usb_control/usb_control.h"
#include "adc_usb.h"
#include "weather.h"
extern float adc_voltage[6];
extern Usb usb;
flag_control flag;
static void timer_callback(lv_timer_t * timer);
static void timer_callback_1(lv_timer_t * timer);
extern lv_ui guider_ui;
void create_100ms_timer(void);
char buffer_1[32];
char buffer_2[32];
char buffer_3[32];
char buffer_4[32];
char buffer_5[32];
char buffer_6[32];
lv_timer_t* task_timer;
lv_timer_t* task_timer_1;
extern unsigned int temp;
char wea_buffer_1[32];

static bool wea_flag=true;

static void start_screen_1_btn_1_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		// lv_timer_del(task_timer_1);//删除定时器句柄，避免不必要的内存占用导致重启芯片
		ui_load_scr_animation(&guider_ui, &guider_ui.USB_control_2, guider_ui.USB_control_2_del, &guider_ui.start_screen_1_del, setup_scr_USB_control_2, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, true, true);
		break;
	}
	default:
		break;
	}
}
static void start_screen_1_btn_2_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		// lv_timer_del(task_timer_1);//删除定时器句柄，避免不必要的内存占用导致重启芯片
		ui_load_scr_animation(&guider_ui, &guider_ui.USB_Data_4, guider_ui.USB_Data_4_del, &guider_ui.start_screen_1_del, setup_scr_USB_Data_4, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, true, true);

		break;
	}
	default:
		break;
	}
}
static void start_screen_1_btn_3_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		// lv_timer_del(task_timer_1);//删除定时器句柄，避免不必要的内存占用导致重启芯片
		ui_load_scr_animation(&guider_ui, &guider_ui.USB_Change_3, guider_ui.USB_Change_3_del, &guider_ui.start_screen_1_del, setup_scr_USB_Change_3, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, true, true);
		break;
	}
	default:
		break;
	}
}
static void start_screen_1_btn_4_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		// lv_timer_del(task_timer_1);//删除定时器句柄，避免不必要的内存占用导致重启芯片
		ui_load_scr_animation(&guider_ui, &guider_ui.Set_5, guider_ui.Set_5_del, &guider_ui.start_screen_1_del, setup_scr_Set_5, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, true, true);
		break;
	}
	default:
		break;
	}
}
void create_3000ms_timer(void) {  
    /* 创建一个定时器 */  
	task_timer_1 = lv_timer_create(timer_callback_1, 3000, 0);
 
} 
void events_init_start_screen_1(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->start_screen_1_btn_1, start_screen_1_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->start_screen_1_btn_2, start_screen_1_btn_2_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->start_screen_1_btn_3, start_screen_1_btn_3_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->start_screen_1_btn_4, start_screen_1_btn_4_event_handler, LV_EVENT_ALL, ui);
	// create_3000ms_timer();

}
static void timer_callback_1(lv_timer_t * timer) 
{
	/* 这里编写定时器到期时需要执行的代码 */
	weather_scanf();
	weather_data_up(&guider_ui);
}
void weather_data_up(lv_ui *ui)
{
	snprintf(wea_buffer_1, sizeof(wea_buffer_1), "%d", temp);//float到char的类型转换
	lv_label_set_text(ui->start_screen_1_label_3, wea_buffer_1);
}  
static void USB_control_2_btn_1_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.start_screen_1, guider_ui.start_screen_1_del, &guider_ui.USB_control_2_del, setup_scr_start_screen_1, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, true, true);
		break;
	}
	default:
		break;
	}
}
static void USB_control_2_sw_1_event_handler (lv_event_t *e)
{
	void *uui = lv_event_get_user_data(e);
	lv_ui* ui = (lv_ui *)uui;
	flag.control_sw_1=lv_obj_has_state(ui->USB_control_2_sw_1, LV_STATE_CHECKED);					 /* 返回值：bool类型，开 :1；关: 0 */
	if(flag.control_sw_1==0)
	{
		usb.usb_pin_state[0]= 0;
		Serial.printf("OFF");}
	else if(flag.control_sw_1==1)
	{
		usb.usb_pin_state[0]= 1;
		Serial.println(usb.usb_pin_state[0]);
		Serial.printf("ON");}
}
static void USB_control_2_sw_2_event_handler (lv_event_t *e)
{
	void *uui = lv_event_get_user_data(e);
	lv_ui* ui = (lv_ui *)uui;
	lv_obj_clear_state(ui->USB_control_2_sw_2, LV_EVENT_ALL);
	flag.control_sw_2=lv_obj_has_state(ui->USB_control_2_sw_2, LV_STATE_CHECKED);					 /* 返回值：bool类型，开 :1；关: 0 */
	if(flag.control_sw_2==false)
	{
		usb.usb_pin_state[1] = 0;
		Serial.printf("OFFsw2");}
	else if(flag.control_sw_2==true)
	{
		usb.usb_pin_state[1] = 1;
		Serial.printf("ONsw2");}
} 
static void USB_control_2_sw_3_event_handler (lv_event_t *e)
{
	void *uui = lv_event_get_user_data(e);
	lv_ui* ui = (lv_ui *)uui;
	flag.control_sw_3=lv_obj_has_state(ui->USB_control_2_sw_3, LV_STATE_CHECKED);					 /* 返回值：bool类型，开 :1；关: 0 */
	if(flag.control_sw_3==0)
	{
		usb.usb_pin_state[2] = 0;
		Serial.printf("OFF");}
	else if(flag.control_sw_3==1)
	{
		usb.usb_pin_state[2] = 1;
		Serial.printf("ON");}
}
static void USB_control_2_sw_4_event_handler (lv_event_t *e)
{
	void *uui = lv_event_get_user_data(e);
	lv_ui* ui = (lv_ui *)uui;
	flag.control_sw_4=lv_obj_has_state(ui->USB_control_2_sw_4, LV_STATE_CHECKED);					 /* 返回值：bool类型，开 :1；关: 0 */
	if(flag.control_sw_4==0)
	{
		usb.usb_pin_state[4] = 0;
		Serial.printf("OFF");}
	else if(flag.control_sw_4==1)
	{
		usb.usb_pin_state[4] = 1;
		Serial.printf("ON");}
}
static void USB_control_2_sw_5_event_handler (lv_event_t *e)
{
	void *uui = lv_event_get_user_data(e);
	lv_ui* ui = (lv_ui *)uui;
	flag.control_sw_5=lv_obj_has_state(ui->USB_control_2_sw_5, LV_STATE_CHECKED);					 /* 返回值：bool类型，开 :1；关: 0 */
	if(flag.control_sw_5==0)
	{
		usb.usb_pin_state[3] = 0;
		Serial.printf("OFF");}
	else if(flag.control_sw_5==1)
	{
		usb.usb_pin_state[3] = 1;
		Serial.printf("ON");}
}
static void USB_control_2_sw_6_event_handler (lv_event_t *e)
{
	void *uui = lv_event_get_user_data(e);
	lv_ui* ui = (lv_ui *)uui;
	flag.control_sw_6=lv_obj_has_state(ui->USB_control_2_sw_6, LV_STATE_CHECKED);					 /* 返回值：bool类型，开 :1；关: 0 */
	if(flag.control_sw_6==0)
	{
		usb.usb_pin_state[5] = 0;
		Serial.printf("OFF");}
	else if(flag.control_sw_6==1)
	{
		usb.usb_pin_state[5] = 1;
		Serial.printf("ON");}
}
void events_init_USB_control_2(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->USB_control_2_btn_1, USB_control_2_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->USB_control_2_sw_1, USB_control_2_sw_1_event_handler, LV_EVENT_CLICKED, ui);
	lv_obj_add_event_cb(ui->USB_control_2_sw_2, USB_control_2_sw_2_event_handler, LV_EVENT_CLICKED, ui);
	lv_obj_add_event_cb(ui->USB_control_2_sw_3, USB_control_2_sw_3_event_handler, LV_EVENT_CLICKED, ui);
	lv_obj_add_event_cb(ui->USB_control_2_sw_4, USB_control_2_sw_4_event_handler, LV_EVENT_CLICKED, ui);
	lv_obj_add_event_cb(ui->USB_control_2_sw_5, USB_control_2_sw_5_event_handler, LV_EVENT_CLICKED, ui);
	lv_obj_add_event_cb(ui->USB_control_2_sw_6, USB_control_2_sw_6_event_handler, LV_EVENT_CLICKED, ui);
}
static void USB_Change_3_btn_1_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.start_screen_1, guider_ui.start_screen_1_del, &guider_ui.USB_Change_3_del, setup_scr_start_screen_1, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, true, true);
		break;
	}
	default:
		break;
	}
}
static void USB_Change_3_sw_1_event_handler (lv_event_t *e)
{
	void *uui = lv_event_get_user_data(e);
	lv_ui* ui = (lv_ui *)uui;
	flag.change_usb_sw1=lv_obj_has_state(ui->USB_Change_3_sw_1, LV_STATE_CHECKED);					 /* 返回值：bool类型，开 :1；关: 0 */
	
	if(flag.change_usb_sw1==0)
	{
		flag.change_usb_sw2=1;
		lv_obj_add_state(ui->USB_Change_3_sw_2, LV_STATE_CHECKED);
		Serial.printf("OFF");
		}
	else if(flag.change_usb_sw1==1)
	{
		Input_Signal_Set(typec1);
		flag.change_usb_sw2=0;
		lv_obj_clear_state(ui->USB_Change_3_sw_2, LV_STATE_CHECKED);
		Serial.printf("ON");}
}
static void USB_Change_3_sw_2_event_handler (lv_event_t *e)
{
	void *uui = lv_event_get_user_data(e);
	lv_ui* ui = (lv_ui *)uui;
	flag.change_usb_sw2=lv_obj_has_state(ui->USB_Change_3_sw_2, LV_STATE_CHECKED);					 /* 返回值：bool类型，开 :1；关: 0 */
	
	if(flag.change_usb_sw2==0)
	{
		flag.change_usb_sw1=1;
		lv_obj_add_state(ui->USB_Change_3_sw_1, LV_STATE_CHECKED);
		Serial.printf("OFF");}
	else if(flag.change_usb_sw2==1)
	{
		Input_Signal_Set(typec2);
		flag.change_usb_sw1=0;
		lv_obj_clear_state(ui->USB_Change_3_sw_1, LV_STATE_CHECKED);
		Serial.printf("ON");}
}
void events_init_USB_Change_3(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->USB_Change_3_btn_1, USB_Change_3_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->USB_Change_3_sw_1, USB_Change_3_sw_1_event_handler, LV_EVENT_CLICKED, ui);
	lv_obj_add_event_cb(ui->USB_Change_3_sw_2, USB_Change_3_sw_2_event_handler, LV_EVENT_CLICKED, ui);
}
static void USB_Data_4_btn_1_event_handler (lv_event_t *e)
{
	// lv_timer_del(task_timer);
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_timer_del(task_timer);//删除定时器句柄，避免不必要的内存占用导致重启芯片
		ui_load_scr_animation(&guider_ui, &guider_ui.start_screen_1, guider_ui.start_screen_1_del, &guider_ui.USB_Data_4_del, setup_scr_start_screen_1, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, true, true);
		break;
	}
	default:
		break;
	}
}
static void USB_Data_4_arc_1_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		
		break;
	}
	default:
		break;
	}
}
static void USB_Data_4_arc_4_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		
		break;
	}
	default:
		break;
	}
}

void create_100ms_timer(void) {  
    /* 创建一个定时器 */  
	task_timer = lv_timer_create(timer_callback, 100, 0);
 
} 
void events_init_USB_Data_4(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->USB_Data_4_btn_1, USB_Data_4_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->USB_Data_4_arc_1, USB_Data_4_arc_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->USB_Data_4_arc_4, USB_Data_4_arc_4_event_handler, LV_EVENT_ALL, ui);
	create_100ms_timer();

}
static void timer_callback(lv_timer_t * timer) {  
    /* 这里编写定时器到期时需要执行的代码 */
    usb_data_up(&guider_ui);
}  
void usb_data_up(lv_ui *ui)
{
  lv_arc_set_value(ui->USB_Data_4_arc_1, (int)(adc_voltage[0]*100));
  lv_arc_set_value(ui->USB_Data_4_arc_2, (int)(adc_voltage[1]*100));
  lv_arc_set_value(ui->USB_Data_4_arc_3, (int)(adc_voltage[2]*100));
  lv_arc_set_value(ui->USB_Data_4_arc_4, (int)(adc_voltage[3]*100));
  lv_arc_set_value(ui->USB_Data_4_arc_5, (int)(adc_voltage[4]*100));
  lv_arc_set_value(ui->USB_Data_4_arc_6, (int)(adc_voltage[5]*100));
 
  snprintf(buffer_1, sizeof(buffer_1), "%.2f", adc_voltage[0]);//float到char的类型转换
  snprintf(buffer_2, sizeof(buffer_2), "%.2f", adc_voltage[1]);
  snprintf(buffer_3, sizeof(buffer_3), "%.2f", adc_voltage[2]);
  snprintf(buffer_4, sizeof(buffer_4), "%.2f", adc_voltage[3]);
  snprintf(buffer_5, sizeof(buffer_5), "%.2f", adc_voltage[4]);
  snprintf(buffer_6, sizeof(buffer_6), "%.2f", adc_voltage[5]);
  lv_label_set_text(ui->USB_Data_4_label_1, buffer_1);
  lv_label_set_text(ui->USB_Data_4_label_2, buffer_2);
  lv_label_set_text(ui->USB_Data_4_label_3, buffer_3);
  lv_label_set_text(ui->USB_Data_4_label_4, buffer_4);
  lv_label_set_text(ui->USB_Data_4_label_5, buffer_5);
  lv_label_set_text(ui->USB_Data_4_label_6, buffer_6);
}
static void Set_5_btn_1_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.start_screen_1, guider_ui.start_screen_1_del, &guider_ui.Set_5_del, setup_scr_start_screen_1, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
		break;
	}
	default:
		break;
	}
}
static void Set_5_btn_2_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.start_screen_1, guider_ui.start_screen_1_del, &guider_ui.Set_5_del, setup_scr_start_screen_1, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true, true);
		break;
	}
	default:
		break;
	}
}
static void Set_5_btn_3_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.start_screen_1, guider_ui.start_screen_1_del, &guider_ui.Set_5_del, setup_scr_start_screen_1, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true, true);
		break;
	}
	default:
		break;
	}
}
void events_init_Set_5(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->Set_5_btn_1, Set_5_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->Set_5_btn_2, Set_5_btn_2_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->Set_5_btn_3, Set_5_btn_3_event_handler, LV_EVENT_ALL, ui);
}

void events_init(lv_ui *ui)
{

}
