#ifndef USART_H_
#define USART_H_

#include "main.h"
#include "usart.c"

void USART_ini(unsigned int speed);
void USART_Send_Char (unsigned char data);
void USART_Send_Str(char str[]);

#endif /* USART_H_ */