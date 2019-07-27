
// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 3

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

float Celsius = 0;
float Fahrenheit = 0;

/*
int x = 1;
int ButtonState = 0;
int OldButtonState = LOW;
int NewButtonState = digitalRead(Switch_pin);
*/

int Switch_pin = 5;
int LED_pin = 22;
int Relay_pin = 23;
int val = 0;
int val2 = 0;



void setup() {
  sensors.begin();
  Serial.begin (115200);
  
  pinMode(Switch_pin,INPUT_PULLDOWN);
  pinMode(Relay_pin,OUTPUT);
  digitalWrite(Relay_pin,LOW);
  digitalWrite(LED_pin, LOW);
}

void loop() {
  sensors.requestTemperatures();
  Celsius = sensors.getTempCByIndex(0);
  Fahrenheit = sensors.toFahrenheit(Celsius);

val = digitalRead(Switch_pin);
val2 = digitalRead(Relay_pin);

Serial.print("Switch State: ");
Serial.print(val); 
Serial.println();

delay (1000);


if (val == 1){
digitalWrite(Relay_pin,HIGH);
digitalWrite(LED_pin,HIGH);
 val2 = digitalRead(Relay_pin);
Serial.print("Relay State: ");
Serial.print(val2); 
Serial.println();
}


else {
  digitalWrite(Relay_pin,LOW);
  digitalWrite(LED_pin,LOW);
 Serial.print("Relay State: ");
Serial.print(val2); 
Serial.println();
}
  Serial.print(Celsius);
  Serial.print(" C ");
  Serial.println();
  Serial.print(Fahrenheit);
  Serial.print(" F ");
  Serial.println();
}
