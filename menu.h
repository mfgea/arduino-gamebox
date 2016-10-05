#define MAX_GAMES 8

class GamesMenu: public ArduinoGame {
  public:
    GamesMenu();
    virtual void initialize();
    virtual const char* getName() { return ""; }
    virtual void draw() const;
    virtual void update(int btn1Pressed, int btn2Pressed);
    virtual boolean mustRefreshDisplay();

    void addGame(ArduinoGame *pGame);

  protected:
    boolean refreshLCD;
    ArduinoGame* gameList[MAX_GAMES];
    int gameCount;
    int currentSelection;
};
