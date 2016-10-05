class GameRunnerPlayer {
  public:
    void initialize();
    void draw() const;
    void drawScore() const;
    void update();
    boolean isJumping() const;
    boolean isDead() const;
    void jumpUp();
    void incScore();
    void kill();

  public:
    int score;
  private:
    int y;
    int jump;
    int animIdx;
    int dead;

};

class GameRunnerMap {
  public:
    void initialize();
    void update();
    boolean isCollision(const int pos) const;
    void draw(const int pos) const;
};

class GameRunnerState {
  public:
    void initialize();
    void draw() const;
    void update();

  public:
    int gameSpeed;
    int pos;
};

class GameRunner : public ArduinoGame {
  public:
    GameRunner();
    virtual const char* getName();
    virtual void initialize();
    virtual void draw() const;
    virtual void update(int btn1Pressed, int btn2Pressed);

    boolean isGameOver() const;

  protected:
    GameRunnerPlayer player;
    GameRunnerState state;
    GameRunnerMap gamemap;

    int gamesPlayed;
    int highScore;
};

