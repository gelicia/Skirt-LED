/*
 * Show messages on an 8x8 led matrix,
 * scrolling from right to left.
 *
 * Uses FrequencyTimer2 library to
 * constantly run an interrupt routine
 * at a specified frequency. This
 * refreshes the display without the
 * main loop having to do anything.
 *
 */

#include <FrequencyTimer2.h>

static byte pacMan[] = {
//1                        2                        3                        4                        5                        6                        7                        8
 0, 0, 0, 1, 1, 1, 1, 0,  0, 0, 0, 1, 1, 1, 0, 0,  0, 0, 0, 1, 1, 1, 0, 0,  0, 0, 0, 1, 1, 1, 0, 0,  0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
 0, 0, 1, 1, 1, 1, 0, 0,  0, 0, 1, 1, 1, 1, 1, 0,  0, 0, 1, 1, 1, 1, 1, 0,  0, 0, 1, 1, 1, 1, 1, 0,  0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
 0, 1, 1, 1, 1, 0, 0, 0,  0, 1, 1, 1, 1, 0, 0, 0,  0, 1, 1, 1, 1, 1, 1, 0,  0, 1, 1, 1, 1, 1, 1, 0,  0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 
 0, 1, 1, 1, 0, 0, 0, 0,  0, 1, 1, 1, 0, 0, 0, 0,  0, 1, 1, 1, 1, 0, 0, 0,  0, 1, 1, 1, 1, 1, 1, 0,  0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 
 0, 1, 1, 1, 1, 0, 0, 0,  0, 1, 1, 1, 1, 0, 0, 0,  0, 1, 1, 1, 1, 1, 1, 0,  0, 1, 1, 1, 1, 1, 1, 0,  0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 
 0, 0, 1, 1, 1, 1, 0, 0,  0, 0, 1, 1, 1, 1, 1, 0,  0, 0, 1, 1, 1, 1, 1, 0,  0, 0, 1, 1, 1, 1, 1, 0,  0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
 0, 0, 0, 1, 1, 1, 1, 0,  0, 0, 0, 1, 1, 1, 0, 0,  0, 0, 0, 1, 1, 1, 0, 0,  0, 0, 0, 1, 1, 1, 0, 0,  0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

static byte pong[] = {
  //1                      2                         3                         4                         5                         6                         7                         8                         9
  0, 0, 0, 0, 1, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 1,  0, 0, 0, 1, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 1, 0, 1, 
  0, 0, 0, 0, 0, 0, 0, 1,  0, 0, 0, 0, 0, 0, 0, 0,   1, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   1, 0, 0, 0, 0, 0, 0, 0,   1, 0, 0, 0, 0, 0, 1, 1,   0, 0, 0, 0, 0, 0, 0, 1, 
  0, 0, 0, 0, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0, 0, 1,   1, 1, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   1, 0, 0, 0, 0, 0, 0, 0,   1, 0, 0, 0, 0, 1, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0, 0, 1,   0, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1,   0, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1,   0, 0, 0, 0, 0, 0, 0, 1,   0, 0, 0, 0, 0, 0, 0, 0,   1, 0, 0, 0, 0, 0, 0, 0, 
  1, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 1,   1, 0, 1, 0, 0, 0, 0, 1,   0, 0, 0, 0, 0, 0, 0, 1,   0, 0, 0, 0, 1, 0, 0, 1,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 
  1, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   1, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   1, 0, 0, 1, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 
};

static byte creeperExplode[] = {
  //1                      2                        3                        4                        5                        6                        7
  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  1, 1, 0, 0, 0, 1, 0, 1,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 1, 1, 0, 0, 1, 1, 0,  0, 1, 1, 0, 0, 0, 0, 0,  0, 1, 1, 0, 0, 1, 1, 0,  0, 1, 1, 0, 1, 1, 1, 0,  1, 0, 1, 0, 1, 0, 1, 0,  1, 0, 1, 0, 1, 0, 1, 0,  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 1, 1, 0, 0, 1, 1, 0,  0, 1, 1, 0, 0, 1, 1, 0,  0, 1, 1, 1, 1, 1, 1, 0,  0, 1, 0, 1, 0, 0, 1, 0,  0, 1, 0, 1, 0, 0, 0, 1,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 1, 1, 0, 0, 0,  0, 0, 0, 1, 1, 0, 0, 0,  0, 0, 1, 0, 0, 1, 0, 0,  0, 0, 1, 0, 0, 1, 0, 0,  1, 0, 0, 0, 0, 0, 1, 0,  1, 0, 0, 0, 0, 0, 1, 0,  0, 0, 1, 0, 1, 0, 0, 0, 
  0, 0, 1, 1, 1, 1, 0, 0,  0, 0, 1, 1, 1, 1, 0, 0,  0, 1, 1, 0, 0, 1, 1, 0,  0, 1, 0, 0, 0, 0, 1, 0,  0, 1, 0, 0, 0, 0, 1, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 1, 1, 1, 1, 0, 0,  0, 0, 1, 1, 1, 1, 0, 0,  0, 0, 1, 1, 1, 1, 0, 0,  0, 0, 1, 1, 0, 1, 0, 0,  1, 0, 0, 1, 0, 0, 0, 1,  1, 0, 0, 1, 0, 0, 0, 1,  0, 0, 0, 1, 0, 1, 0, 0, 
  0, 0, 1, 0, 0, 1, 0, 0,  0, 0, 1, 0, 0, 1, 0, 0,  0, 0, 1, 0, 0, 1, 0, 0,  0, 1, 0, 0, 1, 0, 0, 0,  1, 1, 1, 0, 1, 0, 1, 0,  0, 1, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  1, 0, 0, 0, 0, 1, 0, 0,  1, 0, 0, 0, 0, 1, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 
};

static byte clearScreen[] = { 
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

static byte party[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0,
  0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
  1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0,
  1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
};

static byte spaceInvaders[] = {
  0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0,  0, 0, 0, 0, 1, 1, 0, 0, 0, 
  0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,  0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,  0, 0, 0, 1, 1, 1, 1, 0, 0, 
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0,  0, 0, 1, 1, 1, 1, 1, 1, 0, 
  0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1,  0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0,  0, 1, 1, 0, 1, 1, 0, 1, 1, 
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  0, 1, 1, 1, 1, 1, 1, 1, 1, 
  0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0,  0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1,  0, 0, 0, 1, 0, 0, 1, 0, 0, 
  0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0,  0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1,  0, 0, 1, 0, 1, 1, 0, 1, 0, 
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,  0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0,  0, 1, 0, 1, 0, 0, 1, 0, 1, 
};

static byte spaceInvaders2[] = {
  0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0,  0, 0, 0, 0, 1, 1, 0, 0, 0, 
  0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,  0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1,  0, 0, 0, 1, 1, 1, 1, 0, 0, 
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1,  0, 0, 1, 1, 1, 1, 1, 1, 0, 
  0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1,  0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1,  0, 1, 1, 0, 1, 1, 0, 1, 1, 
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  0, 1, 1, 1, 1, 1, 1, 1, 1, 
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0,  0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,  0, 0, 0, 1, 0, 0, 1, 0, 0, 
  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,  0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,  0, 0, 1, 0, 1, 1, 0, 1, 0, 
  0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0,  0, 1, 0, 0, 0, 0, 0, 0, 1,
};

struct Image {
  int width, height;
  byte *pixels;
};

struct Animation {
  struct Image image;
  //make unused elements 0, increase as needed. Frame number starts at 1 so 0s can be counted as unused frames
  int frames[15];
};

struct Image party_image = {
  43, 8,
  party
};

struct Image pacMan_image = {
  64, 8,
  pacMan
};

struct Image clear_image = {
   8, 8,
   clearScreen
};

struct Image spaceInv_image = {
  34, 8,
  spaceInvaders
};

struct Image pong_image = {
 72, 8,
  pong 
};

struct Image spaceInv2_image = {
  34, 8,
  spaceInvaders2
};

struct Image creeperExplode_image = {
  56, 8, 
  creeperExplode
};

struct Animation pacMan_anim = {
  pacMan_image,
  {4, 3, 2, 1, 2, 3}
};

struct Animation creeperExplode_anim = {
  creeperExplode_image,
 {1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 4, 5, 6, 7}
};

byte col = 0;
byte leds[8][8];

//Button code
const int buttonPin = 19;
int formerButtonState = 1;

// pin[xx] on led matrix connected to nn on Arduino (-1 is dummy to make array start at pos 1)
int pins[17]= {-1, 5, 4, 3, 2, 14, 15, 16, 17, 13, 12, 11, 10, 9, 8, 7, 6};

// col[xx] of leds = pin yy on led matrix
int cols[8] = {pins[13], pins[3], pins[4], pins[10], pins[06], pins[11], pins[15], pins[16]};

// row[xx] of leds = pin yy on led matrix
//int rows[8] = {pins[9], pins[14], pins[8], pins[12], pins[1], pins[7], pins[2], pins[5]};
int rows[8] = {pins[5], pins[2], pins[7], pins[1], pins[12], pins[8], pins[14], pins[9]};

void setup() {
   Serial.begin(9600);           // set up Serial library at 9600 bps
  
  //set up button input
  pinMode(buttonPin, INPUT);
  
  // sets the pins as output
  for (int i = 1; i <= 16; i++) {
    pinMode(pins[i], OUTPUT);
  }

  // set up cols and rows
  for (int i = 1; i <= 8; i++) {
    digitalWrite(cols[i - 1], LOW);
  }

  for (int i = 1; i <= 8; i++) {
    digitalWrite(rows[i - 1], LOW);
  }

  clearLeds();

  // Turn off toggling of pin 11
  FrequencyTimer2::disable();
  // Set refresh rate (interrupt timeout period)
  FrequencyTimer2::setPeriod(2000);
  // Set interrupt routine to be called
  FrequencyTimer2::setOnOverflow(display);
}

int stateCounter = 1;
int maxState = 5;

void loop() {
  int buttonState = digitalRead(buttonPin);
  Serial.print(buttonState);
  Serial.println(formerButtonState);
  
  if (buttonState == 0 && formerButtonState == 1){
    Serial.println("button press!");
    formerButtonState = buttonState;
    stateCounter++;
    if (stateCounter > maxState){
      stateCounter = 1; 
    }
  }
  else if (buttonState == 1 && formerButtonState == 0){
    Serial.println("button depress");
    formerButtonState = buttonState;
  }
  
  Serial.println(stateCounter);
  
  switch (stateCounter) {
     case 1 :
       scrollImage(&party_image, 60);
       break;
     case 2 : 
       //scrollAndAlternateImage(&spaceInv_image,&spaceInv2_image,4,90);
       break;
     case 3 : 
       animateImage(&creeperExplode_anim, 300);
       break;
     case 4 : 
       //animateImage(&pong_image, 120);
       break; 
     case 5 : 
       animateImage(&pacMan_anim, 200);
       break;
     default:
       //scrollImage(&party_image, 60);
       break;
  }
  
  //1, 3, 5 work
  //animateImage anim works
  
  
  
 //scrollImage(&party_image, 60);
 // scrollAndAlternateImage(&spaceInv_image,&spaceInv2_image,4,90);
//animateImage(&creeperExplode_anim, 300);
//animateImage(&pong_image, 120);
//animateImage(&pacMan_anim, 200);

}

void clearLeds() {
  // Clear display array
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      leds[i][j] = 0;
    }
  }
}

