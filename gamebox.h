class ArduinoGame {
  public:
    virtual void initialize() {}
    virtual const char* getName() = 0;
    virtual void draw() const {}
    virtual void update(int, int) {}
    virtual boolean mustRefreshDisplay() = 0;
};

class GameBox {
  public:
    void init();
    void startMenu();
    void startGame(ArduinoGame *game);
    void update();
    void setState(int btn1, int btn2);

  protected:
    ArduinoGame *currentGame;
    int button1State;
    int button2State;
};

