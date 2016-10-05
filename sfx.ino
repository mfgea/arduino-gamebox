#include "pitches.h"

void SFX::init(const int pin) {
  speakerPin = pin;
}
void SFX::introSound() {
  for(int i=NOTE_C4; i<NOTE_C6; ++i) {
    playSound(i, 150);
  }
}

void SFX::playSound(const int pitch, const int duration) const {
  tone(speakerPin, pitch, duration);
}

void SFX::playTune(const int *melody) const {
  while(*melody) {
    int notePitch = melody[0];
    int noteDuration = 1000 / melody[1];
    playSound(notePitch, noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    // stop the tone playing:
    noTone(speakerPin);

    melody += 2;
  }
}

void SFX::playMusic(int melody[], int beats[], int length) const {
  for (int i = 0; i < length; i++) {
    int duration = 1000/beats[i];
    playSound(melody[i], duration);
    int pause = duration * 1.30;
    delay(pause);
    noTone(speakerPin);
  }
}
