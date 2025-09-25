#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "config.h"

struct LCDPrintable {
  char text[LCD_COLS+1]; // Text to print
  byte pos[2]; // Start of the print
};

extern LiquidCrystal lcd;
extern bool isLCDRowEmpty[LCD_ROWS];

extern const LCDPrintable AUTHOR_PRINT[LCD_ROWS];
extern const LCDPrintable WELCOME_PRINT[LCD_ROWS];

extern const LCDPrintable ROUND_WON, ROUND_LOST;
extern LCDPrintable HIGHEST_WIN[LCD_ROWS];

void printLCDAll(LCDPrintable printable[LCD_ROWS]);
void printLCD(LCDPrintable printable);
void clearLCDLine(byte row);
void slowprintLCD(LCDPrintable printable[LCD_ROWS], byte milis);
bool isLCDRowsEmpty();

#endif
