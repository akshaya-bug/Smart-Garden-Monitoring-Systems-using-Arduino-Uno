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
// Dry sensor gives a high value
// Wet sensor gives a low value
const int dryValue = 1023;
const int wetValue = 250;

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
}

void loop()
{
  int rainValue = analogRead(rainPin);

  // Convert to Rain Percentage
  int rainPercent = map(rainValue, dryValue, wetValue, 0, 100);
  rainPercent = constrain(rainPercent, 0, 100);

  String condition;

  if (rainPercent < 20)
  {
    condition = "DRY";
    noTone(buzzer);
  }
  else if (rainPercent < 60)
  {
    condition = "DRIZZLE";
    tone(buzzer, 1000);
  }
  else
  {
    condition = "HEAVY RAIN";
    tone(buzzer, 1000);
  }

  // OLED Display
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(10,0);
  display.println("Rain Monitor");

  display.setCursor(0,16);
  display.print("Rain : ");
  display.print(rainPercent);
  display.println("%");

  display.setCursor(0,30);
  display.print("Status: ");
  display.println(condition);

  // Simple Raindrop Icon
  display.fillCircle(108, 12, 3, WHITE);
  display.drawLine(108, 15, 108, 22, WHITE);
  display.drawLine(106, 18, 108, 22, WHITE);
  display.drawLine(110, 18, 108, 22, WHITE);

  // Warning Message
  if (rainPercent >= 20)
  {
    display.setCursor(0,50);
    display.println("CLOSE THE WINDOW!");
  }

  display.display();

  // Serial Monitor
  Serial.print("Raw Value : ");
  Serial.print(rainValue);

  Serial.print("   Rain : ");
  Serial.print(rainPercent);

  Serial.print("%   Status : ");
  Serial.println(condition);

  delay(1000);
}