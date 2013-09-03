#include "LPD8806.h"
#include "SPI.h"

// Example to control LPD8806-based RGB LED Modules in a strip
// Written by Leon Durivage @neutronned

/*****************************************************************************/

// Number of RGB LEDs in strand:
int LEDsW = 10;
int LEDsH = 8;

// Chose 2 pins for output; can be any valid output pins:
int dataPin  = 2;
int clockPin = 3;

LPD8806 strip = LPD8806(LEDsW * LEDsH, dataPin, clockPin);
long c;

//start, default off
void setup() {
  strip.begin();
  c=0xC97F5B;//random(0xFFFFFF);
  strip.show();
}

void loop() {
  int i;
  //long c;
  
  //c=random(0xFFFFFF);
  
  setLED(5,5,128);
//  strip.setPixelColor(39, strip.Color(0,   0, 127));
  strip.show();
}

void setLED(uint32_t x, uint32_t y, uint32_t color){
  int ledAddr = (8 * (9-x)) + (x&1==0?(7-y):y);
  strip.setPixelColor(ledAddr, Wheel(color));
}

uint32_t Wheel(uint16_t WheelPos)
{
  byte r, g, b;
  switch(WheelPos / 128)
  {
    case 0:
      r = 127 - WheelPos % 128;   //Red down
      g = WheelPos % 128;      // Green up
      b = 0;                  //blue off
      break; 
    case 1:
      g = 127 - WheelPos % 128;  //green down
      b = WheelPos % 128;      //blue up
      r = 0;                  //red off
      break; 
    case 2:
      b = 127 - WheelPos % 128;  //blue down 
      r = WheelPos % 128;      //red up
      g = 0;                  //green off
      break; 
  }
  return(strip.Color(r,g,b));
}
