#include "LPD8806.h"
#include "SPI.h"

int party[] PROGMEM = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0,
  0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
  1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0,
  1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
};


struct Image {
int width, height, *pixels;
};

struct Image party_image = {
  43, 8, party
};

// Number of RGB LEDs in strand:
int LEDsW = 10;
int LEDsH = 8;

// Chose 2 pins for output; can be any valid output pins:
int dataPin  = 2;
int clockPin = 3;

LPD8806 strip = LPD8806(LEDsW * LEDsH, dataPin, clockPin);

//start, default off
void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show();
}

void loop() {
  scrollImage(&party_image, 0);
//  setLED(5,5,128);
//  strip.setPixelColor(39, strip.Color(0,   0, 127));
 // strip.show();
}

void scrollImage(struct Image *image, int del){
  int width = image->width;
  const int *pixels = image->pixels;
  strip.show();
  //iterate through each column of the image at an offset
  for(int i=0; i<width; i++){
    //update the display
    for(int y=0; y<width; y++){
      for(int x=0; x<width; x++){
        int what = pgm_read_byte(&pixels[y*width + (x + i)%width]);
        if (what == 1){
         setLED(x, y, 128); 
        }
        else {
          setLED(x, y, 0); 
        }
        Serial.println(what);
      } 
    }
    strip.show();
    delay(del);
  }
}

void setLED(uint32_t x, uint32_t y, uint32_t color){
  int ledAddr = (8 * (9-x)) + (x&1==0?(7-y):y);
  strip.setPixelColor(ledAddr, Wheel(color));
}

void clearLEDs(){
  for(int y=0; y<LEDsH; y++){
      for(int x=0; x<LEDsW; x++){
        setLED(x,y,0);
      }
  }
}

//changed so 0 is off
//colors are 1 to 385
uint32_t Wheel(uint16_t WheelPos)
{
  byte r, g, b;
  
  if(WheelPos == 0){
    return 0;
  }
  else {
    //set WheelPos to what it was and use original algorithm
    WheelPos = WheelPos - 1;
    
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
}
