#include <WiFi.h>
#include "time.h"
#include <TM1637Display.h>

#define CLK 5
#define DIO 4

TM1637Display display(CLK, DIO);

const char *ssid = "wifi_tech";
const char *password = "tech@12345";

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 19800; // IST (GMT+5:30)
const int daylightOffset_sec = 0;

void setup() {
  Serial.begin(115200);
  display.setBrightness(0x0f);

  // Connect to Wi-Fi
  connectWiFi();

  // Initialize NTP
  Serial.print("Initializing NTP..");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.print("Local Time Printing..");
  printLocalTime();
}

void connectWiFi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    for (int i = 0; i < 4; i++) 
    {
      display.showNumberDec(0, false, 1, i);
      delay(150);
      display.clear();
    }
  }
  Serial.println("\nWiFi connected.");
  display.showNumberDec(0, true);
}

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  Serial.print("Hour (12 hour format): ");
  Serial.println(&timeinfo, "%I");
  Serial.print("AM/PM: ");
  Serial.println(timeinfo.tm_hour >= 12 ? "PM" : "AM");
  Serial.println();
}

void blinkColon(int hour, int minute, bool showColon) {
  // Display hour with colon (if showColon is true) and leading zeros
  display.showNumberDecEx(hour, showColon ? 0b01000000 : 0, true, 2, 0);
  // Display minute with leading zeros
  display.showNumberDecEx(minute, 0, true, 2, 2);
}

void loop() {
  // Check Wi-Fi connection
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected. Reconnecting...");
    connectWiFi();
  }

  static int lastHour = 12, lastMinute = 0; // Default to 12:00
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) 
  {
    Serial.println("Failed to obtain time");
    display.showNumberDec(8888, false);
    delay(100);
  }

  // Update time
  //int hour = timeinfo.tm_hour;  // 24 hour
  int hour = timeinfo.tm_hour % 12 == 0 ? 12 : timeinfo.tm_hour % 12;  // 12 hour 
  int minute = timeinfo.tm_min;
  lastHour = hour;
  lastMinute = minute;

  // Blink colon
  static bool colonState = false;
  blinkColon(hour, minute, colonState);
  colonState = !colonState;
  delay(500);
}