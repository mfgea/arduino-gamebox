#include "sfx.h"
#include "pitches.h"

SFX::SFX(const int pin) {
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
