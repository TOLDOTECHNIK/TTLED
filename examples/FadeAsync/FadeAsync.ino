#include <TTLED.h>

#define LED_PIN		5


//true: digital pin is attached to LED's anode
//false: digital pin is attached to LED's cathode
TTLED led = TTLED(LED_PIN, true);    //create LED object

void setup(){
  led.init();
  led.fadeAsync(1000);               //1000: time for one period (full fade in and full fade out)
}

void loop(){
  led.update();                      //do LED calculations and brightness update (necessary in async mode)
  if(millis() > 10000){              //stop async after 10s since last reset
    led.stopAsync();
  }
  delay(20);
}


