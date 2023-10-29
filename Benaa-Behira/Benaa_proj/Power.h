/**
 ************************************************************************                  
 * @file                    : Power.h
 * @author                  : Ahmed Hesham
 * @brief                   : Power Module header file
 ************************************************************************
 */

#ifndef _POWER_H
#define _POWER_H

/********************************************************************** Includes Start ************************************************************************/
#include <Arduino.h>
/********************************************************************** Includes End   ************************************************************************/

/********************************************************************** Macro Declarations Start **************************************************************/
#define POWERPIN   23
/********************************************************************** Macro Declarations End   **************************************************************/

/********************************************************************** Macro Functions Declarations Start ****************************************************/

/********************************************************************** Macro Functions Declarations End   ****************************************************/

/********************************************************************** Data Type Declarations Start **********************************************************/
extern byte Power_State;
/********************************************************************** Data Type Declarations End   **********************************************************/

/********************************************************************** Software Interfaces Declarations Start ************************************************/
void Power_Init(void);
void Power_Runnable(void);
/********************************************************************** Software Interfaces Declarations End   ************************************************/



#endif