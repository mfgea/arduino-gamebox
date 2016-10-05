/*
 *  Arduino Gamebox - Games. In Arduino.
 *  by Matias Gea - @mfgea - 2016
 *
 *  Main Proyect File v1.0
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "sfx.h"
#include "gamebox.h"
#include "menu.h"
#include "runner.h"
#include "monkeydodge.h"

// Settings
#define DEBUG 0

// Pins
const int BUTTON1_PIN = 2;
const int BUTTON2_PIN = 3;
const int SPEAKER_PIN = 8;

GameBox gamebox;
GamesMenu menu;
SFX sfx;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void debug(const char *str) {
#if DEBUG
  Serial.println(str);
#endif
}

void setup() {
#if DEBUG
  Serial.begin(9600);
#endif

  sfx.init(SPEAKER_PIN);

  // Set interrupts for button pins
  pciSetup(BUTTON1_PIN);
  pciSetup(BUTTON2_PIN);

  // Initialize Gamebox
  gamebox.init();

  // menu.addGame(new AwesomeGame());

  // Start menu app
  gamebox.startMenu();
}

void loop() {
  gamebox.update();
}

void pciSetup(byte pin) {
  pinMode(pin, INPUT_PULLUP);

  *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
  PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
  PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

ISR(PCINT2_vect){
  gamebox.setState(digitalRead(BUTTON1_PIN), digitalRead(BUTTON2_PIN));
}
