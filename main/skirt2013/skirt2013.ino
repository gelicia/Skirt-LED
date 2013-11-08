#include "LPD8806.h"
#include "SPI.h"

int palette[] = {
   48, 96, 144, 192, 240, 288, 336, 384
};

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

int spaceInvaders[] PROGMEM = {
  0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0,  0, 0, 0, 0, 1, 1, 0, 0, 0, 
  0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,  0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0,  0, 0, 0, 2, 2, 2, 2, 0, 0, 
  0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,  0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 0, 0,  0, 0, 3, 3, 3, 3, 3, 3, 0, 
  0, 4, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 4,  0, 0, 4, 4, 0, 4, 4, 4, 0, 4, 4, 0,  0, 4, 4, 0, 4, 4, 0, 4, 4, 
  0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,  0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,  0, 5, 5, 5, 5, 5, 5, 5, 5, 
  0, 0, 0, 0, 6, 6, 0, 0, 6, 6, 0, 0, 0,  0, 6, 0, 6, 6, 6, 6, 6, 6, 6, 0, 6,  0, 0, 0, 6, 0, 0, 6, 0, 0, 
  0, 0, 0, 7, 7, 0, 7, 7, 0, 7, 7, 0, 0,  0, 7, 0, 7, 0, 0, 0, 0, 0, 7, 0, 7,  0, 0, 7, 0, 7, 7, 0, 7, 0, 
  0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8,  0, 0, 0, 0, 8, 8, 0, 8, 8, 0, 0, 0,  0, 8, 0, 8, 0, 0, 8, 0, 8, 
};

int spaceInvaders2[] PROGMEM = {
  0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0,  0, 0, 0, 0, 1, 1, 0, 0, 0, 
  0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,  0, 2, 0, 0, 2, 0, 0, 0, 2, 0, 0, 2,  0, 0, 0, 2, 2, 2, 2, 0, 0, 
  0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,  0, 3, 0, 3, 3, 3, 3, 3, 3, 3, 0, 3,  0, 0, 3, 3, 3, 3, 3, 3, 0, 
  0, 4, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 4,  0, 4, 4, 4, 0, 4, 4, 4, 0, 4, 4, 4,  0, 4, 4, 0, 4, 4, 0, 4, 4, 
  0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,  0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,  0, 5, 5, 5, 5, 5, 5, 5, 5, 
  0, 0, 6, 6, 0, 0, 6, 6, 0, 0, 6, 6, 0,  0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0,  0, 0, 0, 6, 0, 0, 6, 0, 0, 
  0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,  0, 0, 0, 0, 7, 0, 0, 0, 7, 0, 0, 0,  0, 0, 7, 0, 7, 7, 0, 7, 0, 
  0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 8, 8, 0,  0, 0, 0, 8, 0, 0, 0, 0, 0, 8, 0, 0,  0, 8, 0, 0, 0, 0, 0, 0, 8,
};

 int clearScreen[] PROGMEM = { 
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

 int fullScreen[] PROGMEM = { 
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1
};

struct Image {
  int width, height, *pixels;
};

struct Image party_image = {
  43, 8, party
};

struct Image spaceInv_image = {
  34, 8,
  spaceInvaders
};

struct Image spaceInv2_image = {
  34, 8,
  spaceInvaders2
};

struct Image clear_image = {
   8, 8,
   clearScreen
};

struct Image full_image = {
   8, 8,
   fullScreen
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
  //scrollImage(&party_image, 60);
  //setLED(0,0,128);
  //strip.setPixelColor(39, strip.Color(0,   0, 127));
  //strip.show();
  
  scrollAndAlternateImage(&spaceInv_image, &spaceInv2_image, 4, 90);
  
  //displayImage(full_image);
}

void displayImage(struct Image image){
  int width = image.width;
  const int* pixels = image.pixels;
  
  for(int y=0; y<LEDsH; y++){
     for(int x=0; x<LEDsW; x++){
       int colorIdx = pgm_read_byte(&pixels[y*width + x%width]);
       int color = 0;
       if (colorIdx != 0){
         color = palette[colorIdx-1];
       }
       setLED(x, y, color); 
        
     } 
   }
    strip.show();
}

//todo fix to be dynamic
void scrollImage(struct Image *image, int del){
  int width = image->width;
  const int *pixels = image->pixels;
  //strip.show();
  //iterate through each column of the image at an offset
  for(int i=0; i<width; i++){
    //update the display
    for(int y=0; y<LEDsH; y++){
      for(int x=0; x<LEDsW; x++){
        int colorIdx = pgm_read_byte(&pixels[y*width + (x + i)%width]);
        int color = 0;
        if (colorIdx != 0){
          color = palette[colorIdx-1];
        }
        setLED(x, y, color); 
        
      } 
    }
    strip.show();
    delay(del);
  }
}

//Alternate between two images while scrolling
void scrollAndAlternateImage(struct Image *image1, struct Image *image2, int altDelay, int del){
  int width = image1->width;
  
  //iterate through each column of the image at an offset
  for(int i=0; i<width; i++){
    const int *pixels ;
    if (i&altDelay) {
      pixels = image1->pixels;
    }
    else {
     pixels = image2->pixels;
    }
    
    //update the display
    for(int y=0; y<8; y++){
      for(int x=0; x<10; x++){
        int colorIdx = pgm_read_byte(&pixels[y*width + (x + i)%width]);
        int color = 0;
        if (colorIdx != 0){
          color = palette[colorIdx-1];
        }
        setLED(x, y, color);
      } 
    }
    strip.show();
    delay(del);
  }
}


//sets an LED of x,y 
//color is 0-385, with 0 being off
void setLED(uint32_t x, uint32_t y, uint32_t color){
  int ledAddr = (8 * (9-x)) + (((x&1)==0)?(7-y):(y));
  strip.setPixelColor(ledAddr, color==0?color:Wheel(color-1));
}

void clearLEDs(){
  for(int y=0; y<LEDsH; y++){
    for(int x=0; x<LEDsW; x++){
      setLED(x,y,0);
    }
  }
}

//Input a value 0 to 384 to get a color value.
//The colours are a transition r - g -b - back to r

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
