#include "i2c.h"
#include <avr/io.h>

#define wait_for_completion while(!(TWCR & (1 << TWINT)));
#define I2C_WRITE 0
#define I2C_READ 1

void initI2C(){
    TWSR |= (1 << TWPS0);
    TWSR &= ~(1 << TWPS1); // prescalar = 1
    TWBR = 0xC6; //bit rate generator = 10kHz (TWBR = 198)
    TWCR |= (1 << TWINT) | (1 << TWEN); // enable two wire interface
}

void beginTransmission(int address){
    
    TWCR = ((1 << TWEN) | (1<<TWINT) | (1<<TWSTA)); /*Set the start condition*/
    wait_for_completion;
    
    write(address << 1);/*Send the address to the slave*/
}

void endTransmission(){
    // set the stop condition
    TWCR = ((1 << TWEN) | (1 << TWINT) | (1 << TWSTO));
    //wait_for_completion;
}

char read(){
    TWCR = ((1 << TWEN) | (1 << TWINT)); //  Not acknowledge
    wait_for_completion;

    return TWDR;
}
/* passes in the slave address or the data*/
void write(int num){
    TWDR = num; // sets the register address or the data
    TWCR = ((1<< TWEN)|(1<<TWINT)); // Triggers the I2C action
    wait_for_completion;
}
/*requestFrom(SlaveAddress, )*/
void requestFrom(int num1, int num2){
    write(num1);
    
    TWCR = ((1<<TWEN)|(1<<TWINT)|(1<<TWSTA)); // another start condition
    wait_for_completion;

    write((num2 << 1) + I2C_READ); // sets read bit from 1
}
