#include <Keypad.h>

#include "melodies.h"
#include "lcd_display.h"
#include "keypad_input.h"
#include "game.h"

// Global states
enum GameState {
  GAME_IDLE,
  GAME_RUNNING,
};

GameState currentState = GAME_IDLE;

// Keys
const char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Ardiuno Pins
const byte rowPins[KEYPAD_ROWS] = {9, 8, 7, 6};
const byte colPins[KEYPAD_COLS] = {5, 4, 3, 2};


// Creation of keypad
// This translates to: Make a keymap with keys array, considering the rowPins and columnPins with the dimensions of ROWS and COLS.
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);


// LCD with configuration: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(A0,A1,13,12,11,10);

// User Input
// This is for saving memory
char userInput[MAX_USERINPUT+1];
byte userInputIndex = 0;

void setup() {
  Serial.begin(9600); // Serial comunication to computer
  pinMode(BUZZER_PIN, OUTPUT); // Needed for using the passive buzzer
  userInput[0] = '\0'; // Start empty char[] with no text
  lcd.begin(LCD_COLS,LCD_ROWS); // Startup display
  printLCDAll(WELCOME_PRINT);
  pinMode(A3, INPUT_PULLUP); // Set for generating a random read
  randomSeed(analogRead(A3)+millis());
}

void loop() {
  char key = keypad.getKey();
  if (!key) return;

  switch(currentState){
    case GAME_IDLE:
      handleIdle(key);
      break;

    case GAME_RUNNING:
      handleRunning(key);
      break;
  }
}

void handleIdle(char key) {
  switch (key) {
    // See author
    case 'A':
      slowprintLCD(AUTHOR_PRINT, 100);
      lcd.blink();
      break;

    // Start Game
    case '*':
      startGame();
      currentState = GAME_RUNNING;
      break;

    // Welcome Screen
    case 'B':
      playMelody(menuMelody);
      printLCDAll(WELCOME_PRINT);
      break;
  }
}

void handleRunning(char key) {
  if (key == 'D')
    return;
  else if (key == '*') {
    currentState = GAME_IDLE;
    playMelody(menuMelody);
    printLCDAll(WELCOME_PRINT);
    return;
  }
  else if (key == '#') {
    // Convert char array to integer
    int userAnswer = atoi(userInput);
    
    // Compare with the result
    if (userAnswer == x) {
      winRound();
    } else {
      lostRound();
    }

    restartInput();
    return;
  }
  else if (key == 'B') {
    deleteKeyInput();
    printSecondRowGame();
    playMelody(backspaceMelody);
    if(rowIndex>=3)
      rowIndex--;
    return;
  }
  else if (key == 'C'){
    restartInput();
    printSecondRowGame();
    playMelody(backspaceMelody);
    rowIndex = 2;
    return;
  }
  else { // 1-9
    if (userInputIndex >= MAX_USERINPUT) {
      Serial.println("Answer must not exceed 4 characters!");
      Serial.println("End string with #");
      playMelody(outOfBoundsMelody);
      return;
    }

    if (!isMatchRunning) // Ignore if there is no match
      return;

    if (key == 'A')
      key = '-';
    addKeyInput(key);
    lcd.setCursor(rowIndex++, 1);
    lcd.print(key);
    return;
  }
}
