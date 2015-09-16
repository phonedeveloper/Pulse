# Pulse
Pulses an Arduino digital pin at a set rate and duty cycle.

**Pulse** uses the Actions library to generate a pulse on a digital output pin.

You can use this to blink an LED without using **delay()**, timers or interrupts.

Since **Pulse** depends on being called frequently in your sketch's **loop()**, it's a great way to see if your loop is hung up on a long-running process.

Requires the **Actions** library at https://github.com/phonedeveloper/Actions

Examples **BlinkBeep** and **AlarmSound** are provided.

## Benefits
 * Is very easy to use
 * Does not block - lots of time to do other things between pulses
 * Is great for providing an indicator that something is not hogging your sketch's loop()
 * Is good for audio or visual alerts, or periodic events where precise timing is not important
 * Does not use interrupts, timers, or device-specific features
 * Up to one minute between pulses

## Be aware
 * It is not for precision timing
 * It is not small by itself, but if you are already using the **Actions** library elsewhere in your sketch, the incremental increase is quite small
 * Is only as accurate as how often Pulse::loop() is called
 * The actual frequency will always be lower
 * Can become erratic if long-running functions prevent **Pulse::loop()** from being run on time. However, this can be addressed by calling **Pulse::loop()** from within those functions.

# Installation
From the command line, go to your **sketchbook** folder. Inside is a folder named **libraries** (if not, create it). **cd** to the **sketchbook\libraries** folder, and if there is no other library named **Pulse** in that folder, run the following command:

`$ git clone https://github.com/phonedeveloper/Pulse.git`

This will install the Pulse library and some examples. Restart the Arduino development environment to see them.

You will also need to install the Actions library. See https://github.com/phonedeveloper/Actions/README.md for instructions.

# Example Sketches
The following examples are provided (in the library's **examples** folder, and accessible via the Arduino IDE's ***File | Examples*** menu:

* **BlinkBeep**: Simulatneously flashes the pin 13 LED and turns on/off a buzzer on pin 3 at different rates and duty cycles.
* **AlarmSound**: Makes an alarm sound (four quick beeps followed by silence, repeating) using Pulse for the rapid alarm sounds, and Actions to repeatedly enable and disable those sounds every 1/2 second.

# Simple Examples

To use **Pulse** with all of its defaults (blink the pin 13 LED at 1 hz and 50% duty cycle):

```
#import <Actions.h>
#import <Pulse.h>
Pulse blink;

...

void loop() {
  blink.loop();
}
```
To set a different delay, add a delay parameter. This example sets the delay to 500 ms, which is 250 ms on and 250 ms off:

```
#import <Actions.h>
#import <Pulse.h>
Pulse blink(500);

...

void loop() {
  blink.loop();
}
```
To toggle a different pin, specify the delay followed by the pin number in the constructor. This example toggles pin 3:

```
#import <Actions.h>
#import <Pulse.h>
Pulse blink(500, 3);

...

void loop() {
  blink.loop();
}
```

You can change the duty cycle if you specify the delay and pin number parameters and follow them with the duty cycle parameter (from 1 to 99 percent). This example sets the duty cycle to 10% (50 ms on, 450 ms off)
on pin 13.

```
#import <Actions.h>
#import <Pulse.h>
Pulse blink(500, 13, 10);

...

void loop() {
  blink.loop();
}
```
# API
The examples below assume that an instance of **Pulse** named ```blink``` is created during construction.

### Includes:
```
#include <Actions.h>
#include <Pulse.h>
```

### Constuctor examples:
```
// Pulse::Pulse(delay=500, pin=13, dutyCycle=50)
Pulse blink;              // defaults (above)
Pulse blink(1000);        // 1 second pulse cycle
Pulse blink(1000, 3);     // use pin 3
Pulse blink(1000, 3, 25); // use 25% duty cycle

```
where

* ```delay``` is the time for a complete pin cycle *(range: 1-60000, units: milliseconds)*
* ```pin``` is the desired digital output pin
* ```dutyCycle``` is the duty cycle for the **HIGH** state *(range: 1 to 99, units: percent)*

The constructor automatically calls **start()** (see below).

### Loop:

```
void loop() {    // the sketch's loop() method
  blink.loop();
}
```

This function needs to be called from within the sketch's loop and from within any loops in long-running functions. It checks to see if it is time to change the pin's state and changes it when it is time.

### Starting and stopping:
```
bool result = blink.start();
```
Starts the pulsing function. If it is stopped when called, **true** is returned.  **false** is returned if it is already running or it is stopping.

**start()** is automatically called during construction.

```
int finalState = HIGH;
bool result = blink.stop(finalState);
```
Stops the pulsing function at the next pin state change, setting the pin output to **finalState**. Returns **true** if called while the pulsing function was running, and **false** if it was not running or was already stopping. This function will usually return before the last pulse finishes, because it simply sets a flag telling the pulsing function that a stop is desired.
 
# Caveats

This is NOT for precision timing.

**Pulse** works by using the **Actions** library to set the time after which it will be called back to change the pin's state. **Pulse::loop()** is where the pin state change occurs after enough time has passed.

The error will accumulate because **Pulse** does not attempt to shorten a future delay if **Pulse::loop()** is called late.

For example, if something in the sketch's **loop()** always takes 100 ms to complete, then the pin state will change ***up to 100 ms after*** the state should be changed (assuming **Pulse::loop()** is also called in the sketch's **loop()**. The amount of "lateness" may appear consistent, appear to change slowly or in a pattern, or appear random, depending on how well the pulse rate and the long running task timing correlate.

# License
The MIT license. See LICENSE.
# Author
Sean Sheedy, PhoneDeveloper LLC