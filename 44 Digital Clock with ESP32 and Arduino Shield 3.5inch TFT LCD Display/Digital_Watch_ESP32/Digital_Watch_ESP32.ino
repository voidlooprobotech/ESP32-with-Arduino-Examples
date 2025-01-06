// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include "RTClib.h"
#include <UTFTGLUE.h>              //use GLUE class and constructor

UTFTGLUE myGLCD(0,13,12,33,32,15); //all dummy args
RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
uint8_t Second = 61, Minutes = 61, Hours = 25, Date, Months = 13, Week = 10;
float Temperature;
uint16_t Years;

void printDigiTime(uint16_t x, uint16_t y);
void printColon(uint16_t x, uint16_t y );

void setup () 
{
  Serial.begin(115200);

  #ifndef ESP8266
    while (!Serial); // wait for serial port to connect. Needed for native USB
  #endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

    // Setup the LCD
    myGLCD.InitLCD();
    myGLCD.setFont(BigFont);

    // Clear the screen and draw the frame
    myGLCD.clrScr();

    myGLCD.setColor(255, 0, 0);   // top label color
    myGLCD.fillRect(0, 0, 479, 20); // top label 

    myGLCD.setColor(255, 255, 255); // text color
    myGLCD.setBackColor(255, 0, 0);  // text background color
    myGLCD.print("* voidlooprobotech *", CENTER, 1);

    myGLCD.setFont(SmallFont);

    myGLCD.setColor(255, 255, 0);     // bottom label color
    myGLCD.fillRect(0, 20, 479, 40); // bottol leabel

    myGLCD.setColor(0, 0, 0);  // text  color
    myGLCD.setBackColor(255, 255, 0);  // text background color
    myGLCD.print("<www.youtube.com/voidloopRobotechAutomation>", CENTER, 23);

    myGLCD.setFont(BigFont);
    myGLCD.setColor(255, 255, 255);  // text  color
    myGLCD.setBackColor(0, 0, 0);  // text background color
    myGLCD.print("Subscribe this Channel", CENTER, 300);
  
    myGLCD.setColor(255, 255, 255);     // bottom label color
    myGLCD.fillRect(0, 40, 479, 290); // bottol leabel
    myGLCD.setBackColor(255, 255, 255);  // text background color

}

void loop () {

  printDigiTime(100, 100);
  delay(1000);
}

void printDigiTime(uint16_t x, uint16_t y)
{
  DateTime now = rtc.now();
  String strSecond;
  String strMinutes;
  String strHours;
  String strDate;
  String strMonths;
  String strYears;
  String strTemp;

if(Second != now.second())
{
  if(now.second() < 10)
  {
    strSecond = "0" + String(now.second());
  }
  else
  {
    strSecond = String(now.second());
  }
  
  myGLCD.setFont(SevenSegNumFont);
  myGLCD.setColor(0, 255, 0);  // text  color
  myGLCD.print(strSecond, (x+190), (y+20), 0); 
}

if( Minutes != now.minute())
{
  if(now.minute() < 10)
  {
    strMinutes = "0" + String(now.minute());
  }
  else
  {
    strMinutes = String(now.minute());
  }

  myGLCD.setFont(SevenSegNumFont);
  myGLCD.setColor(0, 255, 0);  // text  color
  myGLCD.print(strMinutes, (x+110), (y+20), 0);

}

if( Hours != now.hour())
{
  if(now.hour() < 10)
  {
    strHours = "0" + String(now.hour());
  }
  else
  {
    strHours = String(now.hour());
    
  }

  myGLCD.setFont(SevenSegNumFont);
  myGLCD.setColor(0, 255, 0);  // text  color
  myGLCD.print(strHours, (x+30), (y+20), 0);   // y == 50

}

if(Date != now.day())
{
  if(now.day() < 10)
  {
    strDate = "0" + String(now.day());
  }
  else
  {
    strDate = String(now.day());
  }

  myGLCD.setFont(SevenSegNumFont);
  myGLCD.setColor(0, 0, 255);  // text  color
  myGLCD.print(strDate, x, (y+70), 0);       
}
  

if(Months != now.month())
{
  if(now.month() < 10)
  {
    strMonths = "0" + String(now.month());
  }
  else
  {
    strMonths = String(now.month());
  }

  myGLCD.setFont(SevenSegNumFont);
  myGLCD.setColor(0, 0, 255);  // text  color
  myGLCD.print(strMonths, (x+80), (y+70), 0);
}

if(Years != now.year())
{
  if(now.year() < 10)
  {
    strYears = "0" + String(now.year());
  }
  else
  {
    strYears = String(now.year());
  }

  myGLCD.setFont(SevenSegNumFont);
  myGLCD.setColor(0, 0, 255);  // text  color
  myGLCD.print(strYears, (x+160), (y+70), 0);
}

if(Temperature != rtc.getTemperature())
{
  if(rtc.getTemperature() < 10)
  {
    strTemp = "0" + String(rtc.getTemperature()) + "'C";
  }
  else
  {
    strTemp = String(rtc.getTemperature()) + "'C";
  }

  myGLCD.setFont(BigFont);
  myGLCD.setColor(255, 0, 0);  // text  color
  myGLCD.print(strTemp, (x+95), (y+125), 0);

}

if(Week != now.dayOfTheWeek())
{
  myGLCD.setFont(BigFont);
  myGLCD.setColor(255, 0, 0);  // text  color
  myGLCD.print(daysOfTheWeek[now.dayOfTheWeek()], (x+90), y, 0);
}
  Second = now.second();
  Minutes = now.minute();
  Hours = now.hour();
  Date = now.day();
  Months = now.month();
  Years = now.year();
  Temperature = rtc.getTemperature();
  Week = now.dayOfTheWeek();
}

