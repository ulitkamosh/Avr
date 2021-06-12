#include "usart.h"

void USART_ini (unsigned int speed)
{
	UBRRH = (unsigned char) (speed>>8);
	UBRRL = (unsigned char) speed;
	UCSRB = (1<<RXEN)|(1<<TXEN); //�������� ����� � �������� �� usart
	UCSRB |= (1<<RXCIE); //��������� ���������� ��� ������
	//UCSRA |= (1<<U2X); //�������� �������
	UCSRC = (1<<URSEL)|(0<<USBS)|(3<<UCSZ0); // ���������� � �������� UCSRC (URSEL=1), ������������ ����� (UNSEL=0),
	// ��� �������� �������� (UPM1=0 UPM0=0), 2���� -���� (USBS=1), 8������� ������� (UCSZ1=1 � UCZ0=1)
}

void USART_Send_Char (unsigned char data)
{
	while(!(UCSRA&(1<<UDRE)));  
	UDR = data; //������ ���������� ������, �� ������ ���������� � ��� ��� ����� ����
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
