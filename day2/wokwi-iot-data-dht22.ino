#include <DHTesp.h>
#include <WiFi.h>
#include <ThingSpeak.h>

#define dhtPin 23
DHTesp dht;

const int channelid=2733500;
const char* apikey="8V7Y52A0J5JRKZ12";
const char* ssid="Wokwi-GUEST";
const char* password="";

WiFiClient client;

void setup() {
  // put your setup code here, to run once:
  dht.setup(dhtPin,DHTesp::DHT22);
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  // (Hotspot) AP, (WIFI) STATION
  WiFi.mode(WIFI_STA); // station
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  } // wait until internet is connected
  Serial.println("WiFi Connected");
  ThingSpeak.begin(client); // connect with server only when you have internet
}

void loop() {
  // put your main code here, to run repeatedly:
  TempAndHumidity data=dht.getTempAndHumidity();
  Serial.print("Humidity: ");
  Serial.print(data.humidity);
  Serial.print(",Temperature: ");
  Serial.println(data.temperature);

  ThingSpeak.setField(1,data.humidity);
  ThingSpeak.setField(2,data.temperature);
  int x=ThingSpeak.writeFields(channelid,apikey);
  if(x==200){ // x refers to http response
    Serial.println("Data Uploaded to Cloud");
  } else {
    Serial.println("Data is not uploaded");
  }

  delay(15000); // this speeds up the simulation
}
