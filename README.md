# TTLED

This is a LED library for Arduino. It provides everyday tasks like on/off, fade, blink, ...

## History
2014-01-15 Initial release

## Installation
Download the ZIP file and extract it's content. Put the TTLED folder in "ARDUINOAPP/hardware/libraries/".
In the Arduino IDE you can test the sample sketches unter Samples->TTLED.

## Usage
### Create TTLED object
####Syntax
TTLED ledObject = TTLED(pin, activeHigh);

####Parameters
pin: the number of the pin which is attached to the LED

activeHigh: true, false. true: digital pin is attached to LED's anode. false: digital pin is attached to LED's cathode

####Returns
nothing

####Example
TTLED led = TTLED(5, true);

### on()
This method turns the attached LED on. All async modes will be stopped.

####Syntax
ledObject.on();

####Parameters
none

####Returns
nothing

####Example
led.on();

### off()
This method turns the attached LED off. All async modes will be stopped.

####Syntax
ledObject.off();

####Parameters
none

####Returns
nothing

####Example
led.off();