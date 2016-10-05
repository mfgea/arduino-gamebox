class SFX {
  public:
    void init(const int pin);
    void introSound();
    void playSound(const int pitch, const int duration) const;
    void playTune(const int *melody) const;

  protected:
    int speakerPin;
};
