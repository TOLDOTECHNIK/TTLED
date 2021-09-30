#include <TTLED.h>

#define LED_PIN		13

TTLED led = TTLED(LED_PIN, true);

void setup(){
  led.init();
  led.blinkAsync(1000);    //on time = 1000 and off time = 1000
  Serial.begin(9600);
}

void loop(){
  led.update();
  Serial.println(led.getState());
  delay(500);
}



