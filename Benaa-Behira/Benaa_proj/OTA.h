/**
 ************************************************************************                  
 * @file                    : OTA.h
 * @author                  : Ahmed Hesham
 * @brief                   : OTA Module header file
 ************************************************************************
 */

#ifndef _OTA_H
#define _OTA_H

/********************************************************************** Includes Start ************************************************************************/
#include <Arduino.h>
//for more info about the library, visit the module website "https://otadrive.com/"
#include <otadrive_esp.h> // by "OTAdrive"
/********************************************************************** Includes End   ************************************************************************/

/********************************************************************** Macro Declarations Start **************************************************************/

/********************************************************************** Macro Declarations End   **************************************************************/

/********************************************************************** Macro Functions Declarations Start ****************************************************/

/********************************************************************** Macro Functions Declarations End   ****************************************************/

/********************************************************************** Data Type Declarations Start **********************************************************/

/********************************************************************** Data Type Declarations End   **********************************************************/

/********************************************************************** Software Interfaces Declarations Start ************************************************/
void OTA_Init (void);
void OTA_Runnable (void);
/********************************************************************** Software Interfaces Declarations End   ************************************************/



#endif