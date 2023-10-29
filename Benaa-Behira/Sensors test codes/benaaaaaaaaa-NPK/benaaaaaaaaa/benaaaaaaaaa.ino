#include <SoftwareSerial.h>
SoftwareSerial mod(16,17);                        
#define RE 13//13
#define DE 14//14
const byte nitro[] =  {0x01,0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte phos[]  =  {0x01,0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte pota[]  =  {0x01,0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};
const byte test[]  =  {0x01, 0x03, 0x00, 0x00, 0x00, 0x03, 0x05, 0xCB};
byte values[12];

void test_func()
{
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(100);  
  if(mod.write(test,sizeof(test))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    delay(100);
    for(byte i=0;i<12;i++){
    values[i] = mod.read();
    Serial.print(values[i],HEX);
    }
    Serial.println();
  }

  Serial.print("N :");
  Serial.println(values[4]);
  Serial.print("P :");
  Serial.println(values[6]);
  Serial.print("K :");
  Serial.println(values[8]);
}
byte nitrogen(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(100);
  Serial.print("NIT Response: ");
  if(mod.write(nitro,sizeof(nitro))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values[i] = mod.read();
    Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}
 
byte phosphorous(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(100);
  if(mod.write(phos,sizeof(phos))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    Serial.print("PHS Response: ");
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values[i] = mod.read();
    Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}
 
byte potassium(){
  //mod.flushInput();
  // digitalWrite(DE,HIGH);
  // digitalWrite(RE,HIGH);
  // delay(100);
  Serial.print("POT Response: ");
  if(mod.write(pota,sizeof(pota))==8){
    // digitalWrite(DE,LOW);
    // digitalWrite(RE,LOW);
    //mod.flush();
    delay(1000);
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values[i] = mod.read();
    Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}

void setup() {
  Serial.begin(9600);
  mod.begin(9600);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
}

void loop() {
  byte val1,val2,val3,test_para;
  // val1 = nitrogen();
  // delay(250);
  //  val2 = phosphorous();
  //  delay(250);
  //  val3 = potassium();
  // test_para = test_func();
  test_func();
  // Serial.print("test : ");
  // Serial.println(test_para);
  // delay(250);

  // Serial.print("N ");
  // Serial.print(1);
  // Serial.print(": ");
  // Serial.println(val1);
  // Serial.print("P ");
  // Serial.print(2);
  // Serial.print(": ");
  // Serial.println(val2);
  // Serial.print("K ");
  // Serial.print(3);
  // Serial.print(": ");
  // Serial.println(val3);

  for (byte i=0; i<11; i++)
  {
    values[i]=0;
  }

  delay(2000);
}
