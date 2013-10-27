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
int ticks = 0;

int xOffset;
int yOffset;
int pieceIdx;
int rotIdx;

int xSensorPin = A1;
int ySensorPin = A0;
int selectButtonPin = 12;

int xJoystickOffset = 0; 
int yJoystickOffset = 0; 

const int LEFT_THRESHOLD = 20;
const int RIGHT_THRESHOLD = 1000;

const int MAX_SPEED = 5;

const int LEDsW = 10;
const int LEDsH = 8;
int dataPin = 2;
int clockPin = 3;
LPD8806 strip = LPD8806(LEDsW * LEDsH, dataPin, clockPin);

uint32_t blocks[LEDsW][LEDsH] = {};

void setup() {
  Serial.begin(9600);
  
  pinMode(selectButtonPin, INPUT);
  
  strip.begin();
  strip.show();
  randomSeed(analogRead(A2));
  random(0,7); //call it once because it always started with 0
  
  yOffset = 3;
  xOffset = 3;
  pieceIdx = 4;//random(0,7);
  rotIdx = 1;
  
  for(int i=0; i<LEDsW; i++){
    for(int j=0; j<LEDsH; j++){
      blocks[i][j] = 0;
    }
  }
}

void loop() {
  int ticksPerDrop = 20; //20 ticks before the piece moves down
  
  int joyX = analogRead(xSensorPin);  
  int joyY = analogRead(ySensorPin);  
  
  //record left or right joystick push
  if (joyX < 20){
    xJoystickOffset = 1;
  }
  else if (joyX > 1000){
   xJoystickOffset = -1; 
  }
  else if (490 < joyX && joyX < 510){
    xJoystickOffset = 0;
  }
  
  //record up or down joystick push
  if (joyY < 20){
    yJoystickOffset = 1;
  }
  else if (joyY > 1000){
   yJoystickOffset = -1; 
  }
  else if (490 < joyY && joyY < 510){
    yJoystickOffset = 0;
  }
  
  //if there was a joystick left or right push, move the piece
  if (xJoystickOffset != 0) {
     tryMove(rotIdx, xOffset + xJoystickOffset, yOffset);
  }
  
  //if there was a joystick up or down push, rotate or move down
  if(yJoystickOffset == 1){
    int rotation = (rotIdx + 1) % (pieces[pieceIdx].rotationCount);
    tryMove(rotation, xOffset, yOffset);
  } else if(yJoystickOffset == -1){
    tryMove(rotIdx, xOffset, yOffset + 1);
  }
  
  if (ticks > ticksPerDrop){
     ticks = 0;
     if(!tryMove(rotIdx, xOffset, yOffset + 1)) { //reset if reached bottom
       //save the screen
       setBlocks(xOffset, yOffset);
       clearRows();
       
       // setup new piece.
       xOffset = 3;
       yOffset = -2; 
       rotIdx = 0;
       pieceIdx = random(0,7);
     }
  }
  else {
    ticks++; 
  }
  
  strip.show();
  delay(100); 
}

//saves the screen in a array
void setBlocks(int posX, int posY)
{
  Pos *offsets = pieces[pieceIdx].rotations + (4 * rotIdx);
  uint32_t color = pieces[pieceIdx].color;
  
  for(int i=0; i<4; i++){
    int x = posX + offsets[i].x;
    int y = posY + offsets[i].y;
    
    if(0 <= x && x < LEDsW && 0 <= y && y < LEDsH){
      blocks[x][y] = color;
    }
  }
}

/* 
erases the old position of the piece
if the position is a valid place, it changes the values
if the position is not, it does nothing

it draws the shape with the values, changed or not*/
bool tryMove(int rotation, int posX, int posY)
{
   //set the old location to be black
   displayPiece(0, xOffset, yOffset);
   
   bool unblocked = checkMove(rotation, posX, posY);
   if(unblocked){
     xOffset = posX;
     yOffset = posY;
     rotIdx = rotation;
   }
   
   displayPiece(pieces[pieceIdx].color, xOffset, yOffset);
   
   return unblocked;
}

//ensures the move doesn't run into other pieces and returns true or false if the move is valid
bool checkMove(int rotation, int posX, int posY)
{
  Pos *offsets = pieces[pieceIdx].rotations + (4* rotation);
  
  for(int i=0; i<4; i++){
    int x = posX + offsets[i].x;
    int y = posY + offsets[i].y;
    
    if(y >= LEDsH){
      return false;
    } else if(x < 0 || LEDsW <= x){
      return false;
    } else if(y > 0 && blocks[x][y] != 0){
      return false;
    }
  }
  
  return true;
}

bool rowIsFull(int row){
  for (int i=0; i<LEDsW; i++){
    if(blocks[i][row] == 0) {return false; }
  }
  
  return true;
}

void clearRows(){
  for (int row = LEDsH-1; row>=0; row--){
    while (rowIsFull(row)){
      clearRow(row);
      strip.show();
      delay(50);
      moveDownFrom(row);
      strip.show();
      delay(50);
    }
  }
}

void clearRow (int row) {
  for (int i=0; i<LEDsW; i++){
    setLED(i, row, 0);  
    blocks[i][row] = 0;
  }
}

void moveDownFrom(int row){
 for  (int y = row-1; y>=0; y--){
  for (int x = 0; x < LEDsW; x++){
   setLED(x, y+1, blocks[x][y]);
   blocks[x][y+1] = blocks[x][y];
  } 
 }
 
 clearRow(0);
}

void displayPiece(int pieceColor, int baseX, int baseY){
  Pos *offsets = pieces[pieceIdx].rotations + (4* rotIdx);
  
  for (int i=0; i<4; i++){
    int newX = offsets[i].x + baseX;
    int newY = offsets[i].y + baseY;

    setLED(newX, newY, pieceColor);
  }
}

/*LED utility functions*/
void setLED(int x, int y, uint32_t color){
  int ledAddr = (8 * (9-x)) + (((x&1)==0)?(7-y):(y));
  if (0 <= x && x < LEDsW && 0 <= y && y < LEDsH){
    strip.setPixelColor(ledAddr, color==0?color:Wheel(color-1));    
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


