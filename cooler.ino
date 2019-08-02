
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
int Switch_pin = 5;
int LED_pin = 22;
int Relay_pin = 23;
int switchVal = 0;
int relayVal = 0;

bool coolerOn = false;


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
  switchVal = digitalRead(Switch_pin);
  relayVal = digitalRead(Relay_pin);

  Serial.print("Switch State: ");
  Serial.print(switchVal); 
  Serial.print(" / Relay State: ");
  Serial.print(relayVal); 

  Serial.println();
  Serial.print(Fahrenheit);
  Serial.print("F ");
  Serial.print(Celsius);
  Serial.print("C / ");

  Serial.println();

  delay (250);


  if (switchVal == 1){
    if (coolerOn == false){
      //Turn cooler & LED on
      digitalWrite(Relay_pin,HIGH);
      digitalWrite(LED_pin,HIGH);
      coolerOn = true;
    } else {
      //Turn cooler & LED off
      digitalWrite(Relay_pin,LOW);
      digitalWrite(LED_pin,LOW);
      coolerOff = false;
    }

    relayVal = digitalRead(Relay_pin);
  }
  
  
}
