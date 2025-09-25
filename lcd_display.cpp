#include "lcd_display.h"

extern LiquidCrystal lcd;
bool isLCDRowEmpty[LCD_ROWS] = { true, true };

// Author
const LCDPrintable AUTHOR_PRINT[LCD_ROWS] = {
  { "Mathgame by", {0,0} },
  { "Andres Alv.", {3,1} }
};

// Title screen
const LCDPrintable WELCOME_PRINT[LCD_ROWS] = {
  { "MATHGAME! Press", {0,0} },
  { "star(*) to begin", {0,1} }
};

// Game scenarios
const LCDPrintable ROUND_WON = { "Correct answer!", {0,1} };
const LCDPrintable ROUND_LOST = { "Wrong answer!", {0,1} };

LCDPrintable HIGHEST_WIN[LCD_ROWS] = {
  { "Highest round:", {0,0} },
  { "", {0,1} }
};

// FUNCTIONS
// The parameters of the functions are to limit the size for the LCD variables
void printLCDAll(LCDPrintable printable[LCD_ROWS]) {
  if (!isLCDRowsEmpty())
    lcd.clear();

  for (int i=0; i<LCD_ROWS; i++) {
    printLCD(printable[i]);
  }
}

// Prints in a row (based on printable.position) the variable printable
void printLCD(LCDPrintable printable) {
  if (!isLCDRowEmpty)
    clearLCDLine(printable.pos[0]);

  lcd.setCursor(printable.pos[0], printable.pos[1]);
  lcd.print(printable.text);
  isLCDRowEmpty[printable.pos[0]]= {false};
}

void clearLCDLine(byte row) {
  lcd.setCursor(0, row);
  lcd.print(EMPTY_LCD_LINE);
}

// Slow animation for printing every character
void slowprintLCD(LCDPrintable printable[LCD_ROWS], byte milis) {
  lcd.clear();
  for (int i =0; i<LCD_ROWS; i++) { // Going through every row of the array
    lcd.setCursor(printable[i].pos[0], printable[i].pos[1]); // Start from position stated

    // Going through every column
    for (int j=0; printable[i].text[j] != '\0'; j++) {
      lcd.print(printable[i].text[j]);
      delay(milis);
    }
    isLCDRowEmpty[i]= {false};
  }
}

// Check if LCDRows are empty
bool isLCDRowsEmpty() {
  return isLCDRowEmpty[0] == true && isLCDRowEmpty[1] == true;
}
