#include "main.h"

unsigned int mode;
unsigned char data;
int i=0;
int q=0;
int n=0;

void port_ini(void)
{

	DDRA=0x0F;

	PORTD=0x00;
	DDRD=0x20;

	PORTB=0xFF;
	DDRB=0x00;

	PORTC=0xFF;
	DDRC=0x00;
}

ISR(USART_RX_vect)
{
	data = UDR;

	if ((data=='1')||(data=='2')||(data=='3')||(data=='4')||(data=='5')||(data=='6')||(data=='7')||(data=='8')||(data=='9')||(data=='0')||(data==',')||(data=='p')||(data=='d')){
		if (mode==1)
		{	
			data = (data<<4);
			data = (data>>4);
			Play(data);

		} else {			
			if (i == 196) 
			{
				USART_Send_Str("error!");
				USART_Send_Str("limit reached");
				goto m2;	
			}
			if (data=='p')
			{
				if (n!=3)
				{
					USART_Send_Str("error!");
					USART_Send_Str("last note is too short");
					goto m2;
				}
				i++;
				buffermel[i]=',';
				
				SaveBuff(i);
				n=0;
				for (int ii=0;ii<i;ii++)
				{
					buffermel[ii]=NULL;
				}
				i=0;
				goto m2;
			}
			if (data=='d')
			{
				i--;
				if (n==0) {n=3;}else{n--;}
				goto m2;
			}
			if (n==3)
			{
				if (data!=',')
				{
					USART_Send_Str("error!");
					USART_Send_Str("expected ','");
					goto m2;	
				}
			}
			if (data==',')
			{
				if (n<3)
				{
					USART_Send_Str("error!");
					USART_Send_Str("correct note is 3 chr long");
					goto m2;
				}
				n=0;
				goto m3;
			}

			n++;
m3:			buffermel[i]=data;
			i++;	
m2:			USART_Send_Str("melody:");	
			for (q=0; q<i; q++){USART_Send_Char(buffermel[q]);}
		}
	} else 
	{
		USART_Send_Str("error!");
		USART_Send_Str("Put numbers 1..7");
	}
}

int main(void)
{	
	unsigned char count;
	unsigned char temp;
	unsigned char countc;
	unsigned char tempc;

	port_ini();
	USART_ini(12);
	sei();
	mode = 0;
	PORTA=mode+1;
	while (1)
	{	
		m1:	tempc=PINC;
		for (countc=0; countc<4; countc++)
		{
			if ((tempc&1)==0) {
				if (countc<2){
					mode = countc;
					PORTA=mode+1;
				}
				if (countc==2)
				{
					if (mode==0){ChangeTempo(0);PORTA=mode+1;}
					else {ChangeOctave(0);PORTA=mode+1;}
				}
				if (countc==3)
				{
					if (mode==0){ChangeTempo(1);PORTA=mode+1;}
					else {ChangeOctave(1);PORTA=mode+1;}
				}
			}
			tempc >>= 1;
		}
		temp=PINB;
		
		for (count=0; count<8; count++)
		{
			if ((temp&1)==0) {
				if (mode==1) {
					count++;
					Play(count);
					goto m1;
				} else {
					switch (count)
					{
						case 0:
						{
							PlayMel(&mel0[0]);
						}
						break;
						case 1:
						{
							PlayMel(&mel1[0]);
						}
						break;
						case 2:
						{
							PlayMel(&mel2[0]);
						}
						break;
						case 3:
						{
							PlayMel(&mel3[0]);
						}
						break;
						case 4:
						{
							PlayMel(&mel4[0]);
						}
						break;
						case 5:
						{
							PlayMel(&mel5[0]);
						}
						break;
						case 6:
						{
							PlayMel(&mel6[0]);
						}
						break;
						case 7:
						{
							PlayMel(&mel7[0]);
						}
						break;
					}
					goto m1;
					}
				}
			temp >>= 1;
			}
		}
		TCCR1A=0x00;
	}
	

