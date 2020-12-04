#include <libraries/DHT.h>
#include <DHT_U.h>

#include <SPI.h>
#include <libraries/Adafruit_GFX.h>
#include <libraries/TFT_ILI9163C.h>
// Color definitions
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define __CS 10
#define __DC 9
#define __RES 8

TFT_ILI9163C tft = TFT_ILI9163C(__CS, __DC, __RES);
int switchPin = 3;
int buttonPin = 4;
int G_ledPin = 5;
int R_ledPin = 6;
int DefTemp = 20;
long previousMillis = 0;

void setup(void) {
  pinMode(G_ledPin, OUTPUT);
  pinMode(R_ledPin, OUTPUT);
  tft.begin();
  tft.setRotation(2);
  tft.fillScreen(BLACK);

  tft.setCursor(0, 35);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("Test"), delay(500), tft.print("."), delay(500), tft.print("."), delay(500), tft.println("."), delay(1000);

  int testTemperature;
  testTemperature = dht.readTemperature();
  if (isnan(testTemperature)) {
    tft.setTextColor(RED);
    tft.print("Checksum error");
    return;
  } else {
    tft.setTextColor(GREEN);
    tft.print("OK");
    return;
  }
  delay(2000);
  tft.clearScreen();
}

int lasthum = 0;
int lasttemp = 0;
int lastDefTemp = 20;
void loop() {
  delay(1000);
  //  DHT.read(DHT11_PIN);
  float humidity = dht.readHumidity(); //Измеряем влажность
  float temperature = dht.readTemperature(); //Измеряем температуру
  if ((lasthum != humidity) || (lasttemp != temperature) || (lastDefTemp != DefTemp)) {
    tft.clearScreen();
    digitalWrite(G_ledPin, HIGH);
    lasthum = humidity;
    lasttemp = temperature;
    lastDefTemp = DefTemp;
  }
  if (digitalRead(switchPin) == HIGH)
  {
    if (millis() - previousMillis > 100)
    {
      previousMillis = millis();
      DefTemp++;
    }
  }
  if (digitalRead(buttonPin) == HIGH)
  {
    if (millis() - previousMillis > 100)
    {
      previousMillis = millis();
      DefTemp--;
    }
  }
  if (DefTemp >= temperature)
  {
    digitalWrite(G_ledPin, HIGH);
    digitalWrite(R_ledPin, LOW);
  }
  else
  {
    digitalWrite(G_ledPin, LOW);
    digitalWrite(R_ledPin, HIGH);
  }
  int chek;
  //  chek = DHT.read(DHT11_PIN);
  tft.setCursor(0, 35);
  tft.setTextSize(2);
  tft.setTextColor(MAGENTA);
  tft.println("  Weather   station");
  tft.setTextColor(WHITE);
  tft.print("Temp: ");
  if (temperature <= 0) {
    tft.setTextColor(WHITE), tft.print(temperature), tft.println("C");
  }
  if (temperature > 0 && temperature <= 10) {
    tft.setTextColor(BLUE), tft.print(temperature), tft.println("C");
  }
  if (temperature > 10 && temperature <= 20) {
    tft.setTextColor(YELLOW), tft.print(temperature), tft.println("C");
  }
  if (temperature > 20 && temperature <= 30) {
    tft.setTextColor(GREEN), tft.print(temperature), tft.println("C");
  }
  if (temperature > 30) {
    tft.setTextColor(RED), tft.print(temperature), tft.println("C");
  }
  tft.setTextColor(WHITE);
  tft.print("Hum: ");
  if (humidity > 0 && humidity <= 40) {
    tft.setTextColor(YELLOW), tft.print(humidity), tft.println("%");
  }
  if (humidity > 40 && humidity <= 60) {
    tft.setTextColor(GREEN), tft.print(humidity), tft.println("%");
  }
  if (humidity > 60 && humidity <= 100) {
    tft.setTextColor(RED), tft.print(humidity), tft.println("%");
  }
  tft.println();
  tft.setTextColor(WHITE);
  tft.print("Set: ");
  if (DefTemp <= 0) {
    tft.setTextColor(WHITE), tft.print(DefTemp), tft.println("C");
  }
  if (DefTemp > 0 && DefTemp <= 10) {
    tft.setTextColor(BLUE), tft.print(DefTemp), tft.println("C");
  }
  if (DefTemp > 10 && DefTemp <= 20) {
    tft.setTextColor(YELLOW), tft.print(DefTemp), tft.println("C");
  }
  if (DefTemp > 20 && DefTemp <= 30) {
    tft.setTextColor(GREEN), tft.print(DefTemp), tft.println("C");
  }
  if (DefTemp > 30) {
    tft.setTextColor(RED), tft.print(DefTemp), tft.println("C");
  }
}
