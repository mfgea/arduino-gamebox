#define MAX_GAMES 8

class GamesMenu: public ArduinoGame {
  public:
    GamesMenu();
    virtual void initialize();
    virtual const char* getName() { return ""; }
    virtual void draw() const;
    virtual void update(int, int);
    virtual boolean mustRefreshDisplay();

    void addGame(ArduinoGame *pGame);

  protected:
    boolean refreshLCD;
    ArduinoGame* gameList[MAX_GAMES];
    int gameCount;
    int currentSelection;
};
