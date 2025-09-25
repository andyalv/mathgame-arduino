#include "melodies.h"
#include "pitches.h"

const Note winningMelody[] = {
  {NOTE_C5, 4}, {NOTE_E5, 4}, {NOTE_G5, 4}, {0, 0}
};

const Note losingMelody[] = {
  {NOTE_C4, 4}, {NOTE_A3, 4},{NOTE_F3, 4}, {0, 0}
};

const Note outOfBoundsMelody[] = {
  {NOTE_E4, 4}, {NOTE_E4, 4}, {NOTE_B3, 4}, {NOTE_F3, 4}, {0, 0}
};

const Note backspaceMelody[] = {
  {NOTE_B4, 8}, {NOTE_E5, 8}, {0, 0}
};

const Note menuMelody[] = {
  {NOTE_E5, 16}, {NOTE_F5, 16}, {NOTE_G5, 16}, {0, 0}
};

void playMelody(const Note melody[]) {
  for (int i = 0; melody[i].note != 0 && melody[i].duration != 0; i++) {
    int duration = 1000 / melody[i].duration;
    tone(BUZZER_PIN, melody[i].note, duration);
    delay(duration * 1.3);
    noTone(BUZZER_PIN);
  }
}
