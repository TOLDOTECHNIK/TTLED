# TTLED

This is a LED library for Arduino. It provides everyday tasks like on/off, fade, blink, ...

This library is ESP32 compatible now. Be aware there's no LED fade capability.

## History
- 2014-01-15 Initial release
- 2016-05-14 Prevent LED from turning off when fading
- 2018-12-06 ESP32 analogWrite fix
- 2019-02-23 prevent led from flickering when fading in/out again
- 2021-09-30 fix compile errors

## Installation
Download the ZIP file and extract its content. Move the TTLED folder to "ARDUINOAPP/hardware/libraries/".
In the Arduino IDE you'll find the sample sketches under Samples->TTLED.

## Usage
### Create object TTLED(pin, activeHigh)

#### Parameters
pin: the number of the pin which is attached to the LED

activeHigh: true, false. true: digital pin is attached to LED's anode. false: digital pin is attached to LED's cathode

#### Returns
nothing

#### Example
```
TTLED led = TTLED(5, true);
```
### init()
This method must be called. It initialises the LED pin.

#### Parameters
none

#### Returns
nothing

#### Example
```cpp
led.init();
```

### on()
This method turns the attached LED on. All async modes will be stopped.

#### Parameters
none

#### Returns
nothing

#### Example
```cpp
led.on();
```

### off()
This method turns the attached LED off. All async modes will be stopped.

#### Parameters
none

#### Returns
nothing

#### Example
```cpp
led.off();
```

## getState()
This method returns the logical state of the LED. It will be LOW if LED is fully off. It will be HIGH if LED fully or partially on.

#### Parameters
none

#### Returns
HIGH/LOW

#### Example
```cpp
if(led.getState() == HIGH){
	//code if led is on
}
else{
	//code if led is fully off
}
```

## getValue()
This method returns the current brightness (0-255) of the LED.

#### Parameters
none

#### Returns
uint8_t 0 - 255 (0=off, 255 = full brightness)

#### Example
```cpp
int brightness = led.getValue();
```

### toggle()
Turns the LED on if it's off. Turns the LED off if it's on.

#### Parameters
none

#### Returns
nothing

#### Example
```cpp
led.toggle();
```

### stopAsync()
Stops the LED's async mode. Async mode gets started by calling blinkAsync() or fadeAsync().

#### Parameters
none

#### Returns
nothing

#### Example
```cpp
led.stopAsync();
```

### blinkAsync(unsigned int blinkInterval)
Starts the auto blinking mode. Ensure to call the update() method continuously. If you don't call it, the LED will not blink.

#### Parameters
blinkInterval: LED is on for blinkInterval ms and off for blinkInterval ms

#### Returns
nothing

#### Example
```cpp
led.blinkAsync(1000);
void loop(){
	led.update();
}
```

### blinkAsync(unsigned int onInterval, unsigned int offInterval)
Starts the auto blinking mode with different on/off times. Ensure to call the update() method continuously. If you don't call it, the LED will not blink.

#### Parameters
onInterval: LED is on for onInterval ms 
offInterval: LED is off for offInterval ms

#### Returns
nothing

#### Example
```cpp
led.blinkAsync(10, 990);    //LED blinks every second for 10ms
void loop(){
	led.update();
}
```

### blink(unsigned int blinkInterval, uint8_t times)
Blinks the LED n times. Blinking is not done asynchronously. This means, your sketch will stop until blinking is done.

#### Parameters
blinkInterval: LED is on for blinkInterval ms and off for blinkInterval ms
times: Blinking gets repeated n times.

#### Returns
nothing

#### Example
```cpp
led.blink(1000, 5);
```

### fadeAsync(unsigned int time)
Starts fading the LED. Fadin is based on an internal ease in/out algorithm. Ensure to call the update() method continuously. If you don't call it, the LED will not fade.

#### Parameters
time: Time in ms for one full fade period (in and out)

#### Returns
nothing

#### Example
```cpp
led.fadeAsync(1000);
void loop(){
	led.update();
}
```

### fadeIn(unsigned int fadeTime)
Fades the LED in (from current brightness to max brightness).

#### Parameters
fadeTime: Time in ms for fading in

#### Returns
nothing

#### Example
```cpp
led.fadeIn(1000);
```

### fadeOut(unsigned int fadeTime)
Fades the LED out (from current brightness to dark).

#### Parameters
fadeTime: Time in ms for fading out

#### Returns
nothing

#### Example
```cpp
led.fadeOut(1000);
```

### setValue(uint8_t value)
Sets the LED's PWM value. It is the same as analogWrite();

#### Parameters
value: 0 - 255 (0=off, 255 = full brightness)

#### Returns
nothing

#### Example
```cpp
led.setValue(150);
```

### setMaxValue(uint8_t value)
Sets the allowed maximum brightness of the LED. For example the method on() will take this maximum brightness value. If max value is set to 0, the LED is off, but it is working like brightness was set to 255. This means, you can still get virtually the on/off state. 

#### Parameters
value: 0 - 255 (0=off, 255 = full brightness)

#### Returns
nothing

#### Example
```cpp
led.setMaxValue(200);
```