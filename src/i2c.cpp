#include "i2c.h"
#include <avr/io.h>

#define wait_for_completion while(!(TWCR & (1 << TWINT)));
#define I2C_WRITE 0
#define I2C_READ 1


void init2C(){
    TWSR |= (1 << TWPS0);
    TWSR &= ~(1 << TWPS1); // prescalar = 1
    TWBR = 0xC6; //bit rate generator = 10k (TWBR = 198)
    TWCR |= (1 << TWINT) | (1 << TWEN); // enable two wire interface
}

void beginTransmission(int num){
    TWCR = ((1 << TWEN) | (1<<TWINT) | (1<<TWSTA));
    wait_for_completion;
    TWDR = num + I2C_WRITE;
}
void endTransmission(){
    // set the stop condition
    TWCR = ((1 << TWEN) | (1 << TWINT) | (1 << TWSTO));
    wait_for_completion;
}
void read(){

    TWCR = ((1 << TWEN) | (1 << TWINT) | (1 << TWSTA)); // set another start condition
    wait_for_completion;
    TWDR = 0x6C + I2C_READ; // SLA+R, switch to reading
    TWCR = ((1 << TWEN) | (1 << TWINT)); // trigger I2C action
    wait_for_completion;

}
void write(int num){
    
}
void requestFrom(int num1, int num2){

}