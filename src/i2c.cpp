#include "i2c.h"
#include <avr/io.h>

#define wait_for_completion while(!(TWCR & (1 << TWINT)));


void init2C(){
    TWSR |= (1 << TWPS0);
    TWSR &= ~(1 << TWPS1);
    TWBR = 0xC6;
    TWCR |= (1 << TWINT) | (1 << TWEN);
}

void beginTransmission(int num){
    TWCR = ((1 << TWEN) | (1<<TWINT) | (1<<TWSTA));
    wait_for_completion;
}
void endTransmission(){

}
void read(){

}
void write(int num){

}
void requestFrom(int num1, int num2){

}