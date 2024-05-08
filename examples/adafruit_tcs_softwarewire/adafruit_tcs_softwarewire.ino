/*!
 *  @file adafruit_tcs_softwarewire.ino
 *
 *  Software License Agreement (BSD License)
 *
 *  Copyright (c) 2024, BeeKeepers
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *  1. Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holders nor the
 *  names of its contributors may be used to endorse or promote products
 *  derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
 *  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
 *  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 *  DAMAGE.
 */
#include <SoftwareWire.h>
#include <Wire.h>

#include <Adafruit_TCS34725_SWwire.h>

SoftwareWire sWire(8, 9);

Adafruit_TCS34725_SWwire tcs_soft = Adafruit_TCS34725_SWwire(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
Adafruit_TCS34725_SWwire tcs_real = Adafruit_TCS34725_SWwire(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

void setup(void) {
  Serial.begin(9600);

  if(tcs_soft.begin(&sWire, TCS34725_ADDRESS)) {
    Serial.println("Found sensor (soft)");
  } else {
    Serial.println("No TCS34725 found (soft)");
  }

  if(tcs_real.begin(&Wire, TCS34725_ADDRESS)) {
    Serial.println("Found sensor (real)");
  } else {
    Serial.println("No TCS34725 found (real)");
  }

  // Now we're ready to get readings!
}

void loop(void) {
  uint16_t r1, g1, b1, c1, colorTemp1, lux1;
  uint16_t r2, g2, b2, c2, colorTemp2, lux2;

  tcs_real.getRawData(&r1, &g1, &b1, &c1);
  tcs_soft.getRawData(&r2, &g2, &b2, &c2);

  Serial.print("REAL: ");
  Serial.print(r1, DEC); Serial.print("/");
  Serial.print(g1, DEC); Serial.print("/");
  Serial.print(b1, DEC); Serial.print("\t");

  Serial.print("SOFT: ");
  Serial.print(r2, DEC); Serial.print("/");
  Serial.print(g2, DEC); Serial.print("/");
  Serial.println(b2, DEC);
}