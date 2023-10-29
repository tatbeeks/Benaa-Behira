/**
 ************************************************************************                  
 * @file                    : NPK.c
 * @author                  : Ahmed Hesham
 * @brief                   : NPK Sensor source file
 
 sensor works based on RS485 communication protocol. through RS485 to TTL gateway, SoftwareSerial or HardwareSerial libraries (based on needs)
 can be used 
 ************************************************************************
 */
#include "NPK.h"
//create object 'mod' with Rx&Tx pins
SoftwareSerial mod(18, 19);

byte Nitrogen_val, phosphorous_val, potassium_val;

// Modbus RTU request frames for reading NPK NPK_values

//frames for NPK german made
// const byte nitro[] = { 0x01, 0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c };
// const byte phos[] =  { 0x01, 0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc };
// const byte pota[] =  { 0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0 };

//frames for local manfacturer NPK (future electronics)
const byte nitro[] = { 0x01, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x0A };
const byte phos[] = { 0x01, 0x03, 0x00, 0x01, 0x00, 0x01, 0xD5, 0xCA };
const byte pota[] = { 0x01, 0x03, 0x00, 0x02, 0x00, 0x01, 0x25, 0xCA };

//array to store the recieved frame
byte values[11];

byte nitrogen() {
  //send Nitrogen frame
  if (mod.write(nitro, sizeof(nitro)) == 8) {
    //wait for response
    delay(100);
    //recieve frame from sensor
    for (byte i = 0; i < 7; i++) {
      values[i] = mod.read();
      Serial.print(values[i], HEX);
    }
    Serial.println();
  }
  //return the value of Nitrogen placed in Byte index 4
  return values[4];
}

byte phosphorous() {

  if (mod.write(phos, sizeof(phos)) == 8) {

    delay(100);
    for (byte i = 0; i < 7; i++) {
      values[i] = mod.read();
      Serial.print(values[i], HEX);
    }
    Serial.println();
  }
  return values[4];
}

byte potassium() {

  if (mod.write(pota, sizeof(pota)) == 8) {

    delay(100);
    for (byte i = 0; i < 7; i++) {
      values[i] = mod.read();
      Serial.print(values[i], HEX);
    }
    Serial.println();
  }
  return values[4];
}


void NPK_Init() {
  mod.begin(9600);
}

void NPK_Runnable() {
  // Read values
  Nitrogen_val = nitrogen();
  //delay for correct communication with sensor
  delay(50);
  phosphorous_val = phosphorous();
  delay(50);
  potassium_val = potassium();


  Serial.print("N ");
  Serial.print(": ");
  Serial.println(Nitrogen_val);
  Serial.print("P ");
  Serial.print(": ");
  Serial.println(phosphorous_val);
  Serial.print("K ");
  Serial.print(": ");
  Serial.println(potassium_val);
}

void NPK_Nitrogen_Runnable(void) {
  Nitrogen_val = nitrogen();

  Serial.print("N ");
  Serial.print(": ");
  Serial.println(Nitrogen_val);
  delay(50);
}
void NPK_Phosphorous_Runnable(void) {
  phosphorous_val = phosphorous();
  Serial.print("P ");
  Serial.print(": ");
  Serial.println(phosphorous_val);

  delay(50);
}
void NPK_Potassium_Runnable(void) {
  potassium_val = potassium();
  Serial.print("K ");
  Serial.print(": ");
  Serial.println(potassium_val);
}
