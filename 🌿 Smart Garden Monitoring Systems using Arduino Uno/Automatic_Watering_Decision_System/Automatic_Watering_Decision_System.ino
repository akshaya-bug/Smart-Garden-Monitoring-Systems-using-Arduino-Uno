#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pin Definitions
const int rainPin = A0;
const int buzzer = 8;

// Calibration Values
// Adjust according to your sensor readings
const int dryValue = 1023;
const int wetValue = 250;

// Variables
bool rainDetected = false;
int rainCount = 0;

void setup()
{
  pinMode(buzzer, OUTPUT);
  noTone(buzzer);

  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    while (1);
  }

  display.clearDisplay();
  display.display();
}

void loop()
{
  // Read Sensor
  int rainRaw = analogRead(rainPin);

  // Convert to Rain Percentage
  int rainPercent = map(rainRaw, dryValue, wetValue, 0, 100);
  rainPercent = constrain(rainPercent, 0, 100);

  bool isRaining = (rainPercent >= 20);

  // Count Rain Events
  if (isRaining && !rainDetected)
  {
    rainDetected = true;
    rainCount++;
  }

  if (!isRaining)
  {
    rainDetected = false;
  }

  // OLED Display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(18,0);
  display.println("Rain Monitor");

  display.drawLine(0,10,127,10,WHITE);

  display.setCursor(0,16);
  display.print("Rain : ");
  display.print(rainPercent);
  display.println("%");

  display.setCursor(0,28);
  display.print("Events : ");
  display.println(rainCount);

  if (isRaining)
  {
    tone(buzzer, 1000);

    display.setCursor(0,42);
    display.println("RAIN DETECTED!");

    display.setCursor(0,54);
    display.println("CLOSE WINDOW!");
  }
  else
  {
    noTone(buzzer);

    display.setCursor(0,42);
    display.println("Status : DRY");

    display.setCursor(0,54);
    display.println("Window Safe");
  }

  display.display();

  // Serial Monitor
  Serial.print("Rain Raw : ");
  Serial.print(rainRaw);

  Serial.print("   Rain % : ");
  Serial.print(rainPercent);

  Serial.print("   Events : ");
  Serial.println(rainCount);

  delay(500);
}