//set an image
void setImage(struct Image *image){
 setImage(image, 1); 
}

//Set an image at a certain frame
void setImage(struct Image *image, int frame){
  byte *pixels = image -> pixels;
  int width = image -> width;
  for(int y=0; y<8; y++){
    for(int x=0; x<8; x++){
      leds[y][x] = pixels[(y*width) + x + ((frame-1) * 8)];
    } 
  }
}

//Animate an image by going through 8px at a time
void animateImage(struct Image *image, int del){
  int width = image -> width;
  //assumes width is divisible by 8, all frames must be full
  int numOfFrames = (width/8)-1;
  
  for(int frame = 1; frame <=numOfFrames; frame++){
    setImage(image, frame);
    delay(del);
  }
}

//animate an image by using the Animation's frames. This allows you to use one frame multiple times
void animateImage(struct Animation *anim, int del){
    int numOfFrames = 0;
    struct Image image = anim->image;
    //Set number of frames
    for (int i=0; i<15; i++){
      if (anim->frames[i]>0){
        numOfFrames++;
      }
    }
    
    int frameArr[numOfFrames];
    int frameArrIdx = 0;
    for(int i=0; i<15; i++){
      if (anim->frames[i]>0){
        frameArr[frameArrIdx] = anim->frames[i];
        frameArrIdx++;
      }
    }
    
    for(int frame=0; frame<numOfFrames; frame++){
      setImage(&image, frameArr[frame]);
      delay(del);
    }
}

