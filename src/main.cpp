// Author: Jessmer Palanca , Ariel Villasenor, Lu Yu
// Net ID: jjpalanca, arielv, lyu18    
// Date: 11/21/19     
// Assignment: Lab 5
//----------------------------------------------------------------------//
#include <Arduino.h>
#include <avr/io.h>
#include "i2c.h"
#include "timer.h"
#define DELAY 1000

typedef enum coordinates {x0 = 0x32, x1 = 0x33, y0=0x34, y1=0x35, z0=0x36, z1=0x37};

int main(){
  int Address = 0x53; // This is the slave address
  int x=0;
  int y=0;
  int z=0;

  Serial.begin(9600);
  Serial.flush();
  sei();
  initTimer1();
  initI2C();

  beginTransmission(Address);
  write(0x2D);
  write(0x00);
  endTransmission();

  beginTransmission(Address);
  write(0x2D);
  write(0x08);
  endTransmission();

	Serial.flush();

    while(1){

      beginTransmission(Address);
      requestFrom(x1, Address);
      x = (read() << 8);
      endTransmission();
      
      beginTransmission(Address);
      requestFrom(x0, Address);
      x |= read();
      endTransmission();
      
      beginTransmission(Address);
      requestFrom(y1, Address);
      y = (read() << 8);
      endTransmission();
      
      beginTransmission(Address);
      requestFrom(y0, Address);
      y |= read();
      endTransmission();

      beginTransmission(Address);
      requestFrom(z1, Address);
      z = (read() << 8);
      endTransmission();
      
      beginTransmission(Address);
      requestFrom(z0, Address);
      z |= read();
      endTransmission();

      Serial.print("X = ");
      Serial.print(x);
      Serial.print("\t");

      Serial.print("Y = ");
      Serial.print(y);
      Serial.print("\t");

      Serial.print("Z = ");
      Serial.println(z);
      delayMs(1000);

    }
    return 0;
}

