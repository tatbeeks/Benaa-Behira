/**
 ************************************************************************                  
 * @file                    : Services.c
 * @author                  : Ahmed Hesham
 * @brief                   : Services source file
 ************************************************************************
 */

#include "Services.h"

//define object
WiFiClient espClient;
PubSubClient client(espClient);
//flag to check the server connectivity in main loop
byte Client_Connectivity_Flag;

//server info
const char* mqttServer = "35.172.244.127";  //mqtt server
const int mqttPort = 1883;                  //mqtt port
const char* mqttUser = "amr";               //mqtt username
const char* mqttPassword = "amr123";        //mqtt password

void Client_Init(void) {
  client.setServer(mqttServer, mqttPort);
}

void Client_Connect(void) {
  //connect to MQTT
  byte repeat = 0;
  //initialise the flag as true
  Client_Connectivity_Flag = 1;
  //try to connect to server twice and put the result of trials in Client_Connectivity_Flag variable
  while ((!client.connected()) && (repeat < 2)) {

    Serial.println("Connecting to MQTT...");

    if (client.connect("", mqttUser, mqttPassword)) {
      Serial.println("connected");
      Client_Connectivity_Flag = 1;
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      Client_Connectivity_Flag = 0;
    }
    repeat++;
    delay(100);
  }
}


//function used to publish the values. Should be called fter Client_Connect() function.
void Client_Publish(void) {
  char result1[3];
  char result2[3];
  char result3[3];
  char result4[8];
  char result6[8];
  char result7[8];
  char result8[8];


  itoa(Nitrogen_val, result1, 10);
  client.publish("NITROGEN/BENAA1", result1);


  itoa(phosphorous_val, result2, 10);
  client.publish("PHOSPHORUS/BENAA1", result2);


  itoa(potassium_val, result3, 10);
  client.publish("POTASSIUM/BENAA1", result3);


  dtostrf(TDS_Value, 6, 2, result4);
  client.publish("TDS/BENAA1", result4);


  dtostrf(flowRate, 6, 2, result6);
  client.publish("FLOWRATE1/BENAA1", result6);


  itoa(flowMilliLitres, result7, 10);
  client.publish("WATERPRODUCED/BENAA1", result7);

  itoa(Power_State, result8, 10);
  client.publish("POWERSTATE/BENAA1", result8);
}
