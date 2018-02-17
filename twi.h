/*
 * twi.h
 *
 * Created: 26.02.2017 6:54:33
 *  Author: Серый
 */ 


#ifndef TWI_H_
#define TWI_H_
void INIT_TWI(unsigned char twps,unsigned char twbr);
void I2C_StartCondition(void);
void I2C_StopCondition(void);
void I2C_SendByte(unsigned char byte);
void I2C_SendByteByADDR(unsigned char c,unsigned char addr);


#endif /* TWI_H_ */