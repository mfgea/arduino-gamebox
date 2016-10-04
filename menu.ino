/*
 *  Arduino Gamebox - Games. In Arduino.
 *  by Matias Gea - @mfgea - 2016
 *
 *  Games Menu v1.0
 */

#include "menu.h"

GamesMenu::GamesMenu() {
  gameCount = 0;
  refreshLCD = false;
}

void GamesMenu::initialize() {
  refreshLCD = true;
}

void GamesMenu::addGame(ArduinoGame *game) {
  if (gameCount < MAX_GAMES) {
    gameList[gameCount] = game;
    gameCount++;
  }
}

void GamesMenu::draw() const {
  if (refreshLCD) {
    lcd.clear();
    // Game name
    lcd.print(gameList[currentSelection]->getName());
    lcd.setCursor(0, 1);
    lcd.print("<-Play");

    lcd.setCursor(10, 1);
    lcd.print("Next->");
  }
}

void GamesMenu::update(boolean btn1Pressed, boolean btn2Pressed) {
  refreshLCD = false;

  if (btn1Pressed) {
    gamebox.startGame(gameList[currentSelection]);
  }
  if (btn2Pressed) {
    sfx.playSound(440, 50);
    sfx.playSound(880, 30);
    if (++currentSelection == gameCount) {
      currentSelection = 0;
    }
    refreshLCD = true;
  }
}

boolean GamesMenu::mustRefreshDisplay() {
  return refreshLCD;
}

