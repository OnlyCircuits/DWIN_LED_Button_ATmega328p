/*
 * DWIN_LED_Button.cpp
 * Author : OnlyCircuits
 */ 
#define F_CPU 16000000UL					//XTAL 16MHz 

#include <avr/io.h>							//Library I/O registers

void usart_init (void){						//USART init
	UCSR0A = (1<<U2X0);						//Double frequency
	UCSR0B = (1<<RXEN0);					//Receiver enable
	UCSR0C = (1<< UCSZ01)|(1<<UCSZ00);		//8 bit size	
	UBRR0 = 16;								//Error 2.1%
}

unsigned char usart_receive(void){
	
	while (!(UCSR0A & (1<<RXC0)));			//Polling the receiver
	return UDR0;							//Return data
}

int main(void)
{
	usart_init();							//Enable USART
	
	DDRB = 0xFF;							//PORTB as OUTPUT
	PORTB = 0x00;							//PORTB LOW
	
	unsigned char buff[9];					//Store the data
	
	while (1)
	{
		
		for (uint8_t c = 0; c <= 8; c++)	//Store 9 HEX numbers
		{
			buff[c] = usart_receive();
		}

		if (buff[8] == 0x01)				//Compare the digit
		{
			PORTB |= (1<<1);				//PORTB1 HIGH
		}
		else
		{
			PORTB &= ~(1<<1);				//PORTB1 LOW
		}
		
	}
	
}
