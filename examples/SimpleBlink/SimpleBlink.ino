#include <TTLED.h>

#define LED_PIN		13

TTLED led = TTLED(LED_PIN, true);

void setup(){
   Serial.begin(9600);
   led.init();
}

void loop(){
  led.on();
  Serial.println(led.getState());
  delay(500);
  led.off();
  Serial.println(led.getState());
  delay(500);
}


