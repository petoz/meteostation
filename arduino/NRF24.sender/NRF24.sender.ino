// nRF24L01 vysílač

//#define SENSOR_DHT22  //if DHT22 sensor is used
//#define SENSOR_DS18B20  //if D18b20b sensor is used
#define NO_SENSOR   //if no sensor is used, for test only RF24
//#define BATTERY   //if battery voltage is measured

#include "RF24.h"
#include "LowPower.h"

const int ledPin =  13;      // the number of the LED pin

#define CE A0
#define CS A1
RF24 nRF(CE, CS);
byte adresaPrijimac[5] = {0x76,0x79,0x73,0x30,0x30};    //raspberry
unsigned char ADDRESS0[5]  =
{
  0xb5,0x43,0x88,0x99,0x45
}; // Define a static TX address
//just change b1 to b2 or b3 to send to other pip on receiver

String String_sum;
int msg[1];

void setup() {
  Serial.begin(57600);
  Serial.println("Ja som vysielac 1.12");
  Serial.print(ADDRESS0[0],HEX);
  Serial.print(ADDRESS0[1],HEX);
  Serial.print(ADDRESS0[2],HEX);
  Serial.print(ADDRESS0[3],HEX);
  Serial.println(ADDRESS0[4],HEX);
  pinMode(ledPin, OUTPUT);
  delay(2000);
  digitalWrite(ledPin, HIGH);
  delay(300);
  digitalWrite(ledPin, LOW);
  delay(50);
  digitalWrite(ledPin, HIGH);
  delay(50);
  digitalWrite(ledPin, LOW);
  delay(50);
  digitalWrite(ledPin, HIGH);
  delay(300);
  digitalWrite(ledPin, LOW);
  delay(2000);
  // zapnutí komunikace nRF modulu
  nRF.begin();
  // nastavení výkonu nRF modulu,
  // pro HIGH a MAX je nutný externí 3,3V zdroj
  //nRF.setPALevel(RF24_PA_MAX);        //pre ladenie spotreby docasne !!!, potom max
  /*pre MIN 18,6uA v klude;pocas trvaleho vysielania 6.17mA -MIN
   * LOW 6,64mA
   * HIGH 7,99mA
   * MAX 10,17mA
   * pre nRF.PowerDown() spotreba 1.5uA
   * pre startListening spotreba 13,9mA pre MIN-MAX
  */
  /*celkova spotreba 27,7mA
   *
   */
  // the following statements improve transmission range
  //nRF.setPayloadSize(4); // setting the payload size to the needed value - pre zvacsenie dosahu
  nRF.setDataRate(RF24_250KBPS); // reducing bandwidth  - pre zvacsenie dosahu
  // nastavení zapisovacího a čtecího kanálu
  Serial.print("PALevel=");
  Serial.println(nRF.getPALevel());
  //nRF.setPALevel(RF24_PA_LOW);//s LOW v pivnici OK
  //nRF.setPALevel(RF24_PA_MIN);//s MIN v pivnici - ide ale nespolahlivo
  //nRF.setPALevel(RF24_PA_HIGH);//s  v pivnici - ?
  nRF.setPALevel(RF24_PA_MAX);//s  v pivnici - ?
  Serial.print("PALevel=");
  Serial.println(nRF.getPALevel());
  Serial.print("DataRate=");
  Serial.println(nRF.getDataRate());
  Serial.print("PayloadSize=");
  Serial.println(nRF.getPayloadSize());
  //I succeded to improve the range with a Payload size of about 8 bytes (I had 12 before), this gave me about 80 meters range in open air
  nRF.setPayloadSize(1);
  Serial.print("PayloadSize=");
  Serial.println(nRF.getPayloadSize());
  Serial.print("Channel=");
  Serial.println(nRF.getChannel());
  //Set radio.setChannel(108); 2.508 Ghz - Above most Wifi Channels
  nRF.setChannel(125);
  Serial.print("Channel=");
  Serial.println(nRF.getChannel());
  //nRF.openWritingPipe(adresaVysilac);
  //nRF.openReadingPipe(1, adresaPrijimac);   //raspberry
  nRF.openWritingPipe(ADDRESS0);
  nRF.openReadingPipe(0,ADDRESS0);
  setupSensor();
}

float t;
float h;

void loop() {
  delay(10);
  t = readTemp();
  Serial.print("Teplota:");
  Serial.println(t);
  h = readHum();
  Serial.print("Vlhkost:");
  Serial.println(h);

#ifdef DHT22
if (sensorOK()) {
}
#endif

  #ifdef BATTERY
  float BatVoltageP=BatVoltagePercent();
  #endif

  #ifndef BATTERY
  float BatVoltageP=99.9;
  #endif

  String_sum = String(t+200) + String(h+200);
  String_sum = String_sum + String(BatVoltageP+200);
  String_sum = String_sum + String( (t+200) + (h+200) );
  Serial.print("Posilam:");
  Serial.println(String_sum);
  digitalWrite(ledPin,HIGH);    //turn on led while sending data
  nRF.powerUp();
  int messageSize = String_sum.length();
   for (int i = 0; i < messageSize; i++) {
    int charToSend[1];
    charToSend[0] = String_sum.charAt(i);
    nRF.write(charToSend,1);
  }

//send the 'terminate string' value...
  msg[0] = 2;
  nRF.write(msg,1);
  nRF.powerDown();

//  delay(30);    //kvoli dokonceniu serial.print pred power down
  digitalWrite(ledPin,LOW);   //turn off led after sending data
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); //z 22mA na 6.39mA
  delay(10);    //skuska kvoli cyklickemu resetu
  //spotreba dole z 21.2mA na 11.8mA.
}
