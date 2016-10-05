/*
 **  GAMEBOX - A handheld games console in a box
 **  by Marquis de Geek - @marquisdegeek - 2014
 **
 **  Released under the GPL, version 2.
 **
 ** Version 1.0
 */
#include "pitches.h"

//
// Runner game specific data.
//
namespace {
  char const* g_RunnerPlayerAnimation[] = { "[", "|", "]" };
  int   g_RunnerMapData[] = {0,0,0,0,0,0,0,1,0,0,0,0, 1,0,0, 1,0,0,1,1,0,0,0,1,0,0,1,0,0,0,0, 1,0,0,1,0,0,1,0,0,1,1};
}
//
// GameRunnerPlayer
//
void GameRunnerPlayer::initialize() {
  y = 1;
  jump = 0;
  animIdx = 0;
  dead = 0;
  score = 0;
}

void GameRunnerPlayer::draw() const {
  lcd.setCursor(0,y);
  lcd.print(dead ? "X" : g_RunnerPlayerAnimation[animIdx]);
  lcd.setCursor(0,1-y);
  lcd.print(" ");

  drawScore();
}

void GameRunnerPlayer::drawScore() const {
  lcd.setCursor(7,0);
  lcd.print("Score ");

  lcd.setCursor(13,0);
  lcd.print(score);
}

void GameRunnerPlayer::update() {
  if (dead) {
    return;
  }

  // The animation isn't much, but we only do it once per tick
  if (++animIdx == sizeof(g_RunnerPlayerAnimation)/sizeof(g_RunnerPlayerAnimation[0])) {
    animIdx = 0;
  }

  // While in the air, count down to 0, and replace ply on ground
  if  (jump && --jump == 0) {
    y = 1;
  }
}

boolean GameRunnerPlayer::isJumping() const {
  return jump ? true : false;
}

boolean GameRunnerPlayer::isDead() const {
  return dead ? true : false;
}

void GameRunnerPlayer::jumpUp() {
  y = 0;
  jump = 3;

  int jumpSound[] = { NOTE_C3, 300,  0};
  sfx.playTune(jumpSound);
}

void GameRunnerPlayer::incScore() {
  ++score;
}

void GameRunnerPlayer::kill() {
  int tuneData[] = { NOTE_C4, 4, NOTE_G3, 8, NOTE_C3, 8, 0};

  debug("player.kill");
  if (!dead) {
    dead = 1;
    draw();
    sfx.playTune(tuneData);
  }
}

//
// GameRunnerMap
//
void GameRunnerMap::initialize() {
  // TODO: Randomize g_RunnerMapData, or vary according to level ?
}

void  GameRunnerMap::update() {
}

boolean GameRunnerMap::isCollision(const int pos) const {
  return g_RunnerMapData[pos&0xf] ? true : false;
}

void GameRunnerMap::draw(const int pos) const {
  lcd.setCursor(0,1);
  for(int i=0;i<16;++i) {
    lcd.print(g_RunnerMapData[(pos+i)&0xf] ? "o" : " ");
  }
}


//
// GameRunnerState::
//
void GameRunnerState::initialize() {
  gameSpeed = 200;
  pos = 0;
}

void  GameRunnerState::draw() const {
}

void GameRunnerState::update() {
  if ((pos % 2) == 0) {
    --gameSpeed;
  }
  ++pos;
}


//
// GameRunner
//

GameRunner::GameRunner() {
  gamesPlayed = 0;
  highScore = 0;
}

const char *  GameRunner::getName() {
  return "Arduino Runner";
}

void  GameRunner::initialize() {
  int tuneData[] = { NOTE_C4, 4, NOTE_G3, 8, NOTE_G3, 8, NOTE_A3, 4, NOTE_G3, 2, NOTE_B3, 4, NOTE_C4, 4, 0};

  debug("GameRunner.initialize");

  lcd.clear();
  lcd.print("Arduino Runner");

  sfx.playTune(tuneData);

  player.initialize();
  state.initialize();

  lcd.clear();

  ++gamesPlayed;
}

void  GameRunner::draw() const {
  if (!isGameOver()) {
    gamemap.draw(state.pos);
    player.draw();
    state.draw();
  }
}

void  GameRunner::update(int btn1Pressed, int btn2Pressed) {
  if (isGameOver()) {
    if (btn1Pressed) {
      initialize();
    }
    if (btn2Pressed) {
      gamebox.startMenu();
    }
    return;
  }

  gamemap.update();
  player.update();

  // The player is in the same column as a boulder
  if (gamemap.isCollision(state.pos)) {

    if (player.isJumping()) {
      player.incScore();
    } else {
      player.kill();
      return;
    }
  }

  for(int i=0;i<state.gameSpeed;++i) {
    // don't allow the jump when ply is already in the air
    if (!player.isJumping() && btn2Pressed) {
      player.jumpUp();
    }

    delay(1);
  }

  state.update();

  if (player.score > highScore) {
    highScore = player.score;
  }
}

boolean GameRunner::isGameOver() const {
  return player.isDead();
}

