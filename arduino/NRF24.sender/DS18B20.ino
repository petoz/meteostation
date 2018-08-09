#ifdef SENSOR_DS18B20
#ifndef SENSOR_DHT22

#include <OneWire.h>
#include <DallasTemperature.h>

const int pinCidlaDS = 5;
OneWire oneWireDS(pinCidlaDS);
// vytvoření instance senzoryDS z knihovny DallasTemperature
DallasTemperature senzoryDS(&oneWireDS);

void setupSensor() {
  senzoryDS.begin();
}

float readTemp() {
  senzoryDS.requestTemperatures();
  t = senzoryDS.getTempCByIndex(0);
  //t = dht.readTemperature();
  return t;
}

float readHum() {
  h = 0.0;
  return h;
}


#endif
#endif

