/*
* TTLED
* Version 1.1 November, 2015
* Copyright 2009 TOLDO TECHNIK
* For details, see https://github.com/TOLDOTECHNIK/TTLED
*/

#ifndef TTLED_H
#define TTLED_H

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <Wprogram.h>
#endif

#define PAUSE_MS 0x05

class TTLED{
  public:
    TTLED(uint8_t ledPin, uint8_t activeHigh);
    void update();
    void on();
    void fadeIn(unsigned int fadeTime);
    void off();
    void fadeOut(unsigned int fadeTime);
    void toggle();
    void blink(unsigned int blinkInterval, uint8_t times);
    void blinkAsync(unsigned int blinkInterval);
	void blinkAsync(unsigned int onInterval, unsigned int offInterval);
    void setValue(uint8_t value);
    void setMaxValue(uint8_t value);
    uint8_t getValue();
    void fadeAsync(unsigned int time);
    void stopAsync();
    uint8_t getState();
  private:
    void fadeIn(unsigned int fadeTime, uint8_t stopAsync);
    void fadeOut(unsigned int fadeTime, uint8_t stopAsync);
    uint8_t easeInOutSine(unsigned int currentTime, uint8_t startValue, uint8_t endValue, unsigned int duration);

    uint8_t _pin;
    uint8_t _currentValue;
    uint8_t _maxValue;
    uint8_t _activeHigh;
    uint8_t _fadeDirection;
    uint8_t _logicalState;
    
    unsigned int _fadeTime;
    unsigned int _onInterval;
	unsigned int _offInterval;
    unsigned long lastToggleTime;
};

#endif

