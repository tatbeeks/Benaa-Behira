/**
 ************************************************************************                  
 * @file                    : Turbidity.c
 * @author                  : Ahmed Hesham
 * @brief                   : Turbidity Sensor source file
 ************************************************************************
 */

 #include "Turbidity.h"

int Turbidity_ADC_Read;
double Volt_out;
double Volt_in;
double Volt_in_avg;
double Turbidity_NTU;
long avg;


void Turbidity_Init(void){
  pinMode(TURBIDITY_PIN,INPUT);
}
//* (double)0.176898
void Turbidity_Runnable(void){
  Volt_in_avg=0;
  for (int i=0; i<600; i++)
  {
    Turbidity_ADC_Read=analogRead(TURBIDITY_PIN);
    Volt_out=(3.3 * Turbidity_ADC_Read) / 4096.0;
    Volt_in= (Volt_out * 1.15) / (0.2);
    Volt_in_avg= Volt_in_avg + Volt_in;
  }

  Volt_in_avg/=600;
  Volt_in_avg += 0.9;
  //Volt_in_avg  = round_to_dp(Volt_in_avg,1);

   if(Volt_in_avg < 2.5){                              //The equation only works between 2.5V ~ 4.2V,
      Turbidity_NTU = 3000;                                     //so set any readings below 2.5V with 3000Turbidity_NTU
    }
    else
    {
      Turbidity_NTU = ((double)-1120.4 * (double)(Volt_in_avg*Volt_in_avg)) + ((double)(5742.3 * Volt_in_avg)) - (double)4352.9; 
    }
    if(Turbidity_NTU <0){
      Turbidity_NTU = 0;                       //If the Turbidity_NTU turns out to be under 0, set it to 0.
    }
/*To be deleted on site*/
  Serial.print("Turbidity_ADC_Read : ");
  Serial.println(Turbidity_ADC_Read);
  Serial.println("VoltOut : ");
  Serial.println(Volt_out);
  Serial.println("Volt_in_avg : ");
  Serial.println(Volt_in_avg);
  Serial.println("Turbidity_NTU :  ");
  Serial.println(Turbidity_NTU);
Serial.println("");

}

float round_to_dp( float in_value, int decimal_place)
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}