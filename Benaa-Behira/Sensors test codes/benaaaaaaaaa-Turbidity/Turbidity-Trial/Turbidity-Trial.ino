#define TURBIDITY_PIN 34
int ADC_Read;
double Volt_out;
double Volt_in;
double Volt_in_avg;
double NTU;
long avg;
void setup() {
  pinMode(TURBIDITY_PIN,INPUT);
  Serial.begin(9600);
}

void loop() {
  Volt_in_avg=0;
  /*ADC_Read=analogRead(TURBIDITY_PIN);
  Volt_out=(3.3 * ADC_Read) / 4096.0;
  Volt_in = Volt_out/ 0.2;
  Volt_in_avg+=Volt_in;*/
  for (int i=0; i<600; i++)
  {
    ADC_Read=analogRead(TURBIDITY_PIN);
    Volt_out=(3.3 * ADC_Read) / 4096.0;
    Volt_in= Volt_out/ 0.2;
    Volt_in_avg= Volt_in_avg+Volt_in;
  }
  Volt_in_avg/=600;
  Volt_in_avg += 0.54;
  Volt_in_avg  = round_to_dp(Volt_in_avg,1);
  //Volt_in_avg*=1000;
  //avg = Volt_in_avg;
  //NTU = map(avg,0,4200,0,3500);
  //NTU = 3500-NTU;
   if(Volt_in_avg < 2.5){                  //The equation only works between 2.5V ~ 4.2V,
      NTU = 3000;                    //so set any readings below 2.5V with 3000NTU
    }
    else
    {
      NTU = ((double)-1120.4 * (double)(Volt_in_avg*Volt_in_avg)) + ((double)(5742.3 * Volt_in_avg)) - (double)4352.9; 
    }
    if(NTU <0){
      NTU = 0;                       //If the NTU turns out to be under 0, set it to 0.
    }

  Serial.print("ADC_Read : ");
  Serial.println(ADC_Read);
  Serial.println("VoltIn : ");
  Serial.println(Volt_in);
  Serial.println("Volt_in_avg : ");
  Serial.println(Volt_in_avg);
  Serial.println("NTU :  ");
  Serial.println(NTU);
Serial.println("");

  delay(5000);

}

float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}