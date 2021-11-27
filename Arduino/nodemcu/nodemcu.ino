#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

const char* ssid = "OPPO A12";
const char* password = "1234duakali";
const char* server = "http://niuva.net/v0/public/Device";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("connected with Ip: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    String data = Serial.readStringUntil('\n');
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, data);
    if (error){
      Serial.println(data);
      Serial.println("error");
      return;
    }
    String device = doc["device"];
    float sabun = doc["sabun"];
    float air = doc["air"];
    WiFiClient client;
    HTTPClient http;
    http.begin(client, server);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String sensor = "device="+ device +"&sabun="+ String(sabun) +"&air="+ String(air);
    int httpResponseCode = http.POST(sensor);
    if (httpResponseCode > 0){
      
    }
    Serial.println(http.getString());
    http.end();
  }
}
