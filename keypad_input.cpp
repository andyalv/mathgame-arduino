#include "keypad_input.h"

extern char userInput[MAX_USERINPUT+1];
extern byte userInputIndex;

// User input functions
// They directly affect the userInput char[] and index
void restartInput() {
  userInput[0] = '\0';
  userInputIndex = 0;
}

// Add a char to userInput based on the key pressed
// It is capped to MAX_USERINPUT
void addKeyInput(char key) {
  if (userInputIndex < MAX_USERINPUT){
    userInput[userInputIndex++] = key;
    userInput[userInputIndex] = '\0';
  }
}

// Delete the last char in userInput
void deleteKeyInput(){
  if (userInputIndex != 0)
    userInputIndex--;
  userInput[userInputIndex] = '\0';
}
