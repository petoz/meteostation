#define SENSOR_DHT22
// nRF24L01 vysílač

// připojení knihoven
//#include <SPI.h>
#include "RF24.h"
#include "LowPower.h"

const int ledPin =  13;      // the number of the LED pin

int BatInput = A2; //cislo analogoveho vstupu
float BatVoltageD; //napatie baterie 0-1023
float BatVoltageA; //napatie baterie V
float BatVoltageP; //napatie baterie Percent

// nastavení propojovacích pinů nRF24l01
//#define CE 7
//#define CS 8

#define CE A0
#define CS A1
// inicializace nRF s piny CE a CS
RF24 nRF(CE, CS);
// nastavení adres pro přijímač a vysílač,
// musí být nastaveny stejně v obou programech!
//byte adresaPrijimac[] = "prijimac00";
byte adresaPrijimac[5] = {0x76,0x79,0x73,0x30,0x30};    //raspberry
//byte adresaVysilac[] = "vysilac00";
//byte adresaVysilac[] = "vys02";
//byte adresaVysilac[] = "vys02";
//unsigned char adresaVysilac[5]  = {0x76,0x79,0x73,0x30,0x31}; // Define a static TX address "vys01" - arduino1
//unsigned char adresaVysilac[5]  = {0x76,0x79,0x73,0x30,0x32}; // Define a static TX address "vys02"
//unsigned char adresaVysilac[5]  = {0x76,0x79,0x73,0x30,0x33}; // Define a static TX address "vys03"
//unsigned char adresaVysilac[5]  = {0x76,0x79,0x73,0x30,0x34}; // Define a static TX address "vys04"
//unsigned char adresaVysilac[5]  = {0x76,0x79,0x73,0x30,0x35}; // Define a static TX address "vys05"
unsigned char ADDRESS0[5]  =
{
  0xb4,0x43,0x88,0x99,0x45
}; // Define a static TX address
//just change b1 to b2 or b3 to send to other pip on resciever


#define SENSOR_DHT22

//float t=-39.87;
float t;
//float h=99.99;
float h;
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
  
  //*DHT part
  dht.begin();
  //*DHT part
}

void loop() {

  //*read batter voltage part
  BatVoltageD = analogRead(BatInput);
  BatVoltageA = BatVoltageD * (3.3 / 1023.0);
  BatVoltageP = BatVoltageD/1023*100;
  Serial.print("Napatie dig=");
  Serial.println(BatVoltageD);
  Serial.print("Napatie V=");
  Serial.print(BatVoltageA);
  Serial.print("Napatie V%=");
  Serial.println(BatVoltageP);
  //*read batter voltage part

  //*DHT part
  //dht.begin();
  delay(10);
  t = dht.readTemperature();
  Serial.print("Teplota:");
  Serial.println(t);
  h = dht.readHumidity();
  Serial.print("Vlhkost:");
  Serial.println(h);
  //*DHT part

  if (isnan(h) || isnan(t)) {
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
    return;
  }

  String_sum = String(t+200) + String(h+200);
  String_sum = String_sum + "wWw" + String(BatVoltageP+200) + "bat";
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

/*  Serial.print("Posilam vlhkost ");
  Serial.print(h);
  Serial.println("%\t");
  if (nRF.write(&h, sizeof(h) )) {
    //Serial.println("Sent hum. OK");
  }
    else {
      Serial.print("Sent hum. error");
      delay(2500);
      return;
    }*/
    

//  delay(30);    //kvoli dokonceniu serial.print pred power down
  digitalWrite(ledPin,LOW);   //turn off led after sending data
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); //z 22mA na 6.39mA
  delay(10);    //skuska kvoli cyklickemu resetu
  //spotreba dole z 21.2mA na 11.8mA.
}

