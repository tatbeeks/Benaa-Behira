/**
 ************************************************************************                  
 * @file                    : LCD.c
 * @author                  : Ahmed Hesham
 * @brief                   : LCD Display source file
 ************************************************************************
 */

#include "LCD.h"

//variables to control LCD update values time
long LCD_currentMillis = 0;
long LCD_previousMillis = 0;

//create object
LiquidCrystal_I2C lcd(0x3F, LCD_COLS_NUMBER, LCD_ROWS_NUMBER);

void LCD_Init(void) {
  //start sequence
  lcd.init();
  lcd.backlight();
  //customize screen 
  lcd.setCursor(0, 0);
  lcd.print("N:");
  lcd.setCursor(10, 0);
  lcd.print("P:");
  lcd.setCursor(0, 1);
  lcd.print("K:");
  // lcd.setCursor(10, 1);
  // lcd.print("TURB:");
  lcd.setCursor(0, 2);
  lcd.print("TDS:");
  lcd.setCursor(0, 3);
  lcd.print("FL1:");
}

void LCD_Runnable(void) {
  LCD_currentMillis = millis();
  //update values every 10s
  if (LCD_currentMillis - LCD_previousMillis >= 10000) {
    LCD_previousMillis = millis();

    lcd.setCursor(2, 0);
    lcd.print(Nitrogen_val);
    lcd.print("Mg/L");
    lcd.setCursor(12, 0);
    lcd.print(phosphorous_val);
    lcd.print("Mg/L");
    lcd.setCursor(2, 1);
    lcd.print(potassium_val);
    lcd.print("Mg/L");
    // lcd.setCursor(15, 1);
    // lcd.print((int)Turbidity_NTU);
    //lcd.print("NTU");
    lcd.setCursor(4, 2);
    lcd.print(TDS_Value);
    lcd.print("PPM");
    lcd.setCursor(4, 3);
    lcd.print("            ");
    lcd.setCursor(4, 3);
    lcd.print(int(flowRate));
    lcd.print("L/M");
  }
}
