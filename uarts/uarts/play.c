#include "Play.h"

const unsigned int tabz[]  = {4,8,16,32,64,128,256};
const unsigned char mel0[] = {132, 141, 141, 139, 141, 139, 141, 137, 132, 132, 132, 141, 141, 142, 139, 176, 128, 144, 146, 146, 154, 154, 153, 151, 149, 144, 153, 153, 151, 153, 181, 128, 96, 255};
const unsigned char mel1[] = {74, 109, 128, 64, 77, 106, 128, 64, 79, 77, 79, 77, 79, 77, 79, 77, 79, 113, 128, 64, 255};
const unsigned char mel2[] = {144, 143, 141, 136, 144, 143, 141, 136, 144, 143, 141, 136, 146, 144, 143, 144, 255};
const unsigned char mel3[] = {75, 64, 79, 32, 43, 32, 43, 47, 32, 43, 32, 53, 32, 75, 64, 82, 32, 43, 32, 43, 51, 32, 50, 46, 32, 43, 32, 50, 32, 55, 32, 43, 42, 32, 41, 38, 32, 45, 75, 255};
const unsigned int PROGMEM tabkd[] = {0, 4748, 4480, 4228, 3992, 3768, 3556, 3356, 3168, 2990, 2822, 2664, 2514, 2374, 2240, 2114, 1996, 1884, 1778, 1678, 1584, 1495, 1411, 1332, 1257, 1187, 1120, 1057, 998, 942, 889, 839, 792};
const unsigned int PROGMEM tabkd1[] = {0, 3768, 3356, 2990, 2822, 2514, 2240, 1996, 1884, 1678,  1495, 1411, 1257, 1120, 998, 942, 839};
unsigned char mel4[20];
unsigned char mel5[20];
unsigned char mel6[20];
unsigned char mel7[10];

char buffermel[100];

int buf=0;
unsigned int tempo=2;
unsigned int oct=0;

void ChangeTempo(int t)
{
  
	if (t == 0){
		if (tempo<4) {tempo=tempo+1; PORTA=0x08;_delay_ms(500);}
		}
	if (t == 1){
		if (tempo>1){tempo=tempo-1;PORTA=0x04;_delay_ms(500);}
		}
}

void ChangeOctave(int o)
{
	if (o == 0){
		if (oct<7) {oct=oct+7; PORTA=0x08;_delay_ms(500);}
	}
	if (o == 1){
		if (oct>6) {oct=oct-7;PORTA=0x04;_delay_ms(500);}
	}
}

void SaveBuff(int g)
{
	int b;
	int z;
	int nt=0;
	int tempp=0;
	unsigned char bufferstr[3];
	char *uk=&bufferstr[0];
	USART_Send_Char((unsigned char) g);
	g=g+3;
	for (b=0; b<=g; b++)
	{
		if (buffermel[b]==',')
		{	
			b=b-3;
			
 			for (z=0; z<3; z++)
 			{
 				bufferstr[z]=buffermel[(b+z)];
				
			}
			b=b+4;
			tempp=atoi(uk);
			if (buf == 0){

					mel4[nt] =(char) tempp;
				}
			if (buf == 1)
				{
					mel5[nt] =(char) tempp;
				}
			if (buf == 2)
				{
					mel6[nt] =(char) tempp;
				}
			if (buf == 3)
				{
					mel7[nt] =(char) tempp;
				}
			nt++;
		}
	}

	switch (buf)
	{
		case 0:
		{
			mel4[nt]=0xFF;
			USART_Send_Str("melody is on PB4");
		}
		break;
		case 1:
		{
			mel5[nt]=0xFF;
			USART_Send_Str("melody is on PB5");
		}
		break;
		case 2:
		{
			mel6[nt]=0xFF;
			USART_Send_Str("melody is on PB6");
		}
		break;
		case 3:
		{
			mel7[nt]=0xFF;
			USART_Send_Str("melody is on PB7");
		}
		break;
	}

	buf++;
	if (buf==4)
	{
		buf=0;
	}
	
}

void Play(int nota)
{
	if (pgm_read_word_near(&tabkd1[nota]) != NULL)	{ 
		TCCR1A=0x00;
		TCCR1B=0x09;
		nota = nota + oct;
		OCR1A= (pgm_read_word_near(&tabkd1[nota]));
		TCCR1A=0x40;
		_delay_ms(200);
		TCCR1A=0x00;
	}
}


void PlayMel(unsigned char *mel)
{
	unsigned char fnota;
	unsigned char dnota;
	unsigned char *nota;

	TCCR1A=0x00;
	TCCR1B=0x09;


	
		m3:	nota = mel;
		m4:	if (PINB==0xFF) goto m2;
		if (*nota==0xFF) goto m3;
		fnota = (*nota)&0x1F;
		dnota = ((*nota)>>5)&0x07;
		if (fnota==0) goto m5;
		OCR1A = (pgm_read_word_near(&tabkd[fnota]));
		TCCR1A=0x40;
		m5:	for (int i = 0; i < (2*tabz[dnota]/tempo); i++)
		{
			_delay_ms(10);
		}
		TCCR1A=0x00;
		for (int i = 0; i < (2*tabz[0]/tempo); i++)
		{
			_delay_ms(10);
		};
		nota++;
		goto m4;
	m2:TCCR1A=0x00;
}



