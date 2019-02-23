/*
* TTLED
* Version 1.1 November, 2015
* Version 1.2 December, 2018
* Version 1.3 February, 2019
* Copyright 2009 TOLDO TECHNIK
* For details, see https://github.com/TOLDOTECHNIK/TTLED
*/

#include "TTLED.h"

TTLED::TTLED(uint8_t pin, uint8_t activeHigh){
  _pin=pin;
  _activeHigh = activeHigh;
  pinMode(_pin, OUTPUT);
  fadeOut(0, true);
  _fadeDirection = HIGH;
  _maxValue = 255;
}

void TTLED::update(){
  if(_fadeTime > 0){
    _logicalState = HIGH;
    if(millis() - lastToggleTime > _fadeTime){
      lastToggleTime = millis();
      if(_fadeDirection == LOW){
        _fadeDirection = HIGH;
      }
      else{
        _fadeDirection = LOW;
      }
    }
    _currentValue = easeInOutSine(_fadeDirection == HIGH ? millis() - lastToggleTime : _fadeTime - (millis() - lastToggleTime), _fadeDirection == HIGH ? 1 : 255, _fadeDirection == HIGH ? 255 : 1, _fadeTime);
    setValue(_currentValue);
  }
  else if(_onInterval > 0){
    _logicalState = HIGH;
	if(_offInterval > 0 && _currentValue == 0 && millis() - lastToggleTime > _offInterval){	//turn on if offInterval is set and conditions are true
	  lastToggleTime = millis();
	  fadeIn(0, false);
	}
    else if(millis() - lastToggleTime > _onInterval && (_currentValue > 0 || _offInterval == 0)){
      lastToggleTime = millis();
      if(_currentValue > 0){
        fadeOut(0, false);
      }
      else{
        fadeIn(0, false);
      } 
    }
  }
}

uint8_t TTLED::getState(){
  return _logicalState; 
}

uint8_t TTLED::getValue(){
  return _currentValue; 
}

void TTLED::toggle(void){
  if(_currentValue > 0){
    fadeOut(0, true);
  }
  else{
    fadeIn(0, true);
  }
}

void TTLED::blinkAsync(unsigned int blinkInterval){
  if(_fadeTime > 0){
    stopAsync(); 
  }
  _offInterval = 0;
  _onInterval = blinkInterval;
}

void TTLED::blinkAsync(unsigned int onInterval, unsigned int offInterval){
  if(_fadeTime > 0){
    stopAsync(); 
  }
  _onInterval = onInterval;
  _offInterval = offInterval;
}

void TTLED::blink(unsigned int blinkInterval, uint8_t times){
  for (byte i=0; i<times; i++){
    fadeIn(0, true);
    delay(blinkInterval / 2);
    fadeOut(0, true);
    delay(blinkInterval / 2);
  }
  _logicalState = LOW;
}

void TTLED::setValue(uint8_t value){
  _currentValue = value;
  value = _maxValue / 255.0 * value;
  if(value == 0 && _currentValue > 0){    //prevent led from turning off when fading 
    value = 1;
  }
  if(_activeHigh){
    #if defined(ARDUINO_ARCH_ESP32)
      digitalWrite(_pin, value > 0 ? HIGH : LOW);
    #else
      if(_currentValue == 0 && _logicalState == HIGH){  //prevent led from flickering when fading in again
        analogWrite(_pin, 1);
        delay(5);
      }
      analogWrite(_pin, value);
    #endif
  }
  else{
    #if defined(ARDUINO_ARCH_ESP32)
      digitalWrite(_pin, value > 0 ? LOW : HIGH);
    #else
      if(_currentValue == 0 && _logicalState == HIGH){  //prevent led from flickering when fading in again
        analogWrite(_pin, 254);
        delay(5);
      }
      analogWrite(_pin, 255 - value);
    #endif
  }
  
  if(_currentValue > 0){
    _logicalState = HIGH;
  }
  else{
    _logicalState = LOW;
  }
}

void TTLED::setMaxValue(uint8_t value){
  _maxValue = value;
  setValue(_currentValue);
}

void TTLED::on(){
  fadeIn(0, true); 
}

void TTLED::fadeIn(unsigned int fadeTime){
  fadeIn(fadeTime, true); 
}

void TTLED::fadeIn(unsigned int fadeTime, uint8_t stopAsync){
  if(stopAsync){
    this->stopAsync();
  }
  if(fadeTime > 0 && _logicalState == LOW){
    //take current value as start point and recalc remaining fade time
    //fadeTime = fadeTime / 255.0 * (255 - _currentValue);
    uint8_t startValue = _currentValue;
    for (unsigned int cycle = 0; cycle <= fadeTime / PAUSE_MS; cycle++){
      _currentValue = easeInOutSine(cycle * PAUSE_MS, startValue, 255, fadeTime);
      setValue(_currentValue); 
      delay(PAUSE_MS); 
    }
  }
  
  _currentValue = 255;
  setValue(_currentValue);
}

void TTLED::off(){
  fadeOut(0, true); 
}

void TTLED::fadeOut(unsigned int fadeTime){
  fadeOut(fadeTime, true); 
}

void TTLED::fadeOut(unsigned int fadeTime, uint8_t stopAsync){
  if(stopAsync){
    this->stopAsync();
  }
  if(fadeTime > 0 && _logicalState == HIGH){
    //take current value as start point and recalc remaining fade time
    //fadeTime = fadeTime / 255.0 * _currentValue;
    uint8_t startValue = _currentValue;
    for (unsigned int cycle = fadeTime / PAUSE_MS; cycle > 0; cycle--){
      _currentValue = easeInOutSine(cycle * PAUSE_MS, startValue, 0x00, fadeTime);
      setValue(_currentValue); 
      delay(PAUSE_MS); 
    }
  }
  _currentValue = 0;
  setValue(_currentValue);
}

void TTLED::fadeAsync(unsigned int time){
  if(_onInterval > 0){
    stopAsync(); 
  }
  _fadeTime = time / 2; 
}

uint8_t TTLED::easeInOutSine(unsigned int currentTime, uint8_t startValue, uint8_t endValue, unsigned int duration) {
  static uint8_t temp;
  if(endValue < startValue){
    temp = endValue;
    endValue = startValue;
    startValue = temp; 
  }
  endValue -= startValue;
  return -endValue * cos((float)currentTime / duration * (PI / 2.0)) + endValue + startValue;
}

void TTLED::stopAsync(){
  _fadeTime = 0;
  _onInterval = 0;
  _offInterval = 0;
}




