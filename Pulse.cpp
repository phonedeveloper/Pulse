/*
 * Pulse - pulses a digital output pin's state
 *
 * Pulse uses the Actions library to generate a pulse on a digital output pin.
 *
 * Pulse:
 *  + Is very easy to use
 *  + Does not block - lots of time to do other things between pulses
 *  + Is great for providing an indicator that something is not hogging
 *    your sketch's loop()
 *  + Is good for audio or visual alerts, or periodic events where
 *    precise timing is not important
 *  + Does not use interrupts, timers, or device-specific features
 *  + Up to one minute between pulses
 * But:
 *  - Is not for precision timing
 *  - Not small by itself, but if you are already using Actions
 *    elsewhere, the incremental increase is quite small
 *  - Is only as accurate as how often Pulse::loop() is called
 *  - The actual frequency will always be lower
 *  - Can become erratic if long-running functions prevent
 *    Pulse::loop() from being run on time (but this can be addressed
 *    by calling Pulse::loop() from within those functions.)
 *
 * To use Pulse in a sketch to, say, blink the pin 13 LED at the default
 * rate of 1 hz (1000 ms delay) and 50% duty cycle (500 ms on/500 ms off):
 *
 * #import <Actions.h>
 * #import <Pulse.h>
 * Pulse blink;
 * void loop() {
 *   blink.loop();
 * }
 *
 * To set a different delay, add a delay parameter. This example sets the delay to
 * 500 ms, which is 250 ms on and 250 ms off:
 *
 * #import <Actions.h>
 * #import <Pulse.h>
 * Pulse blink(500);
 * void loop() {
 *   blink.loop();
 * }
 *
 * To toggle a different pin, specify a delay and then the pin number in the
 * constructor:
 *
 * To set a different delay, add a delay parameter. This example sets the delay to
 * 500 ms, which is 250 ms on and 250 ms off:
 *
 * #import <Actions.h>
 * #import <Pulse.h>
 * Pulse blink(500, 3);
 * void loop() {
 *   blink.loop();
 * }
 *
 * You can change the duty cycle if you specify the delay and pin number
 * parameters and follow them with the duty cycle parameter (from 1 to 99
 * percent). This example sets the duty cycle to 10% (50 ms on, 450 ms off)
 * on pin 13.
 *
 * #import <Actions.h>
 * #import <Pulse.h>
 * Pulse blink(500, 13, 10);
 * void loop() {
 *   blink.loop();
 * }
 *
 * CAVEATS:
 *
 * This is NOT for accurate timing.
 *
 * Pulse works by using the Actions library to set the time after which it
 * will be called back to change the pin's state.
 *
 * It does not attempt to shorten a future delay if Pulse::loop() is
 * called late, so error accumulates.
 *
 * For example, if something in loop() always takes 100 ms to complete,
 * then the pin state will remain on or off between 0 and 100ms longer
 * than specified. This "lateness" may appear consistent, appear to drift,
 * or appear random, depending on how well the pulse rate and the long
 * running task timing correlate.
 *
 * Author: PhoneDeveloper, LLC
 * Date: 09/16/2015
 *
 * Copyright (c) 2015, PhoneDeveloper, LLC
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <Actions.h>
#include "Pulse.h"

Pulse::Pulse(unsigned int delay, int pin, unsigned int dutyCycle)
    : pin(pin)
{
    pulse = Actions(1);
    // set duty cycle to 50% if invalid input given
    if(dutyCycle < 1 || dutyCycle > 99)
        dutyCycle = 50;
    // calculate pin on and off times in micros
    unsigned long delayMicros = (unsigned long)delay;
    onTime = (unsigned long)(dutyCycle) * (unsigned long)(delay)*10ul;
    offTime = (100ul - (unsigned long)(dutyCycle)) * (unsigned long)(delay)*10ul;
    pinState = LOW;
    pinMode(pin, OUTPUT);
    start();
}


void Pulse::loop()
{
    pulse.loop();
}


bool Pulse::start()
{
    if(state == STATE_STOPPED)
    {
        state = STATE_RUNNING;
        blink();
        return true;
    }
    else
        return false;
}


bool Pulse::stop(int stopState)
{
    if(state == STATE_RUNNING)
    {
        if(stopState)
        {
            state = STATE_STOP_HIGH;
        }
        else
            state = STATE_STOP_LOW;
        return true;
    }
    else
        return false;
}


void Pulse::blink()
{
    pinState = !pinState;
    digitalWrite(pin, pinState);
    if(state == STATE_RUNNING)
    {
        if(pinState)
        {
            pulse.runLater((MethodInstance) this, (MethodCallback)&Pulse::blink, onTime, true);
        }
        else
        {
            pulse.runLater((MethodInstance) this, (MethodCallback)&Pulse::blink, offTime, true);
        }
    }
    else if(state == STATE_STOP_HIGH)
    {
        digitalWrite(pin, HIGH);
        pinState = !LOW;
        state = STATE_STOPPED;
    }
    else if(state == STATE_STOP_LOW)
    {
        digitalWrite(pin, LOW);
        pinState = LOW;
        state = STATE_STOPPED;
    }
}