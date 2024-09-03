# USB-HUB-tree
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
# 工程使用ESP32-S3-N16R8主控，ST7789V显示驱动和XPT2046触摸驱动，显示屏尺寸为320×240，使用vc-code编译arduino环境
## 软件配置及注解
### 库配置注解
#### lvgl库
- lv_conf.h配置
   - #define LV_MEM_SIZE (80U * 1024U)          /*[bytes]*/一般48就够了，我给的多，这是分配给lvgl的内存，内存过少，会导致内存堆栈溢出芯片重启，内存过多会导致wifi不够内存分配，芯片不断**重启**。
   - #define LV_DISP_DEF_REFR_PERIOD 5      /*[ms]*/这个时间是lvgl刷新的时间，我设置的5ms，即1000ms/5ms=200，理论上达到200帧率。一般设置为10ms，即100帧。
   - #define LV_TICK_CUSTOM 1   1为使用lvgl的内存管理，否则使用别的内存管理方式，如果动画不动，基本上就是它没置1
   - /*Color depth: 1 (1 byte per pixel), 8 (RGB332), 16 (RGB565), 32 (ARGB8888)*/
      #define LV_COLOR_DEPTH 16  这里设置显示屏的RGB格式
- porting文件夹
   - lv_port_indev.h
- 函数
   - lv_timer_t * lv_timer_create(lv_timer_cb_t timer_xcb, uint32_t period, void * user_data)lvgl自带定时器
   lv_timer_create函数为lvgl自带的定时器功能，第一个参数为定时器回调函数，第二个参数为定时时间，ms为单位，第三个参数可以为0.
   其中定时器回调函数static void timer_callback(lv_timer_t * timer)的形参为定时器句柄，lv_timer_t* task_timer;需要先定义再引用。
   lv_timer_del(task_timer);//删除定时器句柄，避免不必要的内存占用导致**重启**芯片；如果不删除，有可能导致内存资源占用过多，芯片不断重启。
#### TFT-eSPI库
   - User_Setup.h配置
   - 函数
      -    tft.setRotation( 1 ); /* Landscape orientation, flipped */  设置屏幕方向，参数为0-3
           tft.invertDisplay(0);   如果设置了lvgl的RGB格式后，显示的颜色仍然不对，则开启这个设置，0为正常，1为反相
#### XPT2046库
   - 引脚配置
   - 接入lvgl的indev文件函数(部分)
   ``` 
   /*Initialize your touchpad*/
   static void touchpad_init(void)
   {
      /*Your code comes here*/
      touch_init();
   }

   /*Return true is the touchpad is pressed*/
   static bool touchpad_is_pressed(void)
   {
      /*Your code comes here*/
      touch_scan();
      if (touch.zRaw != 0) {
         return true;
      }
      return false;
   }

   /*Get the x and y coordinates if the touchpad is pressed*/
   static void touchpad_get_xy(lv_coord_t * x, lv_coord_t * y)
   {
      /*Your code comes here*/
      (*x) = touch.x;
      (*y) = 240-(touch.y);//我的屏幕坐标反了，正常的话不用240-y
   }
   ```
   这里主要是检测按下、xy坐标传递。

   值得注意的是
   ```
   static lv_indev_drv_t indev_drv;
   ```
   每一个输入设备只对应一个indev_drv，如果有两个三个四个，则需要有indev_drv_1,indev_drv_2...等，否则输入设备无法使用

### Guide生成的代码文件
│  ├─ src
│  │  ├─ custom
│  │  └─ generated
其中，custom是存放用户代码，但是在使用guide和vccode联合调试的情况下使用，我只需要界面，所以忽略此文件夹、
generated是界面代码和回调函数文件夹，events_init.cpp中存放所有部件、页面的回调函数，后续需要部件按下有什么反馈或者回调函数，都要在里面找到相应的部件的回调函数，在里面写。
以setup开头文件就是生成每个页面的代码，需要修改部件等可一一对应找到。
gui_guider.c文件中
```
void setup_ui(lv_ui *ui)
{
	init_scr_del_flag(ui);
	setup_scr_start_screen_1(ui);
	lv_scr_load(ui->start_screen_1);
}
```
此处设置起始页面
```
lv_ui guider_ui;
setup_ui(&guider_ui);
events_init(&guider_ui);
```
初始化页面初始化函数和回调函数总初始化才能正确显示页面和部件回调
