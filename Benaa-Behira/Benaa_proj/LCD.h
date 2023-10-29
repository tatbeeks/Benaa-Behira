/**
 ************************************************************************                  
 * @file                    : LCD.h
 * @author                  : Ahmed Hesham
 * @brief                   : LCD Display header file
 ************************************************************************
 */

#ifndef _LCD_H
#define _LCD_H

/********************************************************************** Includes Start ************************************************************************/
#include <Arduino.h>
//lib used to interface with lcd through I2C .. search under the name of LiquidCrystal_I2C.h "by Frank de Brabander"
//product similar link "https://store.fut-electronics.com/products/lcd-2x16-with-i2c"
#include <LiquidCrystal_I2C.h>  //https://github.com/johnrickman/LiquidCrystal_I2C
#include "NPK.h"
#include "Turbidity.h"
#include "TDS.h"
#include "Water_Flow.h"
/********************************************************************** Includes End   ************************************************************************/

/********************************************************************** Macro Declarations Start **************************************************************/
extern LiquidCrystal_I2C lcd;
#define LCD_COLS_NUMBER  20
#define LCD_ROWS_NUMBER  4
/********************************************************************** Macro Declarations End   **************************************************************/

/********************************************************************** Macro Functions Declarations Start ****************************************************/

/********************************************************************** Macro Functions Declarations End   ****************************************************/

/********************************************************************** Data Type Declarations Start **********************************************************/

/********************************************************************** Data Type Declarations End   **********************************************************/

/********************************************************************** Software Interfaces Declarations Start ************************************************/
void LCD_Init (void);
void LCD_Runnable (void);

/********************************************************************** Software Interfaces Declarations End   ************************************************/




#endif