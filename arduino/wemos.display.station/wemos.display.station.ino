#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid     = "espwifi";
const char* password = "Passw0rd";

#include <Adafruit_SSD1306.h>

#define OLED_RESET 0  // GPIO0

Adafruit_SSD1306 display(OLED_RESET);

/*#if (SSD1306_LCDHEIGHT != 48)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif*/

void setup() {
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48)
  display.display();
  delay(500);
  display.clearDisplay();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  int counter = 0;
  //while ( WiFi.status() != WL_CONNECTED ) {
  while ( counter < 12 ) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("wifi conn...");
    display.println(counter);
    display.display();
    delay(500);
    counter++;
  }
}

void loop() {

  HTTPClient http;
  http.begin("http://coffee.onmypc.net/meteotemplate/meteotemplateLive.txt"); //HTTP

  Serial.print("[HTTP] GET...\n");
  int httpCode = http.GET();
  String payload = http.getString();
  Serial.println(payload);
  int from = payload.indexOf("T\":");
  int to = payload.indexOf("H\":");
  //String temp = payload;
  String tout = payload.substring(from+3, to-2);
  Serial.println(tout);
  from = payload.indexOf("H\":");
  to = payload.indexOf("TBAT\":");
  String hout = payload.substring(from+3, to-2);
  Serial.println(hout);
  from = payload.indexOf("TIN\":");
  to = payload.indexOf("HIN\":");
  String tin = payload.substring(from+5, to-2);
  Serial.println(tin);
  from = payload.indexOf("HIN\":");
  to = payload.indexOf("UTime\":");
  String hin = payload.substring(from+5, to-2);
  Serial.println(hin);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.setTextSize(1);
  display.print("T:");
  display.print(tout);
  display.println("*C");
  /*display.drawPixel(60,2, WHITE);   //draw dot sing of celsius)
  display.drawPixel(61,2, WHITE);
  display.drawPixel(62,2, WHITE);
  display.drawPixel(61,1, WHITE);
  display.drawPixel(61,3, WHITE);*/
  //display.setTextSize(2);
  display.print("H:");
  display.print(hout);
  display.println("%");
  display.setCursor(0,22);
  //display.setCursor(0,27);    //for size 2 font
  display.print("Tin");
  display.print(tin);
  display.println("*C");
  display.print("Hin");
  display.print(hin);
  display.println("%");
  /*display.drawPixel(60,28, WHITE);    //drah % gfx symbol
  display.drawPixel(61,28, WHITE);
  display.drawPixel(60,29, WHITE);
  display.drawPixel(61,29, WHITE);
  display.drawPixel(63,28, WHITE);
  display.drawPixel(63,29, WHITE);
  display.drawPixel(63,30, WHITE);
  display.drawPixel(63,31, WHITE);
  display.drawPixel(62,32, WHITE);
  display.drawPixel(62,33, WHITE);
  display.drawPixel(62,34, WHITE);
  display.drawPixel(62,35, WHITE);
  display.drawPixel(61,36, WHITE);
  display.drawPixel(61,37, WHITE);
  display.drawPixel(61,38, WHITE);
  display.drawPixel(61,39, WHITE);
  display.drawPixel(60,40, WHITE);
  display.drawPixel(60,41, WHITE);
  display.drawPixel(60,42, WHITE);
  display.drawPixel(60,43, WHITE);
  display.drawPixel(62,42, WHITE);
  display.drawPixel(63,42, WHITE);
  display.drawPixel(62,43, WHITE);
  display.drawPixel(63,43 , WHITE);*/
  //display.println("%");
  display.display();
  delay(30000);
  display.clearDisplay();
  }
