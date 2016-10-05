/*
 * Donkey Godge game for Arduino
 *
 * Adapted from https://github.com/AfBu/arduino-donkey-dodge-game
 */

#include "monkeydodge_fx.h"

void MonkeyDodge::initialize() {
  // initialize LCD with loading text
  initLcd();
  showStartScreen();
}

void MonkeyDodge::draw() {
  if(refreshLCD) {
    showRoad();
    showDonkey();
    showPlayer();
    showHud();
    updateScore();
  }
}

void MonkeyDodge::update(int btn1Pressed, int btn2Pressed) {
  if (isStartScreen() || isGameOver()) {
    if (btn1Pressed) {
      gamebox.startMenu();
    } else if (btn2Pressed) {
      startLevel(1);
    }
  }

  if (millis() - timer > 60) {
    timer = millis();

    handleControls(btn1Pressed, btn2Pressed);

    if (donkeyHit) lives--;
    if (lives <= 0) {
      gameOver();
    } else if (donkeyHit) {
      startLevel(level);
    }

    if (score > 1000) {
      score -= 1000;
      startLevel(level + 1);
    }

    if (donkeyBeep > 0) {
      sfx.playSound(1000, 10);
      donkeyBeep--;
    }
  }
  if (donkeyBeep == 0) sfx.playSound(spd * 500, 2);
}

// GAME
void MonkeyDodge::showStartScreen() {
  refreshLCD = false;
  screen = START_SCREEN;

  lcd.clear();
  lcd.write(byte(3));
  lcd.print(" DONKEY DODGE ");
  lcd.write(byte(4));
  lcd.setCursor(0, 1);
  lcd.print("<-MENU    PLAY->");

  sfx.playMusic(sfx_melody_2, sfx_beats_2, sfx_length_2);
}

void MonkeyDodge::gameOver() {
  screen = GAMEOVER_SCREEN;
  refreshLCD = false;
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   GAME  OVER");
  lcd.setCursor(0,1);
  lcd.print("   SCORE ");
  lcd.print(int(score + level * 1000), DEC);
  
  sfx.playMusic(sfx_melody_3, sfx_beats_3, sfx_length_3);
}

boolean MonkeyDodge::isGameOver() const {
  return screen == GAMEOVER_SCREEN;
}

boolean MonkeyDodge::isStartScreen() const {
  return screen == START_SCREEN;
}

// Helper functions

void MonkeyDodge::showDonkey() {
  donkeyHit = (int(dx) == int(px) && int(dy) == int(py));
  if (dx < 13) {
    lcd.setCursor(dx, dy);
    lcd.write(byte(3));
  }

  dx -= spd;
  if (dx < 0) {
    dx = 16 + random(0,20);
    dy = random(0,2);
    score += 10 + spd * 10;
    donkeyBeep = 5;
  }
}

void MonkeyDodge::startGame() {
  screen = GAME_SCREEN;

  timer = 0;
  rpt = 0;
  rpb = 2;
  lives = 3;
  score = 0;
  startLevel(1);
}

void MonkeyDodge::startLevel(int lvl) {
  donkeyBeep = 0;
  donkeyHit = false;
  level = lvl;
  px = 2;
  py = 0;
  dx = 0;
  dy = 0;
  spdMin = (45 + float(level) * 5) / 100;
  spd = spdMin;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("    LEVEL ");
  lcd.print(level);
  lcd.setCursor(0,1);
  lcd.print("    LIVES ");
  lcd.print(lives);

  sfx.playMusic(sfx_melody_1, sfx_beats_1, sfx_length_1);

  delay(2000);
}

void MonkeyDodge::updateScore() {
  score += spd / 10;
}

void MonkeyDodge::showHud() const {
  int s;
  // speed
  s = spd * 100;
  if (s < 10) {
    lcd.setCursor(15,0);
  } else if (s < 100) {
    lcd.setCursor(14,0);
  } else {
    lcd.setCursor(13,0);
  }
  lcd.print(s, DEC);
  // score
  s = score;
  if (s < 10) {
    lcd.setCursor(15,1);
  } else if (s < 100) {
    lcd.setCursor(14,1);
  } else if (s < 1000) {
    lcd.setCursor(13,1);
  } else {
    lcd.setCursor(12,1);
  }
  lcd.print(s, DEC);
}

void MonkeyDodge::handleControls(int btn1Pressed, int btn2Pressed) {  
  if (btn1Pressed && py == 1) py = 0;
  if (btn2Pressed && py == 0) py = 1;
}

void MonkeyDodge::showRoad() {
  int x;
  lcd.clear();
  lcd.setCursor(0,0);
  for (int i = 0; i < 4; i++) {
    x = i * 4 + rpt;
    if (x < 13) {
      lcd.setCursor(x, 0);
      lcd.write(byte(0));
    }
    x = i * 4 + rpb;
    if (x < 13) {
      lcd.setCursor(x, 1);
      lcd.write(byte(1));
    }
  }
  rpt -= spd;
  rpb -= spd;
  if (rpt < 0) rpt += 4;
  if (rpb < 0) rpb += 4;
}

void MonkeyDodge::showPlayer() const {
  lcd.setCursor(px,py);
  lcd.write(byte(2));
}

/* INITIALIZATION FUNCTIONS */

void MonkeyDodge::initLcd() const {
  lcd.clear();
  lcd.print("   Loading...");
  lcd.createChar(0, gfx0);
  lcd.createChar(1, gfx1);
  lcd.createChar(2, gfx2);
  lcd.createChar(3, gfx3);
  lcd.createChar(4, gfx4);
  lcd.createChar(5, gfx5);
  lcd.createChar(6, gfx6);
  lcd.createChar(7, gfx7);
}

