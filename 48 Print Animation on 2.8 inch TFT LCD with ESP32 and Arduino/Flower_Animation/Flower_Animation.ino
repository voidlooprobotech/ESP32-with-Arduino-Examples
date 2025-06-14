
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include "animation.h"

TFT_eSPI tft = TFT_eSPI();

void setup() {
  // put your setup code here, to run once:
tft.init();
  tft.setRotation(1);
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_WHITE);
  
}

void loop() {
  // put your main code here, to run repeatedly:
for(int i=0;i<frames;i++)

{
  delay(250);
  tft.pushImage(0, 0, animation_width  , animation_height, animation[i]);
  }
delay(250);
}
