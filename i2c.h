#ifndef I2C_H
#define I2C_H

void beginTransmission(int num);
void beginTransmission();
void read();
void write(int num);
void requestFrom(int num1, int num2);

/* If the implementation of these functions 
 * overlap, this is fine.
 * */

#endif
