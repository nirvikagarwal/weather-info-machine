#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>

#define dataPin 4
#define DHTTYPE DHT11
DHT dht(dataPin, DHTTYPE);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET 5
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LOGO_HEIGHT 64
#define LOGO_WIDTH 128

void setup()
{
    Serial.begin(9600);
    dht.begin();

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    { // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }
    delay(1000);
}

void loop()
{
    float h = dht.readHumidity();                  // read humidity
    float t = dht.readTemperature();               // read temperature
    float hic = dht.computeHeatIndex(t, h, false); // compute head index for temp in °C

    // Printing the results on the serial monitor
    Serial.print("Temperature = ");
    Serial.print(t);
    Serial.print(" *C ");
    Serial.print("    Humidity = ");
    Serial.print(h);
    Serial.println(" % ");

    display.clearDisplay();
    display.setTextSize(1); // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setFont(&FreeSansBold9pt7b);
    display.setCursor(0, 13);
    display.print(F("Temp: "));
    display.setFont(&FreeSans9pt7b);
    display.drawCircle(105, 2, 2, WHITE);
    display.print(t);
    display.println(F(" C"));
    display.setFont(&FreeSansBold9pt7b);
    display.print(F("Humid: "));
    display.setFont(&FreeSans9pt7b);
    display.print(h);
    display.println(F("%"));
    display.setFont(&FreeSansBold9pt7b);
    display.print(F("Feels: "));
    display.setFont(&FreeSans9pt7b);
    display.print(hic);
    display.println(F(" C"));
    display.drawCircle(103, 45, 2, WHITE);
    display.display();

    delay(2000); // Delays 2 secods, as the DHT22 sampling rate is 0.5Hz
}