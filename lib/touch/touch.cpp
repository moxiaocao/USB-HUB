#include <Arduino.h>
#include <../XPT2046_Bitbang_Slim/XPT2046_Bitbang.h>

#define MOSI_PIN 42
#define MISO_PIN 41
#define CLK_PIN  1
#define CS_PIN   2

XPT2046_Bitbang touchscreen(MOSI_PIN, MISO_PIN, CLK_PIN, CS_PIN,320,240);
TouchPoint touch;  

void touch_init(void) {
  
  touchscreen.begin();
}

void touch_scan(void) {   
    touch = touchscreen.getTouch();
  
  if (touch.zRaw != 0) {
    // Serial.print("Touch at X: ");
    // Serial.print(touch.x);
    // Serial.print(", Y: ");
    // Serial.println(touch.y);
  }

//   delay(10);  // Adjust delay as needed for responsiveness vs. serial output frequency
}
