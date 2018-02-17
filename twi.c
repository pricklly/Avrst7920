
/*SCL fr=CPU fre/16+2(TWBR)*(Presc)
Pres=1,4,16,64 TWPS<=0b11=3
SCL=CPU/16+2(TWBR)(TWPS^4)
(CPU/SCL-16)/(2*(TWPS^4))=TWBR
(1200-16)/2)=592=0x250
TWBR 1184/2*16=36=0x24 TWPS=0b10=2 SCL=100
CPU=12000000
ATMEGA16 SCL=PC0 SDA=PC1
*/
#include <avr/io.h>
#include "twi.h"
void INIT_TWI(unsigned char twps,unsigned char twbr)
{
	TWBR=twbr;
	switch (twps)
	{
		case 0:
		break;
		case 1:
		TWSR|=(1<<0);
		break;
		case 2:
		TWSR|=(1<<1);
		TWSR&=~(1<<0);
		break;
		case 3:
		TWSR|=(1<<1)|(1<<0);
		break;
	}
}
void I2C_StartCondition(void)
{
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
}
void I2C_StopCondition(void)
{
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}
void I2C_SendByte(unsigned char byte)
{
	TWDR=byte;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
}
void I2C_SendByteByADDR(unsigned char c,unsigned char addr)
{
  I2C_StartCondition(); // Отправим условие START
  I2C_SendByte(addr); // Отправим в шину адрес устройства + бит чтения-записи
  I2C_SendByte(c);// Отправим байт данных
  I2C_StopCondition();// Отправим условие STOP
}
