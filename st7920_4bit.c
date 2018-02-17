 #define PORTLCD PORTB
 #define DDRLCD DDRB
 #define adrr 0x20
 #define E 3
 #define RS 2 //0-instruction,1-data;serial mode:1-chip enable 0-chip disable
 #define RW 1 //0-write,1-read
 #define D7 7
 #define D6 6
 #define D5 5
 #define D4 4
 #define PSB 0 //0-serial mode 1-4/8 parallel 
 #define RESET 0 //0-active
 #define DATA 1
 #define CMD 0
 //------------------------
 void strob_E(void)
 {
	 PORTLCD|=(1<<E);
	 _delay_ms(1);
	 PORTLCD&=~(1<<E);
 }
 void send_half_byte(unsigned char byte)
 {
	 PORTLCD|=((byte<<4)&0b00001111);
	strob_E;
 }
 void send_command(unsigned char byte)
 {
	 unsigned char hi,lo;
	 hi=byte>>4;
	 lo=byte&0b00001111;
	 PORTLCD&=~(1<<RS);
	 send_half_byte(hi);
	 _delay_ms(2);
	 send_half_byte(lo);
 }
  void send_data(unsigned char byte)
 {
	 unsigned char hi,lo;
	 hi=byte>>4;
	 lo=byte&0b00001111;
	 PORTLCD|=(1<<RS);
	 send_half_byte(hi);
	 _delay_ms(2);
	 send_half_byte(lo);
 }
 void send_red(unsigned char byte, char parm)//USE DATA and CMD
 { 
	 if (parm==1)
		 send_data(byte);
	 else
		 send_command(byte);
 }
 void send (unsigned char byte, char parm)//USE DATA and CMD
 {
		unsigned char hi,lo;
	 hi=byte>>4;
	 lo=byte&0b00001111;
		if (param==1)
		{
	 PORTLCD|=(1<<RS);
	 send_half_byte(hi);
	 _delay_ms(2);
	 send_half_byte(lo);	
		} else
		{
	 PORTLCD&=~(1<<RS);
	 send_half_byte(hi);
	 _delay_ms(2);
	 send_half_byte(lo);
		}
 }
 void send_16(uint16_t dword,char parm)
 {
	 uint8_t hi,lo;
	 hi=dword>>8;
	 send(hi,parm);
	 _delay_ms(2);
	 lo=dword&0000000011111111;
	 send(lo,parm);
 }

 void LCD_Init(void)
 {
_delay_ms(50);
send_command(0b00100000);
_delay_us(150);
send_command(0b00100000);
send_command(0b00000000);
_delay_us(150);
send_command(0b00000000);
send_command(0b11110000);
_delay_us(150);
send_command(0b00000000);
send_command(0b00010000);
_delay_ms(15);
send_command(0b00000000);
send_command(0b01100000);
 }
 
 
 /*
 void LCD_4bit_Init(void)
 {
	 PORTRESET|=(1<<RESET);
	 PORTRESET&=~(1<<RESET);
	 PORTRESET|=(1<<RESET);
	 PORTLCD|=(1<<PSB);
	 PORTLCD&=~(1<<RS);
	 PORTLCD&=~(1<<RW);
	 _delay_ms(100);
	 send_half_byte(0b0010);
	 _delay_us(150);
	 send_command(0b00100000);
	 _delay_us(150);
	 send_command(0b00001100);
	 _delay_us(150);
	 send_command(0b00000001);
	 _delay_ms(20);
	 send_command(0b00000110);
	 
 }*/
 