//Scroll one image
void scrollImage(struct Image *image, int del){
  int width = image->width;
  byte *pixels = image->pixels;
  
  //iterate through each column of the image at an offset
  for(int i=0; i<width; i++){
    //update the display
    for(int y=0; y<8; y++){
      for(int x=0; x<8; x++){
        leds[y][x] = pixels[y*width + (x + i)%width];
      } 
    }
    delay(del);
  }
}

//Alternate between two images while scrolling
void scrollAndAlternateImage(struct Image *image1, struct Image *image2, int altDelay, int del){
   //assumes the two images are the same size
  int width = image1->width;
  
  //iterate through each column of the image at an offset
  for(int i=0; i<width; i++){
    byte *pixels ;
    if (i&altDelay) {
      pixels = image1->pixels;
    }
    else {
     pixels = image2->pixels;
    }
    
    //update the display
    for(int y=0; y<8; y++){
      for(int x=0; x<8; x++){      
        leds[y][x] = pixels[y*width + (x + i)%width];
      } 
    }
    delay(del);
  }
}

// Interrupt routine
void display() {
  digitalWrite(cols[col], LOW);  // Turn whole previous column off
  col++;
  if (col == 8) {
    col = 0;
  }
  for (int row = 0; row < 8; row++) {
    if (leds[col][7 - row] == 1) {
      digitalWrite(rows[row], LOW);  // Turn on this led
    }
    else {
      digitalWrite(rows[row], HIGH); // Turn off this led
    }
  }
  digitalWrite(cols[col], HIGH); // Turn whole column on at once (for equal lighting times)
}
