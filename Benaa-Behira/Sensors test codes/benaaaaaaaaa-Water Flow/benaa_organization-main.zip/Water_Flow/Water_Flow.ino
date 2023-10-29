/*******flowrate pins****/
#define SENSOR 2
#define INTERVAL 1000
long currentMillis = 0;
long previousMillis = 0;
double calibrationFactor = 4.5;
volatile unsigned long pulseCount;
unsigned long pulse1Sec = 0;
double flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

void IRAM_ATTR  pulseCounter()
{
  pulseCount++;
}


void setup() {

  pinMode(SENSOR, INPUT_PULLUP);
  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  previousMillis = 0;
  attachInterrupt(digitalPinToInterrupt(SENSOR), pulseCounter, RISING);

  Serial.begin(9600);

}

void loop() {
    /**********FLOWRATE*****************/

  currentMillis = millis();
  if (currentMillis - previousMillis >= INTERVAL) {
    
    pulse1Sec = pulseCount;
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
/*
    /*DEV NOTES
    flowMilliLitres += (flowRate * 1000) / 60 ;
*/

    flowMilliLitres = (flowRate * 1000) / 60 ;

    // Add the millilitres passed in this second to the cumulative total
/*
  DEV NOTES
  plan to delete this line and send flowMilliLitres if MQTT connection is stable 
  if stable MQTT connection .. flowMilliLitres is published and get zero value
  if connection is unstable .. flowMilliLitres is accumulated and wait for connection to get back and publish then reinitialised 

  //delete the next line permenantly
*/    
    totalMilliLitres += flowMilliLitres;
    
    // Print the flow rate for this second in litres / minute
    Serial.print("Flow rate: ");
    Serial.print(flowRate);  // Print the integer part of the variable
    Serial.print("L/min");
    Serial.print("\t");       // Print tab space

    // Print the cumulative total of litres flowed since starting
    Serial.print("Output Liquid Quantity: ");
    Serial.print(totalMilliLitres);
    Serial.print("mL / ");
    Serial.print(totalMilliLitres / 1000);
    Serial.println("L");
  }

}