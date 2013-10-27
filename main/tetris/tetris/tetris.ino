#include "LPD8806.h"

struct Pos {
  int x, y;
};

struct Piece {
  int rotationCount;
  Pos *rotations;
};

int palette[] = {
   48, 96, 144, 192, 240, 288, 336, 384
};

struct Pos oPiece_rotations [][4] PROGMEM = {
  {{0,0}, {0,-1}, {1,0}, {1,-1}}
};

struct Pos lPiece_rotations [][4] PROGMEM = {
  {{0,0}, {1,0}, {-1,0}, {-1,1}},
  {{0,0}, {0,1}, {0,-1}, {-1,-1}},
  {{0,0}, {-1,0}, {1,0}, {1,-1}},
  {{0,0}, {0,-1}, {0,1}, {1,1}},
};

struct Pos jPiece_rotations [][4] PROGMEM = {
  {{0,0}, {-1,0}, {1,0}, {1,1}},
  {{0,0}, {0,-1}, {0,1}, {-1,1}},
  {{0,0}, {1,0}, {-1,0}, {-1,-1}},
  {{0,0}, {0,1}, {0,-1}, {1,-1}}
};

struct Pos iPiece_rotations [][4] PROGMEM = {
  {{0,0}, {-1,0}, {1,0}, {2,0}},
  {{0,0}, {0,1}, {0,-1}, {0,-2}}
};

struct Pos sPiece_rotations [][4] PROGMEM = {
  {{0,0}, {1,0}, {0,1}, {-1,1}},
  {{0,0}, {0,1}, {1,1}, {1,2}}
};

struct Pos zPiece_rotations [][4] PROGMEM = {
  {{0,0}, {-1,0}, {0,1}, {1,1}},
  {{0,0}, {0,-1}, {-1,0}, {-1,1}}
};

struct Pos tPiece_rotations [][4] PROGMEM = {
  {{0,0}, {-1,0}, {1,0}, {0,-1}},
  {{0,0}, {0,-1}, {1,0}, {0,1}},
  {{0,0}, {-1,0}, {0,1}, {1,0}},
  {{0,0}, {0,-1}, {-1,0}, {0,1}}
};

struct Piece pieces[] PROGMEM = {
 {1, (struct Pos*)oPiece_rotations}, //square
 {4, (struct Pos*)lPiece_rotations}, //l block
 {4, (struct Pos*)jPiece_rotations}, //j block
 {2, (struct Pos*)sPiece_rotations}, //s block
 {2, (struct Pos*)zPiece_rotations}, //z block
 {2, (struct Pos*)iPiece_rotations}, //long block
 {4, (struct Pos*)tPiece_rotations} //t block
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

}

void loop() {
  int turnsPerDrop = fallRate; 
  
  if (turns > turnsPerDrop){
     turns = 0;
     
     
  }
  else {
    turns++; 
  }
  
}
