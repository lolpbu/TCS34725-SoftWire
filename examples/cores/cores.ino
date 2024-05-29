/*!
 *  @file cores.ino
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

SoftwareWire sWire(52, 53);

Adafruit_TCS34725_SWwire tcs_real = Adafruit_TCS34725_SWwire(TCS34725_INTEGRATIONTIME_499MS, TCS34725_GAIN_4X);
Adafruit_TCS34725_SWwire tcs_soft = Adafruit_TCS34725_SWwire(TCS34725_INTEGRATIONTIME_499MS, TCS34725_GAIN_4X);

void setup(void) { 
  Serial.begin(9600);

  if (tcs_soft.begin(&sWire)) {
    Serial.println("Found sensor soft");
  } else {
    Serial.println("No TCS34725 found ... check your connections (soft)");
    while (1);
  }

  if (tcs_real.begin(&Wire)) {
    Serial.println("Found sensor real");
  } else {
    Serial.println("No TCS34725 found ... check your connections (real)");
    while (1);
  }

  // Now we're ready to get readings!
}

void loop(void) {
  uint16_t r1, g1, b1, c1;
  uint16_t r2, g2, b2, c2;

  tcs_real.getRawData(&r1, &g1, &b1, &c1);
  tcs_soft.getRawData(&r2, &g2, &b2, &c2);

  uint16_t t1  = (r1+g1+b1)/3;
  uint16_t tr1 = (g1+b1)/2;
  uint16_t tg1 = (r1+b1)/2;

  uint16_t t2  = (r2+g2+b2)/3;
  uint16_t tr2 = (g2+b2)/2;
  uint16_t tg2 = (r2+b2)/2;

  Serial.print("direita(real): ");
  if(r1 > tr1*1.07)
    Serial.print("vermelho");
  else if(g1 > tg1*1.07)
    Serial.print("verde");
  else {
    if(t1 >= 11500) //1050
      Serial.print("branco");
    else 
      Serial.print("preto");
  }

  Serial.print(" / ");

  Serial.print("esquerda(soft): ");
  if(r2 > tr2*1.07)
    Serial.print("vermelho");
  else if(g2 > tg2*1.07)
    Serial.print("verde");
  else {
    if(t2 >= 11500) //1050
      Serial.print("branco");
    else 
      Serial.print("preto");
  }

  Serial.println("");
}
