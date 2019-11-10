#include "i2c.h"
#include <avr/io.h>

#define wait_for_completion while(!(TWCR & (1 << TWINT)));


void init2C(){
    TWSR |= (1 << TWPS0);
    TWSR &= ~(1 << TWPS1); // prescalar = 1
    TWBR = 0xC6; //bit rate generator = 10k (TWBR = 198)
    TWCR |= (1 << TWINT) | (1 << TWEN); // enable two wire interface
}

void beginTransmission(int num){
    TWCR = ((1 << TWEN) | (1<<TWINT) | (1<<TWSTA));
    wait_for_completion;
    TWDR = num;
}
void endTransmission(){

}
void read(){

}
void write(int num){

}
void requestFrom(int num1, int num2){

}