/*
 * AlarmSound - makes a sound like some alarm clocks
 * 
 * Uses Actions and Pulse libraries to make an alarm clock sound.
 * The output on pin 3 drives a piezo buzzer. (The piezo buzzer
 * must already provide the oscillator circuit; the sketch only
 * provides an on/off signal on pin 3.)
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

static const int BUZZER_PIN = 3;

// For buzzer, use 250 ms between pulses, on pin 13, 10% duty cycle
Pulse buzzer(150, 3, 50);
Actions alarm(1);

void setup() {
  alarmState();
}

void loop() {
  buzzer.loop();
  alarm.loop();
}

void alarmState() {
  static boolean state = false;
  state = !state;
  if (state) buzzer.start();    
  else buzzer.stop(LOW);
  alarm.runLater(alarmState, 500);
}

