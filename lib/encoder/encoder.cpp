 
#include <Arduino.h>
 
#include <ESP32Encoder.h>
 
//按键配置
#define EC11_A_PIN 10
#define EC11_B_PIN 9
 
ESP32Encoder encoder;
 
 
void ec11_init(void)
{ 
  encoder.attachSingleEdge(EC11_A_PIN, EC11_B_PIN);
}
 
int lastEncoderValue = 0;
 
void ec11_scan(void)
{
  if (lastEncoderValue != encoder.getCount())
  {
    int now_count = encoder.getCount();
    
    if (now_count > lastEncoderValue)
    {
      Serial.println("left");
    }
    else
    {
      Serial.println("right");
    }
    
    lastEncoderValue = now_count;
    Serial.print("Encoder value: ");
    Serial.println(lastEncoderValue);
  }
}