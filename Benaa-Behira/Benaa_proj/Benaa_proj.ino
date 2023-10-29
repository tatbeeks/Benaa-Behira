/**
 ************************************************************************                  
 * @file                    : Benaa_proj.ino
 * @author                  : Tatbeek Company
 * @brief                   : Benaa Project source file
 ************************************************************************
 */
#include "main.h"
//variable used to control publish interval
unsigned long Last_Publish_Time = 0;

void setup() {
  Serial.begin(9600);
  delay(50);
  LCD_Init();
  WIFI_Init();
  Client_Init();
  OTA_Init();
  NPK_Init();
  // Turbidity_Init();
  TDS_Init();
  WaterFlow_Init();
  Power_Init();
  delay(50);
}
//WaterFlow_Runnable() called after every call of other function 
//to reduce the variation of function call from 1 sec,
//As this function should be called typically every 1s
void loop() {

  WaterFlow_Runnable();
  NPK_Nitrogen_Runnable();
  WaterFlow_Runnable();
  NPK_Phosphorous_Runnable();
  WaterFlow_Runnable();
  NPK_Potassium_Runnable();
  WaterFlow_Runnable();
  //Turbidity_Runnable();
  WaterFlow_Runnable();
  TDS_Runnable();
  WaterFlow_Runnable();
  LCD_Runnable();
  WaterFlow_Runnable();
  Power_Runnable();
  OTA_Runnable();


  if ((millis() - Last_Publish_Time) >= PUBLISH_TIME_INTERVAL_MS) {
    if (WIFI_Check()) {
      Client_Connect();
      if (Client_Connectivity_Flag == 1) {
        Client_Publish();
        //put every value that should be reset after publish is done
        flowMilliLitres = 0;
        Last_Publish_Time = millis();
      }
    }
  }
}