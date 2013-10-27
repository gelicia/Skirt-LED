#include "LPD8806.h"
#include "SPI.h"

typedef struct Pos {
  int x, y;
} Pos;

typedef struct Piece {
  int color;
  int rotationCount;
  Pos *rotations;
} Piece;

Pos oPiece_rotations [][4] = {
  {{0,0}, {0,-1}, {1,0}, {1,-1}}
};

Pos lPiece_rotations [][4] = {
  {{0,0}, {1,0}, {-1,0}, {-1,1}},
  {{0,0}, {0,1}, {0,-1}, {-1,-1}},
  {{0,0}, {-1,0}, {1,0}, {1,-1}},
  {{0,0}, {0,-1}, {0,1}, {1,1}},
};

Pos jPiece_rotations [][4] = {
  {{0,0}, {-1,0}, {1,0}, {1,1}},
  {{0,0}, {0,-1}, {0,1}, {-1,1}},
  {{0,0}, {1,0}, {-1,0}, {-1,-1}},
  {{0,0}, {0,1}, {0,-1}, {1,-1}}
};

Pos iPiece_rotations [][4] = {
  {{0,0}, {-1,0}, {1,0}, {2,0}},
  {{0,0}, {0,1}, {0,-1}, {0,-2}}
};

Pos sPiece_rotations [][4] = {
  {{0,0}, {1,0}, {0,1}, {-1,1}},
  {{0,0}, {0,1}, {1,1}, {1,2}}
};

Pos zPiece_rotations [][4] = {
  {{0,0}, {-1,0}, {0,1}, {1,1}},
  {{0,0}, {0,-1}, {-1,0}, {-1,1}}
};

Pos tPiece_rotations [][4] = {
  {{0,0}, {-1,0}, {1,0}, {0,-1}},
  {{0,0}, {0,-1}, {1,0}, {0,1}},
  {{0,0}, {-1,0}, {0,1}, {1,0}},
  {{0,0}, {0,-1}, {-1,0}, {0,1}}
};

Piece pieces[] = {
 {326, 1, (struct Pos*)oPiece_rotations}, //o square block
 {356, 4, (struct Pos*)lPiece_rotations}, //l block
 {122, 4, (struct Pos*)jPiece_rotations}, //j block
 {288, 2, (struct Pos*)sPiece_rotations}, //s block
 {384, 2, (struct Pos*)zPiece_rotations}, //z block
 {192, 2, (struct Pos*)iPiece_rotations}, //I long block
 {19, 4, (struct Pos*)tPiece_rotations} //t block
};

int points = 0;
int fallRate = 1;
int turns = 0;
int joystickValX = 0;
int joystickValY = 0;
int joystickSelect = 0;
const int MAX_SPEED = 5;

int LEDsW = 10;
int LEDsH = 8;
int dataPin = 2;
int clockPin = 3;
LPD8806 strip = LPD8806(LEDsW * LEDsH, dataPin, clockPin);

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show();
}

void loop() {
  int turnsPerDrop = fallRate; 
  
  if (turns > turnsPerDrop){
     turns = 0;
     
     
  }
  else {
    turns++; 
  }
  
  displayPiece(pieces[1], pieces[1].color, 0, 4, 5);
  
}

void displayPiece(struct Piece p, int pieceColor, int rotIdx, int baseX, int baseY){
  Pos *rotation = p.rotations + (4*rotIdx);
  for (int i=0; i<=4; i++){
    setLED(rotation[i].x + baseX, rotation[i].y+baseY, pieceColor);
  }
  strip.show();
}


/*LED utility functions*/
void setLED(uint32_t x, uint32_t y, uint32_t color){
  int ledAddr = (8 * (9-x)) + (((x&1)==0)?(7-y):(y));
  strip.setPixelColor(ledAddr, color==0?color:Wheel(color-1));
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


