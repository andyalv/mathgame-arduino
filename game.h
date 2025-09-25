#ifndef GAME_H
#define GAME_H

#include "config.h"
#include <Arduino.h>
#include "lcd_display.h"
#include "melodies.h"

// Game variables
extern int x, visibleNum, visibleSum, gameResult, highestScore;
extern bool isMatchRunning;
extern byte userWins, rowIndex, minGame, maxGame;
extern char tempCharArray[LCD_COLS+1];
extern char userInput[MAX_USERINPUT+1];

void startGame();
void resetGame();
void winRound();
void winRound();
void lostRound();
void newGameProblem();
void printSecondRowGame();

#endif
