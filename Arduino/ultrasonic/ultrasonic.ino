#include <HCSR04.h>
#include <ArduinoJson.h>

UltraSonicDistanceSensor sabun(3, 2);
UltraSonicDistanceSensor air(10, 9);

float maxAir = 10.0;
float minAir = 50.0;
float counterAir = minAir - maxAir;
float maxSabun = 10.0;
float minSabun = 50.0;
float counterSabun = minSabun - maxSabun;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  String data = "{\"device\":\"device.json\",";
  // put your main code here, to run repeatedly:
  float sabunFill = sabun.measureDistanceCm();
  float airFill = air.measureDistanceCm();
  airFill = 100.0 - ((airFill - 10.0) / counterAir * 100);
  sabunFill = 100.0 - ((sabunFill - 10.0) / counterSabun * 100.0);
  if (airFill > 100.0 || airFill < 0.0){
    if (airFill > 100.0){
      data += "\"air\":100.0,";
    }else {
      data += "\"air\":0.0,";
    }
  }
  else {
    data += "\"air\":"+String(airFill)+",";
  }
  if (sabunFill > 100.0 || sabunFill < 0.0){
    if (sabunFill > 100.0){
      data += "\"sabun\":100.0}";
    }else {
      data += "\"sabun\":0.0}";
    }
  }
  else {
    data += "\"sabun\":"+String(sabunFill)+"}";
  }

  Serial.println(data);
  delay(500);
}
