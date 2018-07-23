#ifdef SENSOR_DHT22
#ifndef SENSOR_DS18B20

#include "DHT.h"
#define DHTPIN 5     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
//****DHT part

void setupSensor() {
  dht.begin();
}

float readTemp() {
  t = dht.readTemperature();
  return t;
}

float readHum() {
  h = dht.readHumidity();
  return h;
}


bool sensorOK() {
if (isnan(readHum()) || isnan(readTemp())) {
  Serial.println("Failed to read from DHT sensor!");
  digitalWrite(ledPin, HIGH);
  delay(50);
  digitalWrite(ledPin, LOW);
  delay(100);
  digitalWrite(ledPin, HIGH);
  delay(50);
  digitalWrite(ledPin, LOW);
  delay(100);
  digitalWrite(ledPin, HIGH);
  delay(50);
  digitalWrite(ledPin, LOW);
  delay(100);
  LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF); //z 22mA na 6.39mA
  delay(100);
  //return;
  }
}


#endif
#endif
