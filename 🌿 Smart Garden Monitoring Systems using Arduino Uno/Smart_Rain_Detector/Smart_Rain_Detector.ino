#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pins
const int soilPin = A0;
const int rainPin = A1;
const int buzzer = 8;

// Calibration Values
const int soilDry = 1023;
const int soilWet = 300;

const int rainDry = 1023;
const int rainWet = 250;

void setup()
{
  pinMode(buzzer, OUTPUT);
  noTone(buzzer);

  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    while (1);
  }

  // Startup Screen
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  display.setCursor(5,15);
  display.println("SMART");

  display.setCursor(10,38);
  display.println("GARDEN");

  display.display();
  delay(1500);

  display.clearDisplay();
}

void loop()
{
  // Read Sensors
  int soilRaw = analogRead(soilPin);
  int rainRaw = analogRead(rainPin);

  // Convert Soil Reading to Percentage
  int soilPercent = map(soilRaw, soilDry, soilWet, 0, 100);
  soilPercent = constrain(soilPercent, 0, 100);

  // Convert Rain Reading to Percentage
  int rainPercent = map(rainRaw, rainDry, rainWet, 0, 100);
  rainPercent = constrain(rainPercent, 0, 100);

  // Soil Status
  String soilStatus;

  if (soilPercent >= 70)
    soilStatus = "WET";
  else if (soilPercent >= 40)
    soilStatus = "NORMAL";
  else
    soilStatus = "DRY";

  // Rain Status
  String rainStatus;

  if (rainPercent < 20)
    rainStatus = "DRY";
  else if (rainPercent < 60)
    rainStatus = "DRIZZLE";
  else
    rainStatus = "HEAVY";

  // Alarm
  if (soilPercent < 40 || rainPercent >= 60)
  {
    tone(buzzer, 1000);
  }
  else
  {
    noTone(buzzer);
  }

  // OLED Dashboard
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(10,0);
  display.println("Smart Garden");

  display.drawLine(0,10,127,10,WHITE);

  display.setCursor(0,16);
  display.print("Soil : ");
  display.print(soilPercent);
  display.println("%");

  display.setCursor(0,28);
  display.print("State: ");
  display.println(soilStatus);

  display.setCursor(0,42);
  display.print("Rain : ");
  display.println(rainStatus);

  // Alert Messages
  if (soilPercent < 40)
  {
    display.setCursor(0,55);
    display.println("WATER PLANT!");
  }
  else if (rainPercent >= 60)
  {
    display.setCursor(0,55);
    display.println("HEAVY RAIN!");
  }

  display.display();

  // Serial Monitor
  Serial.print("Soil: ");
  Serial.print(soilPercent);
  Serial.print("%   Rain: ");
  Serial.print(rainStatus);
  Serial.print("   Rain Value: ");
  Serial.println(rainPercent);

  delay(1000);
}