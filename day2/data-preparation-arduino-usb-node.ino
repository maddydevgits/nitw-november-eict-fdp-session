// Program Agenda is to send the sensory data to Gateway

#include<DHT.h>
#include<SoftwareSerial.h>

// Sensor Pins
#define dhtPin 9
#define soilPin A0

#define roPin 2
#define rePin 8
#define dePin 7
#define diPin 3

// create objects
DHT dht(dhtPin,DHT11);
SoftwareSerial mod(roPin,diPin); // 2,3

const byte nitrogenRequest[] = {0x01,0x03,0x00,0x1e,0x00,0x01,0xe4,0x0c};
const byte phosphorousRequest[] = {0x01,0x03,0x00,0x1f,0x00,0x01,0xb5,0xcc};
const byte potassiumRequest[] = {0x01,0x03,0x00,0x20,0x00,0x01,0x85,0xc0};

byte values[11];

void setup() {
  pinMode(soilPin,INPUT); // moisture is always an input
  pinMode(rePin,OUTPUT);
  pinMode(dePin,OUTPUT);

  dht.begin();
  Serial.begin(9600);
  mod.begin(9600); // common or default speed - 9600bps
}

void loop() {
  // read data
  int m=analogRead(soilPin); // data from moisture sensor
  float h=dht.readHumidity();
  float t=dht.readTemperature();

  if(isnan(h)||isnan(t)){
    Serial.println("Data Error");
    return;
  }

  byte nValue, pValue, kValue;
  nValue=readNitrogen();
  delay(250);
  pValue=readPhosphorous();
  delay(250);
  kValue=readPotassium();
  delay(250);

  // send data to gateway
  // Format -> Start of Frame Seperator Data Seperator Data Seperator Data..... End of Frame
  Serial.print("#"); // # - SOF
  Serial.print(","); // , - Seperator
  Serial.print(h); // h - humidity
  Serial.print(",");
  Serial.print(t);
  Serial.print(",");
  Serial.print(m);
  Serial.print(",");
  Serial.print(nValue);
  Serial.print(",");
  Serial.print(pValue);
  Serial.print(",");
  Serial.print(kValue);
  Serial.print(",");
  Serial.println("~"); // ~ - EOF
  delay(4000);

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
    }
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
    }
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
    }
  }
  return values[4];
}
