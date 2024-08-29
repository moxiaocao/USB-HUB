#USB-HUB-tree
```
hub-end
├─ .gitignore
├─ .vscode
│  ├─ extensions.json
│  └─ settings.json
├─ include
│  └─ README
├─ lib
│  ├─ adc_usb
│  │  ├─ adc_usb.cpp
│  │  ├─ adc_usb.h
│  │  └─ 备份.txt
│  ├─ Bool
│  │  ├─ Bool.cpp
│  │  └─ Bool.h
│  ├─ control_usb
│  │  ├─ control_usb.cpp
│  │  └─ control_usb.h
│  ├─ encoder
│  │  ├─ encoder.cpp
│  │  └─ encoder.h
│  ├─ README
│  ├─ src
│  │  ├─ custom
│  │  │  ├─ custom.c
│  │  │  ├─ custom.h
│  │  │  └─ lv_conf_ext.h
│  │  └─ generated
│  │     ├─ events_init.cpp
│  │     ├─ events_init.h
│  │     ├─ guider_customer_fonts
│  │     │  └─ guider_customer_fonts.h
│  │     ├─ guider_fonts
│  │     │  ├─ lv_font_1_12.c
│  │     │  ├─ lv_font_1_16.c
│  │     │  ├─ lv_font_1_22.c
│  │     │  ├─ lv_font_Acme_Regular_12.c
│  │     │  ├─ lv_font_Acme_Regular_16.c
│  │     │  ├─ lv_font_Acme_Regular_18.c
│  │     │  ├─ lv_font_Alatsi_Regular_18.c
│  │     │  ├─ lv_font_Alatsi_Regular_22.c
│  │     │  ├─ lv_font_FontAwesome5_22.c
│  │     │  ├─ lv_font_FZSTK_12.c
│  │     │  ├─ lv_font_FZSTK_16.c
│  │     │  ├─ lv_font_FZSTK_22.c
│  │     │  ├─ lv_font_montserratMedium_12.c
│  │     │  ├─ lv_font_montserratMedium_16.c
│  │     │  ├─ lv_font_montserratMedium_18.c
│  │     │  ├─ lv_font_montserratMedium_20.c
│  │     │  ├─ lv_font_montserratMedium_29.c
│  │     │  ├─ lv_font_SourceHanSerifSC_Regular_12.c
│  │     │  └─ lv_font_SourceHanSerifSC_Regular_18.c
│  │     ├─ gui_guider.c
│  │     ├─ gui_guider.h
│  │     ├─ images
│  │     │  ├─ images_md5.json
│  │     │  ├─ lottie_1.c
│  │     │  ├─ lottie_2.c
│  │     │  ├─ lottie_3.c
│  │     │  ├─ _4_alpha_100x100.c
│  │     │  ├─ _gps2_alpha_30x30.c
│  │     │  ├─ _gps_alpha_52x50.c
│  │     │  ├─ _pass_alpha_30x30.c
│  │     │  ├─ _temp2_alpha_47x42.c
│  │     │  ├─ _temp_alpha_52x50.c
│  │     │  ├─ _weater_alpha_52x50.c
│  │     │  └─ _wifi_alpha_30x30.c
│  │     ├─ setup_scr_Set_5.c
│  │     ├─ setup_scr_start_screen_1.c
│  │     ├─ setup_scr_USB_Change_3.c
│  │     ├─ setup_scr_USB_control_2.c
│  │     ├─ setup_scr_USB_Data_4.c
│  │     ├─ widgets_init.c
│  │     └─ widgets_init.h
│  ├─ touch
│  │  ├─ touch.cpp
│  │  └─ touch.h
│  ├─ usb_control
│  │  ├─ usb_control.c
│  │  └─ usb_control.h
│  └─ weather
│     ├─ weather.cpp
│     └─ weather.h
├─ platformio.ini
├─ src
│  └─ main.cpp
└─ test
   ├─ README
   └─ test1.txt

```
##函数注解
#### lvgl库
- lv_conf.h配置
- porting文件夹
   - lv_port_indev.h
- 函数
   - lv_timer_t * lv_timer_create(lv_timer_cb_t timer_xcb, uint32_t period, void * user_data)lvgl自带定时器
#### TFT-eSPI库
   - User_Setup.h配置
   - 函数
#### XPT2046库
   - 引脚配置
   - 接入lvgl的indev文件函数