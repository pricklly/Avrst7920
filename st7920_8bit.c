#define LCD PORTB
 #define DLCD DDRB
 #define INT PORTC
 #define DINT DDRC
 #define E 7
 #define RS 5 //0-instruction,1-data;serial mode:1-chip enable 0-chip disable
 #define RW 6 //0-write,1-read
 #define D7 7
 #define D6 6
 #define D5 5
 #define D4 4
 #define D3 3
 #define D2 2
 #define D1 1
 #define D0 0
 //#define PSB 0 //0-serial mode 1-4/8 parallel 
 //#define RESET 0 //0-active
 #define DATA 1
 #define CMD 0
 
  void strob_E_8_bit(void)
 {
	 INT|=(1<<E);
	 _delay_ms(1);
	 INT&=~(1<<E);
 }
 void send_command_8_bit(unsigned char byte)
 {
	 
	 INT&=~(1<<RW);
	 INT&=~(1<<RS);
	 LCD|=byte;
	 _delay_ms(2);
	 strob_E;
 }
  void send_data_8_bit(unsigned char byte)
 {
	 INT&=~(1<<RW);
	 INT|=(1<<RS);
	 LCD|=byte;
	 _delay_ms(2);
	 strob_E;
 }
 void send_red_8_bit(unsigned char byte, char parm)//USE DATA and CMD
 { 
	 if (parm==1)
		 send_data_8_bit(byte);
	 else
		 send_command_8_bit(byte);
 }
 void send_8_bit (unsigned char byte, char parm)//USE DATA and CMD
 {
		
		if (param==1)
		{
	 INT&=~(1<<RW);
	 INT|=(1<<RS);
	 LCD|=byte;
	 _delay_ms(2);
	 strob_E;	
		} else
		{
	 INT&=~(1<<RW);
	 INT&=~(1<<RS);
	 LCD|=byte;
	 _delay_ms(2);
	 strob_E;
		}
 }
 void init_pot_LCD_8_bit(void)
 {
	 
 }
 void init_lcd_8_bit(void)
 {
	 init_pot_LCD_8_bit;
	 INT&=(1<<RS);
	 INT&=(1<<RW);
	 _delay_ms(50);
	 send_command_8_bit(0x30);//0b00110000
	 _delay_us(150);
	 send_command_8_bit(0x30);//0b00110000
	 _delay_us(50);
	 send_command_8_bit(0x0C);//0b00001100)
	 _delay_us(150);
	 send_command_8_bit(0x01);
	 _delay_ms(20);
	 send_command_8_bit(0x0C);//0b00000110
	 
 }