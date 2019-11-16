// Author: Jessmer Palanca , Ariel Villasenor, Lu Yu
// Net ID: jjpalanca, arielv, lyu18     
// Date: 11/03/19     
// Assignment: Lab 5
//
// Description: This file contains a programmatic overall description of the
// program. It should never contain assignments to special function registers
// for the exception key one-line code such as checking the state of the pin.
//
#include <Arduino.h>
#include <avr/io.h>
#include "switch.h"
#include "timer.h"
#define DELAY 1000

int main(){
  Serial.begin(9600);

  while(1){
    delayMs(DELAY);
  return 0;
}

