#define START_SCREEN 0;
#define GAMEOVER_SCREEN 1;
#define GAME_SCREEN 2;

class MonkeyDodge: public ArduinoGame {
  public:
    MonkeyDodge();
    virtual void initialize();
    virtual const char* getName();
    virtual void draw();
    virtual void update(int btn1Pressed, int btn2Pressed);

  private:
    void initLcd() const;
    void showStartScreen();
    void showRoad();
    void showPlayer() const;
    void showDonkey();
    void showHud() const;
    void updateScore();
    void startGame();
    void startLevel(int lvl);
    void handleControls(int btn1Pressed, int btn2Pressed);
    void gameOver();

    boolean isGameOver() const;
    boolean isStartScreen() const;

  protected:
    boolean refreshLCD;
    int screen;
    long timer;
    float rpt;
    float rpb;
    byte px;
    byte py;
    float dx;
    byte dy;
    float spd;
    float spdMin;
    float score;
    int level;
    int lives;
    boolean donkeyHit;
    int donkeyBeep;
};
