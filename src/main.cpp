// Author: Jessmer Palanca , Ariel Villasenor, Lu Yu
// Net ID: jjpalanca, arielv, lyu18     
// Date: 11/03/19     
// Assignment: Lab 4
//
// Description: This file contains a programmatic overall description of the
// program. It should never contain assignments to special function registers
// for the exception key one-line code such as checking the state of the pin.
//
#include <Arduino.h>
#include <avr/io.h>
#include "adc.h"
#include "switch.h"
#include "timer.h"
#include "pwm.h"
#define LONG_DELAY 30000
/*
 * Define a set of states that can be used in the state machine using an enum.
 */

typedef enum stateType{
  wait_press, wait_release, debounce_press, debounce_release
} stateType;

//initializing state
volatile stateType state = wait_press;

int main(){
  /* for ADC */
  initADC();
  initTimer1();
  initSwitchPB3();
  initPWMTimer3();
  initPWMTimer4();
  sei();
  Serial.begin(9600);
  unsigned int result = 0;
  float voltage = 0;
  bool On = true;

  while(1){
        // print out ADC value
        // read in ADCL first then read ADCH
        if(!On){
          turnOff();
          Serial.println(On);
        }
        else{
        result = ADCL;
        result += ((unsigned int) ADCH) << 8;
        voltage = result * (5.0/1023.0);
        Serial.println(voltage);
        Serial.println(On);
        changeDutyCycle(voltage);
        }
      switch(state){
        /*Initially `wait_press` is in the `On` state.*/
      case wait_press:
        delayUs(100000);
        break;
        /*When button is pressed, it is sent into the `debounce_press` state
         *where it will make the state equal to `wait_release`.
         * */
      case debounce_press:
        delayUs(LONG_DELAY);
        state = wait_release;
        break;
        /*When button is waiting to be released, it will be in the 
        * `wait_release` state.
        * */
      case wait_release:
        delayUs(100000);
        break;
        /* When button is released, it will be in the `debounce_release` state.
        * It will then be from On to Off, or from Off to On.
        * It will then be switch to the `wait_press` state.
        * */
      case debounce_release:
        delayUs(LONG_DELAY);
        if(On){
          On = false;
        }
        else{
          On = true;
        }
        state = wait_press;
        break;
      }
  }

  return 0;
}

/* This is currently setup for interrupts on pin 22. Will need to be setup for deboucing,
 * which it currently does not do
 */
ISR(PCINT0_vect){
  //use this function for the PCINT0 flag when it goes up
  //handle the switch press
  /*If it is in the `wait_press` state, then it will be switched to the `debounce_press` state.*/
  if(state == wait_press){
    state = debounce_press;
  }
  /*If it is in the `wait_release` state, then it will be switched to the `debounce_release` state.*/
  else if(state == wait_release){
    state = debounce_release;
  }
}

