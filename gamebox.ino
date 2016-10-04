/*
 *  Arduino Gamebox - Games. In Arduino.
 *  by Matias Gea - @mfgea - 2016
 *
 *  GameBox v1.0
 */

#include "gamebox.h"
#include "menu.h"

void GameBox::init() {
  debug("Initialization");

  button1Pressed = 0;
  button2Pressed = 0;

  lcd.begin(16, 2);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Arduino Gamebox");
  lcd.setCursor(1,3);
  lcd.print("by Matias Gea");

  debug("Playing intro sound");
  sfx = new SFX(SPKR_PIN);
  sfx.introSound();

  delay(2000);
}

void GameBox::startMenu() {
  debug("Starting Menu");
  startGame(&menu);
}

void GameBox::startGame(ArduinoGame *game) {
  debug("Starting Game: ");
  debug(game->getName());
  currentGame = game;
  currentGame->initialize();
}

void GameBox::update() {
  if(button1Pressed || button2Pressed) {
    updating();
  }
  if(button1State) {
    debug("Button1 Pressed");
  }
  if(button2State) {
    debug("Button2 Pressed");
  }
  currentGame->update(button1State, button2State);

  button1State = 0;
  button2State = 0;
  currentGame->draw();
}

void GameBox::setState(int btn1, int btn2) {
  button1State = btn1;
  button2State = btn2;
}

