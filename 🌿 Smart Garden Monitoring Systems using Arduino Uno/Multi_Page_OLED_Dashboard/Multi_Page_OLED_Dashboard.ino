#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//---------------- Pins ----------------//
const int soilPin = A0;
const int rainPin = A1;
const int buttonPin = 2;

//------------ Calibration ------------//
// Adjust according to your sensors
const int soilDry = 1023;
const int soilWet = 300;

const int rainDry = 1023;
const int rainWet = 250;

//------------- Variables -------------//
int currentPage = 0;     // 0=Soil  1=Rain  2=Dashboard

bool lastButtonState = HIGH;
bool buttonState = HIGH;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

unsigned long lastAutoSwitch = 0;
const unsigned long autoSwitchTime = 5000;   // 5 seconds

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    while (1);
  }

  // Startup Screen
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,20);
  display.println("SMART");
  display.setCursor(8,42);
  display.println("GARDEN");
  display.display();
  delay(2000);
}

void loop()
{
  //---------------- Read Sensors ----------------//

  int soilRaw = analogRead(soilPin);
  int rainRaw = analogRead(rainPin);

  int soilPercent = map(soilRaw, soilDry, soilWet, 0, 100);
  soilPercent = constrain(soilPercent, 0, 100);

  int rainPercent = map(rainRaw, rainDry, rainWet, 0, 100);
  rainPercent = constrain(rainPercent, 0, 100);

  //---------------- Button ----------------//

  bool reading = digitalRead(buttonPin);

  if (reading != lastButtonState)
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    if (reading != buttonState)
    {
      buttonState = reading;

      if (buttonState == LOW)
      {
        currentPage++;

        if (currentPage > 2)
          currentPage = 0;

        lastAutoSwitch = millis();
      }
    }
  }

  lastButtonState = reading;

  //---------------- Auto Page Change ----------------//

  if (millis() - lastAutoSwitch >= autoSwitchTime)
  {
    currentPage++;

    if (currentPage > 2)
      currentPage = 0;

    lastAutoSwitch = millis();
  }

  //---------------- Rain Status ----------------//

  String rainStatus;

  if (rainPercent < 20)
    rainStatus = "DRY";
  else if (rainPercent < 60)
    rainStatus = "DRIZZLE";
  else
    rainStatus = "HEAVY";

  //---------------- Soil Status ----------------//

  String soilStatus;

  if (soilPercent >= 70)
    soilStatus = "WET";
  else if (soilPercent >= 40)
    soilStatus = "NORMAL";
  else
    soilStatus = "DRY";

  //---------------- OLED ----------------//

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  if (currentPage == 0)
  {
    //================ PAGE 1 =================

    display.setCursor(18,0);
    display.println("SOIL MONITOR");

    display.drawLine(0,10,127,10,WHITE);

    display.setCursor(0,20);
    display.print("Moisture : ");
    display.print(soilPercent);
    display.println("%");

    display.setCursor(0,38);
    display.print("Status : ");
    display.println(soilStatus);

    int bar = map(soilPercent,0,100,0,120);
    display.drawRect(4,52,120,8,WHITE);
    display.fillRect(4,52,bar,8,WHITE);
  }

  else if(currentPage == 1)
  {
    //================ PAGE 2 =================

    display.setCursor(22,0);
    display.println("RAIN SENSOR");

    display.drawLine(0,10,127,10,WHITE);

    display.setCursor(0,20);
    display.print("Rain : ");
    display.print(rainPercent);
    display.println("%");

    display.setCursor(0,38);
    display.print("Status : ");
    display.println(rainStatus);

    int bar = map(rainPercent,0,100,0,120);
    display.drawRect(4,52,120,8,WHITE);
    display.fillRect(4,52,bar,8,WHITE);
  }

  else
  {
    //================ PAGE 3 =================

    display.setCursor(8,0);
    display.println("SMART GARDEN");

    display.drawLine(0,10,127,10,WHITE);

    display.setCursor(0,18);
    display.print("Soil : ");
    display.print(soilPercent);
    display.println("%");

    display.setCursor(0,30);
    display.print("Rain : ");
    display.println(rainStatus);

    display.setCursor(0,44);

    if(soilPercent < 40)
    {
      if(rainPercent < 20)
        display.println("Water Plant");
      else
        display.println("Wait For Rain");
    }
    else
    {
      display.println("Garden Healthy");
    }
  }

  //---------------- Page Number ----------------//

  display.fillRect(92,56,36,8,BLACK);
  display.setCursor(92,56);
  display.print("Pg ");
  display.print(currentPage + 1);
  display.print("/3");

  display.display();

  //---------------- Serial ----------------//

  Serial.print("Soil : ");
  Serial.print(soilPercent);
  Serial.print("%   Rain : ");
  Serial.print(rainPercent);
  Serial.print("%   Page : ");
  Serial.println(currentPage + 1);

  delay(100);
}