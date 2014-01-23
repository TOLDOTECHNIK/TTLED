# TTLED

This is a LED library for Arduino. It provides everyday tasks like on/off, fade, blink, ...

## History
2014-01-15 Initial release

## Installation
Download the ZIP file and extract it's content. Put the TTLED folder in "ARDUINOAPP/hardware/libraries/".
In the Arduino IDE you can test the sample sketches under Samples->TTLED.

## Usage
### Create object TTLED(pin, activeHigh)

####Parameters
pin: the number of the pin which is attached to the LED

activeHigh: true, false. true: digital pin is attached to LED's anode. false: digital pin is attached to LED's cathode

####Returns
nothing

####Example
TTLED led = TTLED(5, true);

### on()
This method turns the attached LED on. All async modes will be stopped.

####Parameters
none

####Returns
nothing

####Example
led.on();

### off()
This method turns the attached LED off. All async modes will be stopped.

####Parameters
none

####Returns
nothing

####Example
led.off();

## getState()
This method returns the logical state of the LED. It will be LOW if LED is fully off. It will be HIGH if LED fully or partially on.

####Parameters
none

####Returns
HIGH/LOW

####Example
if(led.getState() == HIGH){
	//code if led is on
}
else{
	//code if led is fully off
}

## getValue()
This method returns the current brightness (0-255) of the LED.

####Parameters
none

####Returns
uint8_t 0 - 255 (0=off, 255 = full brightness)

####Example
int brightness = led.getValue();

### toggle()
Turns the LED on if it's off. Turns the LED off if it's on.

####Parameters
none

####Returns
nothing

####Example
led.toggle();


### stopAsync()
Stops the LED's async mode. Async mode gets started by calling blinkAsync() or fadeAsync().

####Parameters
none

####Returns
nothing

####Example
led.stopAsync();

### blinkAsync(unsigned int blinkInterval)
Starts the blinking mode. Ensure to call the update() method continuously. If you don't call it, the LED will not blink.

####Parameters
blinkInterval: LED is on for blinkInterval ms and off for blinkInterval ms

####Returns
nothing

####Example
led.blinkAsync(1000);
void loop(){
	led.update();
}

### blink(unsigned int blinkInterval, uint8_t times)
Blinks the LED n times. Blinking is not done asynchronously. This means, your sketch will stop until blinking is done.

####Parameters
blinkInterval: LED is on for blinkInterval ms and off for blinkInterval ms
times: Blinking gets repeated n times.

####Returns
nothing

####Example
led.blink(1000, 5);

### fadeAsync(unsigned int time)
Starts fading the LED. Fadin is based on an internal ease in/out algorithm. Ensure to call the update() method continuously. If you don't call it, the LED will not fade.

####Parameters
time: Time in ms for one full fade period (in and out)

####Returns
nothing

####Example
led.fadeAsync(1000);
void loop(){
	led.update();
}

### fadeIn(unsigned int fadeTime)
Fades the LED in (from current brightness to max brightness).

####Parameters
fadeTime: Time in ms for fading in

####Returns
nothing

####Example
led.fadeIn(1000);

### fadeOut(unsigned int fadeTime)
Fades the LED out (from current brightness to dark).

####Parameters
fadeTime: Time in ms for fading out

####Returns
nothing

####Example
led.fadeOut(1000);

### setValue(uint8_t value)
Sets the LED's PWM value. It is the same as analogWrite();

####Parameters
value: 0 - 255 (0=off, 255 = full brightness)

####Returns
nothing

####Example
led.setValue(150);

### setMaxValue(uint8_t value)
Sets the allowed maximum brightness of the LED. For example the method on() will take this maximum brightness value.

####Parameters
value: 0 - 255 (0=off, 255 = full brightness)

####Returns
nothing

####Example
led.setMaxValue(200);



