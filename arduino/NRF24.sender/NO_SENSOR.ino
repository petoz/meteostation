#ifdef NO_SENSOR
#ifndef DHT22
#ifndef DS18B20

void setupSensor() {
  Serial.println("No sensor, simulation only");
}

float readTemp() {
  t = 12.3;
  return t;
}

float readHum() {
  h = 45.6;
  return h;
}

#endif
#endif
#endif

