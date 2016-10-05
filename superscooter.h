#define DIFFICULTY 4 // Easy
#define LCD_WIDTH 16
#define NUMBER_OF_ENEMIES 20

#define STATE_GAME       1
#define STATE_MENU       0

class SuperScooter: public ArduinoGame {
  public:
    SuperScooter();
    virtual void initialize();
    virtual const char* getName();
    virtual void draw();
    virtual void update(int btn1Pressed, int btn2Pressed);

  private:
    void initValues();
    void initEnemies();
    void showStartScreen();
    void printObjects();
    void checkCollision(int enemyIndex);
    void checkWin();
    void gameLost();
    void gameWon();
    void startGame();
    void printMenu(char const* line1);

  protected:
    boolean refreshLCD;
    int state;
    long previousMillis;
    String player_ship;
    int interval;
    int player_position_y;
    int player_position_x;
    int enemies_x[NUMBER_OF_ENEMIES] = { 16, 22, 27, 34, 38, 42, 47, 51, 54, 58, 65, 70, 74, 78, 83, 87, 91, 95, 99, 104 };
    int enemies_y[NUMBER_OF_ENEMIES] = { 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0 };
};
