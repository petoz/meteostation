#ifdef SENSOR_DHT22
//#ifndef ENABLE_DS18B20

//****DHT part
#include "DHT.h"
//#define DHTPIN 5     // what digital pin we're connected to
#define DHTPIN 5     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
//****DHT part

//#endif
#endif
