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

// Settings
#define DEBUG 0

// Pins
#define BTN_LEFT_PIN 2;
#define BTN_RIGHT_PIN 3;
#define SPKR_PIN 8;

GameBox gamebox();
GamesMenu menu();
SFX sfx(SPKR_PIN);

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void debug(const char *str) {
#if DEBUG
  Serial.println(str);
#endif
}

void setup() {
#if DEBUG
  Serial.begin(9600);
#endif

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
