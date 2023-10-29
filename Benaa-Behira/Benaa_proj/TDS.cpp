/**
 ************************************************************************                  
 * @file                    : TDS.c
 * @author                  : Ahmed Hesham
 * @brief                   : TDS Sensor source file

 TDS is analog input sensor. Manual of Sensor will be attached in repo which contain all details needed
 ************************************************************************
 */

#include "TDS.h"

int incomingData_tds = 0;
int analogBuffer[SCOUNT];  // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0, copyIndex = 0;
const float compensationCoefficient = 1.0 + (0.02 * ((float)TEMPERATURE - 25.0));  //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
float averageVoltage;
double TDS_Value;
float compensationVolatge;


void TDS_Init(void) {
  pinMode(TDSPIN, INPUT);
}

// Call TDS_Runnable() in main loop.
void TDS_Runnable(void) {
  //read the analog value and store into the buffer
  analogBuffer[analogBufferIndex] = analogRead(TDSPIN);
  analogBufferIndex++;
  //enter the condition if SCOUNT of readings are obtained
  if (analogBufferIndex == SCOUNT) {
    analogBufferIndex = 0;

    for (copyIndex = 0; copyIndex < SCOUNT; copyIndex++) {
      analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
    }
    averageVoltage = (getMedianNum(analogBufferTemp, SCOUNT) * (float)VREF) / 4096;                                                                                                    // read the analog value more stable by the median filtering algorithm, and convert to voltage value
    compensationVolatge = averageVoltage / compensationCoefficient;                                                                                                                    //temperature compensation
    TDS_Value = (133.42 * compensationVolatge * compensationVolatge * compensationVolatge - 255.86 * compensationVolatge * compensationVolatge + 857.39 * compensationVolatge) * 0.5;  //convert voltage value to tds value
  }
  Serial.print("TDS ");
  Serial.print(": ");
  Serial.println(TDS_Value);
}

//this function is called to get the median value of every 30(SCOUNT) readings of TDS sensor
int getMedianNum(int bArray[], int iFilterLen) {
  int bTab[iFilterLen];
  for (byte i = 0; i < iFilterLen; i++)
    bTab[i] = bArray[i];
  int i, j, bTemp;
  for (j = 0; j < iFilterLen - 1; j++) {
    for (i = 0; i < iFilterLen - j - 1; i++) {
      if (bTab[i] > bTab[i + 1]) {
        bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
      }
    }
  }
  if ((iFilterLen & 1) > 0)
    bTemp = bTab[(iFilterLen - 1) / 2];
  else
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  return bTemp;
}
