#include "game.h"

// UserInput from final-project.ino
extern char userInput[MAX_USERINPUT+1];

int x, visibleNum, visibleSum, gameResult, highestScore;
bool isMatchRunning;
byte userWins, rowIndex, minGame, maxGame;
char tempCharArray[LCD_COLS+1];

void startGame() {
  Serial.println("Currently running match...");
  resetGame(); // Reset Game variables
  newGameProblem();
}

// Reset Game variables
void resetGame() {
  minGame = 1;
  maxGame = 10;
  rowIndex = 2;
  userWins = x = visibleSum = gameResult = 0;
  isMatchRunning = false;
}

void winRound() {
  // Debug
  Serial.println(ROUND_WON.text);
  Serial.println();

  printLCD(ROUND_WON);
  playMelody(winningMelody);
  userWins++;

  /* Restart rowIndex for position
   * (X= )
   *    ^
  */
  rowIndex = 2; 
  newGameProblem();
}

void lostRound() {
  Serial.println(ROUND_LOST.text);
  userWins++; // Count started from 0

  if (userWins > highestScore)
    highestScore = userWins;

  // Turn int to ascii characters
  // int value, char* str, int base
  itoa(highestScore, tempCharArray, 10);

  // Copy string to the LCDPrintable[] in position 1
  strcpy(HIGHEST_WIN[1].text, tempCharArray);

  Serial.println("Match ended.");
  Serial.println();

  printLCD(ROUND_LOST);
  playMelody(losingMelody);

  printLCDAll(HIGHEST_WIN);
  delay(3000);
  startGame(); // Start a new game
}

void newGameProblem() {
  // Reset visibleNum
  visibleNum = 0;

  if (userWins > 3)
    maxGame = 20;

  if (userWins < 6) {
    visibleNum = random(minGame,maxGame);
    x = random(minGame,maxGame);
  }
  else {
    // Make sure it is never zero
    while (visibleNum == 0)
      visibleNum = random(minGame, maxGame) - random(minGame, maxGame);
    x = random(minGame, maxGame) - random(minGame, maxGame);
  }

  visibleSum = random(minGame, maxGame) - random(minGame, maxGame);

  // Game Operation (eg. 5X + (2) = 7)
  gameResult = ( visibleNum*x ) + visibleSum;

  // Format a char array with the text formatted as indicated
  if (visibleSum != 0)
    sprintf(tempCharArray, "%dX+(%d)=%d", visibleNum, visibleSum, gameResult);
  else
    sprintf(tempCharArray, "%dX = %d", visibleNum, gameResult);

  /* 
   * Create a temporal printable variable for displaying on LCD 
   * the strings.
   *
   * Since the formated string cannot be put directly on
   * the LCDPrintable variable, it is copied bit by bit with the `strcpy`
   * function.
  */
  LCDPrintable printable[LCD_ROWS] = {
    { "", {0,0} },
    { "X=", {0,1} }
  };
  strcpy(printable[0].text, tempCharArray);

  slowprintLCD(printable, 50);
  lcd.blink();
  isMatchRunning = true;

  // Debug print
  Serial.println("Problem no. " + String(userWins));
  Serial.println(String(printable[0].text) + " (x = " + String(x) + ")");
}

// Clear second row and print "X={userInput}"
void printSecondRowGame() {
  clearLCDLine(1);
  LCDPrintable printable;
  String temp = "X=" + String(userInput);
  temp.toCharArray(printable.text, LCD_COLS+1);
  printable.pos[0] = 0;
  printable.pos[1] = 1;
  printLCD(printable);
}
