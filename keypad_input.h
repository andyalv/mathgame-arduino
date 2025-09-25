#ifndef KEYPAD_INPUT_H
#define KEYPAD_INPUT_H

#include "config.h"
#include <Arduino.h>

extern char userInput[MAX_USERINPUT+1];
extern byte userInputIndex;

void restartInput();
void addKeyInput(char key);
void deleteKeyInput();

#endif
