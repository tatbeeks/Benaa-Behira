/**
 ************************************************************************                  
 * @file                    : NPK.h
 * @author                  : Ahmed Hesham
 * @brief                   : NPK Sensor header File.
 ************************************************************************
 */

#ifndef _NPK_H
#define _NPK_H


/********************************************************************** Includes Start ************************************************************************/
//lib used to communicate through software serial adjusted to work with esp32
//search in LIBRARY MANAGER EspSoftwareSerial "by Dirk Kaar, Peter Lerup"
#include <SoftwareSerial.h>  //https://github.com/plerup/espsoftwareserial/
#include <Arduino.h>
/********************************************************************** Includes End   ************************************************************************/

/********************************************************************** Macro Declarations Start **************************************************************/

/********************************************************************** Macro Declarations End   **************************************************************/

/********************************************************************** Macro Functions Declarations Start ****************************************************/

/********************************************************************** Macro Functions Declarations End   ****************************************************/

/********************************************************************** Data Type Declarations Start **********************************************************/
extern byte Nitrogen_val,phosphorous_val,potassium_val;
/********************************************************************** Data Type Declarations End   **********************************************************/

/********************************************************************** Software Interfaces Declarations Start ************************************************/
void NPK_Init (void);
void NPK_Runnable (void);
void NPK_Nitrogen_Runnable(void);
void NPK_Phosphorous_Runnable(void);
void NPK_Potassium_Runnable(void);
/********************************************************************** Software Interfaces Declarations End   ************************************************/


#endif