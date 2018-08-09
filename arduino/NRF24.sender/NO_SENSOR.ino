#ifdef NO_SENSOR
#ifndef DHT22
#ifndef DS18B20

void setupSensor() {
  Serial.println("No sensor, simulation only");
}

float readTemp() {
  t = 12.34;
  return t;
}

float readHum() {
  h = 56.78;
  return h;
}

#endif
#endif
#endif

