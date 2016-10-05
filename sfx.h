class SFX {
  public:
    void init(const int pin);
    void introSound();
    void playSound(const int pitch, const int duration) const;
    void playTune(const int *melody) const;
    void playMusic(int melody[], int beats[], int length) const;

  protected:
    int speakerPin;
};
