/*
 * Void Loop Robotech and Automation
 * Compatible with the Arduino IDE 1.0 and above
 * https://www.youtube.com/c/voidloopRobotechAutomation
 */

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20,4);  // set the I2C address 0x27 for a 20 chars and 4 line display

void setup()
{
  lcd.init();                      
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(0, 1);
  lcd.print("LCD 20x4 with Arduino");
  lcd.setCursor(1, 2);
  lcd.print("void loop robotech");
  lcd.setCursor(3, 3);
  lcd.print("and automation");
}

void loop()
{
}