#ifndef MELODIES_H
#define MELODIES_H

#include <Arduino.h>
#include "config.h"

struct Note {
  int note;
  int duration;
};

extern const Note winningMelody[];
extern const Note losingMelody[];
extern const Note outOfBoundsMelody[];
extern const Note backspaceMelody[];
extern const Note menuMelody[];

void playMelody(const Note melody[]);

#endif
