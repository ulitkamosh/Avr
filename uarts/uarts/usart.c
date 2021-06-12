#include "usart.h"

void USART_ini (unsigned int speed)
{
	UBRRH = (unsigned char) (speed>>8);
	UBRRL = (unsigned char) speed;
	UCSRB = (1<<RXEN)|(1<<TXEN); //включаем прием и передачу по usart
	UCSRB |= (1<<RXCIE); //разрешаем прерывания при приеме
	//UCSRA |= (1<<U2X); //удвоение частоты
	UCSRC = (1<<URSEL)|(0<<USBS)|(3<<UCSZ0); // обращаемся к регистру UCSRC (URSEL=1), ассинхронный режим (UNSEL=0),
	// без контроля четности (UPM1=0 UPM0=0), 2стоп -бита (USBS=1), 8битовая посылка (UCSZ1=1 и UCZ0=1)
}

void USART_Send_Char (unsigned char data)
{
	while(!(UCSRA&(1<<UDRE)));  
	UDR = data; //начнем передавать данные, но только убедившись в том что буфер пуст
}

void USART_Send_Str(char str[])
{
	unsigned char i = 0;
	USART_Send_Char(0x0d);
	while (str[i]!='\0')
	{
		USART_Send_Char(str[i]);
		i++;
	}
	USART_Send_Char(0x0d);
}
