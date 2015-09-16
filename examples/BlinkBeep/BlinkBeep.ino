/*
 * BlinkBeep - blinks pin 13 and cycles a buzzer on pin 3 independently 
 * 
 * BlinkBeep is a demo of the Pulse library which lets you
 * pulse a digital pin at a specified rate and duty cycle.
 * 
 * Note: this sketch enables/disables a buzzer, like a piezo
 * buzzer that contains its own oscillator circuitry. It does
 * not provide an oscillating output.
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
#include <Pulse.h>

static const int LED_PIN = 13;
static const int BUZZER_PIN = 3;

// For LED, use defaults of 1 sec, pin 13, 50% duty cycle
Pulse led;

// For buzzer, use 250 ms between pulses, on pin 13, 10% duty cycle
Pulse buzzer(200, 3, 10);

void setup() {
}

void loop() {
  led.loop();
  buzzer.loop();
}
