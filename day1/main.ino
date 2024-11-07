// all the libraries are classes
#include <DHT.h>
#include <SoftwareSerial.h>
#include <Wire.h>

// dht data pin is connected to pin 9
#define dhtPin 9 

// soil moisture pin is connected pin A0
#define soilPin A0

// RO - Receiver Output
#define roPin 2

// RE - Receiver Enable
#define rePin 8

// DE - Data Enable
#define dePin 7

// DI - Data Input
#define diPin 3

// define an object for the DHT class
DHT dht(dhtPin,DHT11); // two arguments (dhtPin Number, type of sensor)

// define nitrogen request
const byte nitrogenRequest[] = {0x01,0x03,0x00,0x1e,0x00,0x01,0xe4,0x0c};
const byte phosphorousRequest[] = {0x01,0x03,0x00,0x1f,0x00,0x01,0xb5,0xcc};
const byte potassiumRequest[] = {0x01,0x03,0x00,0x20,0x00,0x01,0x85,0xc0};

// store the result of NPK sensor
byte values[11];

// serial object to read from RS485 Convertor
SoftwareSerial mod(roPin,diPin); // 2,3

void setup() {
  pinMode(soilPin,INPUT); // initialise the sensors (S1,S2 - Digital and Analog)
  
  // initialise the DHT11 
  dht.begin();

  Serial.begin(9600); // 9600bps - speed of communication
  mod.begin(9600); // 9600bps

  pinMode(rePin,OUTPUT);
  pinMode(dePin,OUTPUT); // 4 - pins from RS485 (2-pins are mod, 2-pins are OUTPUT)
}

void loop() {
  float h=dht.readHumidity(); // reading the humidity from DHT sensor
  float t=dht.readTemperature(); // reading the temperature from DHT sensor
  float m=analogRead(soilPin); // reading analog value in digital format 

  // nan - not a number
  if(isnan(h)||isnan(t)){
    Serial.println("DHT Error");
    return;
  }

  Serial.print("H: ");
  Serial.print(h);
  Serial.print(",T: ");
  Serial.print(t);
  Serial.print(",M: ");
  Serial.println(m); // ((sv)/5)*1023 = 234 - resolution (10-bit) = 2^10 = 1024-1 = 1023 

  byte nValue, pValue, kValue;

  nValue=readNitrogen();
  delay(250);
  pValue=readPhosphorous();
  delay(250);
  kValue=readPotassium();
  delay(250);
  
  Serial.print("N: ");
  Serial.print(nValue);
  Serial.print(" mg/kg");
  Serial.print(", P: ");
  Serial.print(pValue);
  Serial.print(" mg/kg");
  Serial.print(", K: ");
  Serial.print(kValue);
  Serial.print(" mg/kg");
  Serial.println();
  delay(4000); // 4 seconds - 4000ms 
}

byte readNitrogen(){
  // request to RS485 to NPK Sensor
  // NPK Sensor will send response to RS485 to Arduino
  digitalWrite(dePin,1);
  digitalWrite(rePin,1);
  delay(10); // wait for 10ms
  if(mod.write(nitrogenRequest,sizeof(nitrogenRequest))==8){
    digitalWrite(dePin,0);
    digitalWrite(rePin,0);
    for(byte i=0;i<7;i++){
      values[i]=mod.read();
      Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}

byte readPhosphorous(){
  digitalWrite(dePin,1);
  digitalWrite(rePin,1);
  delay(10);
  if(mod.write(phosphorousRequest,sizeof(phosphorousRequest))==8){
    digitalWrite(dePin,0);
    digitalWrite(rePin,0);
    for(byte i=0;i<7;i++){
      values[i]=mod.read();
      Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}

byte readPotassium(){
  digitalWrite(dePin,1);
  digitalWrite(rePin,1);
  delay(10);
  if(mod.write(potassiumRequest,sizeof(potassiumRequest))==8){
    digitalWrite(dePin,0);
    digitalWrite(rePin,0);
    for(byte i=0;i<7;i++){
      values[i]=mod.read();
      Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}
