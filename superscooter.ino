void SuperScooter::initialize() {
  initValues();
  initEnemies();
  showStartScreen();
}

void SuperScooter::draw() {
  if(refreshLCD) {
    unsigned long currentMillis = millis();
  
    // only do this after the defined interval has passed since the last time
    if(currentMillis - previousMillis > interval) {
      // remember when we do this block
      previousMillis = currentMillis;
        
      if(state == STATE_GAME) {
        printObjects();
        checkWin(); 
      } 
    }
  }
}

void SuperScooter::update(int btn1Pressed, int btn2Pressed) {
  if(state == STATE_MENU) {
    if (btn1Pressed) {
      gamebox.startMenu();
    }
    if (btn2Pressed) {
      startGame();
    }
  }

  if(state == STATE_GAME) {
    if(btn1Pressed) {
      player_position_y = 1;
    }
    if(btn2Pressed) {
      player_position_y = 0;
    }
  }
} 

void SuperScooter::initValues() {
  interval = DIFFICULTY * 100;
  state = STATE_MENU;
  previousMillis = 0;
  
  // define the player and starting position
  player_ship = "[=>";
  player_position_y = 0;
  player_position_x = 1;
  
  // This defines the enemies if you want to build your level by hand.
  // Below, these values will be overwritten by random values. But I 
  // wanted to leave this in so you can see how to define a level. 
  // Simply comment out the code below that fills in random the values.
}

void SuperScooter::initEnemies() {
  // seed the random number generator so we get different values every new run
  // analog pin 1 should be a "fairly" random value because it is "floating"
  randomSeed(analogRead(1));

  // randomly generate the placement of the enemies so each game is different.
  // first, make sure we start with at least the width of the lcd so no enemies
  // are on the screen when we first launch. Also need to be sure we have at 
  // least the ship length between the enemies to be sure the game is solvable!
  // COMMENT OUT THE BLOCK BELOW TO USE DEININED VALUES ABOVE
  int accumulation = LCD_WIDTH;
  for(int i=0; i < NUMBER_OF_ENEMIES; i++) {
    // randomly pick a number between the ship's length and 8
    accumulation += random((player_ship.length()+1), 8);
    enemies_x[i] = accumulation;
    enemies_y[i] = random(0,2);
  }
}

void SuperScooter::showStartScreen() {
  printMenu("Super Scooter!!!");
}

void SuperScooter::printObjects() {
  // clear the screen and draw the player
  lcd.clear();
  lcd.setCursor(player_position_x, player_position_y);
  lcd.print(player_ship); 
  
  // for each enemy
  for(int i=0; i<NUMBER_OF_ENEMIES; i++) {
    // move them to the left 1 space
    enemies_x[i] = enemies_x[i] - 1;
  
    // and draw them where they should appear
    if(enemies_x[i] >= 0 && enemies_x[i] <= LCD_WIDTH) { 
      lcd.setCursor(enemies_x[i], enemies_y[i]);
      lcd.print("*");
    }

    checkCollision(i);  
  }
}

void SuperScooter::checkCollision(int i) {
  // check to see if any enemy touches the player, if so, GAME OVER!!!
  if(
    (enemies_x[i] <= player_position_x+player_ship.length()) &&
    (enemies_x[i] >= player_position_x) &&
    (enemies_y[i] == player_position_y)
  ) {
    gameLost();
  }
}

void SuperScooter::checkWin() {
  // check to see if all enemies have been passed, if so, GAME WON!!!
  if(enemies_x[(NUMBER_OF_ENEMIES-1)] < 0) {
    gameWon();
  }
}

void SuperScooter::gameLost() {
  printMenu("  GAME OVER!!!  ");
}

void SuperScooter::gameWon() {
  printMenu("  GAME OVER!!!  ");
}

void SuperScooter::startGame() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Starting game...");
  delay(1000);
  state = STATE_GAME;
  refreshLCD = true;
}

void SuperScooter::printMenu(char const* line1) {
  state = STATE_MENU;
  refreshLCD = false;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print("<-Back    Play->");
}
