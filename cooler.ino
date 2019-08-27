
// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// Data wire is plugged into port 3 on the Arduino
#define ONE_WIRE_BUS 3

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

//BLUETOOTH
BLECharacteristic *tempCharacteristic;
bool deviceConnected = false;

#define SERVICE_UUID "41A097F3-2FBB-465F-A208-6783BDA7AC64" 
#define CHARACTERISTIC_UUID_TEMP "F0DD78B6-27A6-444E-B6DD-4D51BAED0651"
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

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
  Serial.begin (9600);
  BLEDevice::init("Cooler1");
  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  tempCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_TEMP,
                      BLECharacteristic::PROPERTY_READ
                    );
  pinMode(Switch_pin,INPUT_PULLDOWN);
  pinMode(Relay_pin,OUTPUT);
  digitalWrite(Relay_pin,LOW);
  digitalWrite(LED_pin, LOW);
  
  //BLE2902 needed to notify
  tempCharacteristic->addDescriptor(new BLE2902());

  // Start the service
  pService->start();

  // Start advertising (showing your ble name to connect to)
  pServer->getAdvertising()->start();
}

void loop() {
  sensors.requestTemperatures();

  Celsius = sensors.getTempCByIndex(0);
  Fahrenheit = sensors.toFahrenheit(Celsius);
  switchVal = digitalRead(Switch_pin);
  relayVal = digitalRead(Relay_pin);

  delay (200);
  //BLUETOOTH
  if (deviceConnected) {
    char temp[8];
    char ble_current[8];
    char ble_level[8];
    dtostrf(Celsius, 1, 2, temp);
    tempCharacteristic->setValue(temp);  
  }

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
      coolerOn = false;
    }

    relayVal = digitalRead(Relay_pin);
  }
  
  
}
