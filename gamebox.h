class ArduinoGame {
  public:
    virtual void initialize() {}
    virtual const char* getName() = 0;
    virtual void draw() const {}
    virtual void update() {}
    virtual boolean mustRefreshDisplay() = false;
};

class GameBox {
  public:
    void init();
    void startMenu();
    void startGame(ArduinoGame *game);
    void update();
    void setState(int btn1, int btn2);

    void startMenu();
    void startGame(ArduinoGame *game);

  protected:
    ArduinoGame *currentGame;
    int button1Pressed;
    int button2Pressed;
};

