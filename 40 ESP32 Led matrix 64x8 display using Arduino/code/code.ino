

#include <MD_Parola.h>
#include <MD_MAX72xx.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CKL_PIN     18
#define DATA_PIN    23
#define CS_PIN      21

// create an instance of the MD_Parola class
MD_Parola ledMatrix = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup() {
  ledMatrix.begin();         // initialize the LED Matrix
  ledMatrix.setIntensity(1); // set the brightness of the LED matrix display (from 0 to 15)
  ledMatrix.displayClear();  // clear LED matrix display
}

void loop() {
  if (ledMatrix.displayAnimate()) {

    ledMatrix.displayText("Welcome  to void looprobotech and automation", PA_CENTER, 75, 75, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
    ledMatrix.displayReset();
  }

}
