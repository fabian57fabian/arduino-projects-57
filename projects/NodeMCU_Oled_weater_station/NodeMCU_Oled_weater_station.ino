/**The MIT License (MIT)
  Copyright (c) 2017 by Daniel Eichhorn
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
  See more at https://blog.squix.org
*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <JsonListener.h>
#include "WundergroundForecast.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET LED_BUILTIN //

/**
   Wunderground Settings
*/
const String  WUNDERGRROUND_API_KEY = "___key___";
const String  WUNDERGR_UND_STATE_OR_COUNTRY = "Italy";
const String  WUNDERGR_UND_CITY = "Florence";
const String  WUNDERGRROUND_LANGUAGE = "IT";
const boolean IS_METRIC = true;
const boolean IS_24HOURS = false;

// initiate the WundergoundClient
WundergroundForecast wunderground(IS_METRIC);


/**
   WiFi Settings
*/
const char* ESP_HOST_NAME = "esp-" + ESP.getFlashChipId();
const char* WIFI_SSID     = "___ssid___";
const char* WIFI_PASSWORD = "___password___";

// initiate the WifiClient
WiFiClient wifiClient;

/**
   Helping funtions
*/
void connectWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.println(WiFi.localIP());
  Serial.println();
}
WGForecast forecs;
WGForecast forecsNight;
/**
   SETUP
*/
void setup() {
  Serial.begin(115200);
  delay(1);
}

void printData(int minutesDisplay) {
  Adafruit_SSD1306 display(OLED_RESET);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(10);
  display.clearDisplay();
  display.display();
  //draw rectangle
  for (int16_t i = 0; i < display.height() / 2 - 2; i += 2) {
    display.drawRoundRect(i, i, display.width() - 2 * i, display.height() - 2 * i, display.height() / 4, WHITE);
    display.display();
    delay(1);
  }

  display.clearDisplay();
  display.display();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  String day = forecs.forecastTitle;
  if (day != "") {
    day = forecs.forecastTitle;
  } else {
    day = forecsNight.forecastTitle;
  }
  display.println(day + " " + forecsNight.forecastDay + ":");//Martedì 20:
  display.setCursor(0, 20);
  display.setTextSize(1);
  display.println("Minime di " + forecs.forecastLowTemp + " C");
  display.setCursor(0, 30);
  display.println("Massime di " + forecs.forecastHighTemp + " C");
  display.setCursor(0, 40);
  display.println("Giorno: " + forecs.forecastIcon);
  display.setCursor(0, 50);
  display.println("Sera: " + forecsNight.forecastIcon);
  display.display();
  delay(minutesDisplay * 60 * 1000);
  display.clearDisplay();
  display.display();
}

void downloadData() {
  Serial.println("wifi");
  connectWifi();
  Serial.println("end wifi");
  Serial.println();
  Serial.println("\n\nNext Loop-Step: " + String(millis()) + ":");
  uint8_t maxForecasts = 10;
  WGForecast forecasts[maxForecasts];
  wunderground.updateForecast(forecasts, maxForecasts, WUNDERGRROUND_API_KEY, WUNDERGRROUND_LANGUAGE, WUNDERGR_UND_STATE_OR_COUNTRY, WUNDERGR_UND_CITY);
  forecs = forecasts[0];
  forecsNight = forecasts[1];
}

/**
   LOOP
*/
void loop() {
  downloadData();
  printData(10);
  delay(24 * 60 * 60 * 1000); //sleep for 24 hours
}