#include "pitches.h"

// GFX

byte gfx0[8] = {
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

byte gfx1[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
};

byte gfx2[8] = {
  B00000,
  B11011,
  B11110,
  B11101,
  B11101,
  B11110,
  B11011,
  B00000,
};

byte gfx3[8] = {
  B00000,
  B00010,
  B00011,
  B01111,
  B11110,
  B11110,
  B01010,
  B00000,
};

byte gfx4[8] = {
  B00000,
  B01000,
  B11000,
  B11110,
  B01111,
  B01111,
  B01010,
  B00000,
};

byte gfx5[8] = {
  B00000,
  B00000,
  B01010,
  B00000,
  B01110,
  B10001,
  B00000,
  B00000,
};

byte gfx6[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

byte gfx7[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

// SFX
int sfx_melody_1[] = { NOTE_C4,NOTE_G3,NOTE_G3,NOTE_A3,NOTE_G3,0,NOTE_B3,NOTE_C4 };
int sfx_beats_1[] = { 4,8,8,4,4,4,4,4 };
int sfx_length_1 = 8;

// twinkle twinkle little star
int sfx_melody_2[] = {NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4};
int sfx_beats_2[] = {4,4,4,4,4,4,2,4,4,4,4,4,4,2};
int sfx_length_2 = 14;

int sfx_melody_3[] = { NOTE_C4,NOTE_B3,0,NOTE_G3,NOTE_A3,NOTE_G3,NOTE_G3,NOTE_C4 };
int sfx_beats_3[] = { 4,4,4,4,4,8,8,4 };
int sfx_length_3 = 8;
