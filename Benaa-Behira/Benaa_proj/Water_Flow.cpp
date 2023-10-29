/**
 ************************************************************************                  
 * @file                    : Water_Flow.c
 * @author                  : Ahmed Hesham
 * @brief                   : Water Flow Sensor source file
 
 sensor works on Hall effect base. rotation of its wings result in number of pulses that is calculated through interrupt method.
 get number of pulses generated in defined time (1s), then obtain the flow rate and water produced through formulas illustrated in WaterFlow_Runnable()
 ************************************************************************
 */

 #include "Water_Flow.h"

long currentMillis = 0;
long previousMillis = 0;

//calibrationFactor is diffrent from sensor to another according to the rate of pulses it generates for a specific flow
//you can determine the calibrationFactor of your sensor by a try&error approch. Simplest way is to pass a defined amount of water through the sensor,
//then compare the reading on your serial monitor of the flowMilliLitres value with your known volume then start to change the calibrationFactor 
//according to the variation
double calibrationFactor = .8;// 5.5for ys-DN50

volatile unsigned long pulseCount;
unsigned long pulse1Sec = 0;
double flowRate;
unsigned int  flowMilliLitres=0;

void IRAM_ATTR  pulseCounter()
{
  pulseCount++;
  
}

void WaterFlow_Init(void) {

  pinMode(WATERFLOWPIN, INPUT_PULLUP);
  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  previousMillis = 0;
  attachInterrupt(digitalPinToInterrupt(WATERFLOWPIN), pulseCounter, RISING);
}

void WaterFlow_Runnable(void) {

  currentMillis = millis();
  //run the logic every 1 sec
  if (currentMillis - previousMillis >= FLOW_TIME_INTERVAL) {
    
    pulse1Sec = pulseCount;
    //Serial.println(pulseCount);
    pulseCount = 0;

  /*GENERAL CODE NOTES
    // Because this loop may not complete in exactly 1 second intervals we calculate
    // the number of milliseconds that have passed since the last execution and use
    // that to scale the output. We also apply the calibrationFactor to scale the output
    // based on the number of pulses per second per units of measure (litres/minute in
    // this case) coming from the sensor.
  */

    flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
    previousMillis = millis();

/*GENERAL CODE NOTES
    // Divide the flow rate in litres/minute by 60 to determine how many litres have
    // passed through the sensor in this 1 second interval, then multiply by 1000 to
    // convert to millilitres.
*/  

    flowMilliLitres += (flowRate * 1000) / 60 ;

    // Print the flow rate for this second in litres / minute
    Serial.print("Flow rate: ");
    Serial.print(flowRate);  // Print the integer part of the variable
    Serial.print("L/min");
    Serial.print("\t");       // Print tab space

    // Print the cumulative total of litres flowed since starting
    Serial.print("Output Liquid Quantity: ");
    Serial.print(flowMilliLitres);
    Serial.println("mL / ");
    Serial.print(flowMilliLitres / 1000);
    Serial.println("L");
  }

}