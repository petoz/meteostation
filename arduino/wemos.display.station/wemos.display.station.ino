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
    display.setCursor(0, 0);
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
  String tout = payload.substring(from + 3, to - 2);
  Serial.println(tout);
  from = payload.indexOf("H\":");
  to = payload.indexOf("TBAT\":");
  String hout = payload.substring(from + 3, to - 2);
  Serial.println(hout);
  from = payload.indexOf("TIN\":");
  to = payload.indexOf("HIN\":");
  String tin = payload.substring(from + 5, to - 2);
  Serial.println(tin);
  from = payload.indexOf("HIN\":");
  to = payload.indexOf("UTime\":");
  String hin = payload.substring(from + 5, to - 2);
  Serial.println(hin);

  for (int i = 1; i < 30; i++) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("TI/TO");
    display.println(tin.toFloat(), 1);
    display.println(tout.toFloat(), 1);
    display.display();
    delay(2000);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("HI/HO");
    display.println(hin.toFloat(),1);
    display.println(hout.toFloat(),1);
    display.display();
    delay(2000);
  }
}
