/**
 ************************************************************************                  
 * @file                    : Power.c
 * @author                  : Ahmed Hesham
 * @brief                   : Power Module source file

 this module works on determine thether the device works on adapter power source or battery as a power source
 ************************************************************************
 */

#include "Power.h"

byte Power_State;

void Power_Init(void) {
  pinMode(POWERPIN, INPUT);
}

void Power_Runnable(void) {
  Power_State = digitalRead(POWERPIN);
  Serial.print("POWERSTATE :");
  Serial.println(Power_State);
}