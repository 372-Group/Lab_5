#include <i2c.h>
#define wait_for_completion while(!(TWCR & (1 << TWINT)));
void beginTransmission(int num){
    TWCR = ((1 << TWEN) | (1<<TWINT) | (1<<TWINT));
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