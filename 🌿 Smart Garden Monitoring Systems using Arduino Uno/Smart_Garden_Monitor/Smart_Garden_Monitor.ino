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

const int greenLED = 6;
const int redLED = 7;

// Calibration Values
const int soilDry = 1023;
const int soilWet = 300;

const int rainDry = 1023;
const int rainWet = 250;

void setup()
{
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    while (1);
  }

  display.clearDisplay();
}

void loop()
{
  // -------- Read Sensors --------
  int soilRaw = analogRead(soilPin);
  int rainRaw = analogRead(rainPin);

  // Convert to Percentage
  int soilPercent = map(soilRaw, soilDry, soilWet, 0, 100);
  soilPercent = constrain(soilPercent, 0, 100);

  int rainPercent = map(rainRaw, rainDry, rainWet, 0, 100);
  rainPercent = constrain(rainPercent, 0, 100);

  String recommendation;

  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);

  // -------- Decision Logic --------
  if (soilPercent < 40)
  {
    if (rainPercent < 20)
    {
      recommendation = "WATER THE PLANT";
      digitalWrite(redLED, HIGH);
    }
    else
    {
      recommendation = "WAIT FOR RAIN";
      digitalWrite(redLED, HIGH);
    }
  }
  else
  {
    recommendation = "SOIL GOOD";
    digitalWrite(greenLED, HIGH);
  }

  // -------- OLED Display --------
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(8,0);
  display.println("SMART GARDEN");

  display.drawLine(0,10,127,10,WHITE);

  display.setCursor(0,16);
  display.print("Soil : ");
  display.print(soilPercent);
  display.println("%");

  display.setCursor(0,30);
  display.print("Rain : ");

  if(rainPercent < 20)
    display.println("DRY");
  else if(rainPercent < 60)
    display.println("DRIZZLE");
  else
    display.println("HEAVY");

  display.drawLine(0,42,127,42,WHITE);

  display.setCursor(0,48);
  display.println("Recommendation:");

  display.setCursor(0,58);
  display.println(recommendation);

  display.display();

  // -------- Serial Monitor --------
  Serial.println("-----------------------------");
  Serial.print("Soil Moisture : ");
  Serial.print(soilPercent);
  Serial.println("%");

  Serial.print("Rain Level    : ");
  Serial.print(rainPercent);
  Serial.println("%");

  Serial.print("Decision      : ");
  Serial.println(recommendation);

  Serial.println("-----------------------------");

  delay(1000);
}