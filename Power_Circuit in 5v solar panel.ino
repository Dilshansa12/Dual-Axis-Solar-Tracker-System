// include the library code: 
#include <LiquidCrystal.h> //library for LCD 

// initialize the library with the numbers of the interface pins 
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); 

//Measuring Current Using ACS712 
int sensitivity = 66; // use 100 for 20A Module and 185 for 5A Module 
int adcvalue= 0; 
int offsetvoltage = 2500;  //Sensor Callibration
double Voltage = 0; //voltage measuring 
double Current = 0;// Current measuring 

void setup() 
{
  Serial.begin(9600);
  lcd.begin(20, 4); // set up the LCD's number of columns and rows:
  //lcd.setCursor(0,0);
  //lcd.print("  BRIGHT LIGHT    ");
  lcd.setCursor(0,0);
  lcd.print("  Pwr Measure ");
}  

void loop()
{ 
  // Measure The Votage ***********************************
  // read the input on analog pin A1:
  int sensorValue = analogRead(A1);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float vol = (sensorValue * 5.0) / 1023.0;
  float voltage = (sensorValue * 5.0) / 1023.0;

  // Measure The Current ***********************************
  adcvalue = analogRead(A0);//reading the value from the analog pin A0
  Voltage = (adcvalue / 1024.0) * 1000; // Gets you mV 
  Current = ((Voltage - offsetvoltage) / sensitivity); 

  float Power = voltage*Current;
  Power=-Power/14;
  ///if(Power>1.97){Power=2;}
  //else if(Power<0.02){Power=0.02;}


    // Measure The Power ***********************************
  lcd.setCursor(0,1); 
  lcd.print("  Power: "); 
  lcd.print(Power); 
  Serial.println(Power);
  lcd.print("W"); //unit for the current to be measured 
  delay(200);
}


