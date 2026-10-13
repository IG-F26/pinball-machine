#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 7, 6, 5, 4, 3);  // RS, E, D4, D5, D6, D7

void setup() {
  lcd.begin(16, 2);
  lcd.print("Hello, world!");
}

void loop() {
  lcd.setCursor(0, 1);        // column 0, second row
  lcd.print(millis() / 1000); // seconds since start
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("                ");
  delay(500);
}