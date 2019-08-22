/*
 * main.c
 *
 *  Created on: 23 cze 2019
 *      Author: Arkadiusz Pytlik
 */

#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "TM1637/TM1637.h"

#define AUTO_OCR ( (F_CPU / 1024 / 100) -1 )

void TIMER0_Init(void);
void KeyboardCallback(uint8_t code);

int main(void)
{
	TIMER0_Init();
	TM_Init();
	TM_RegisterKeyboardCallback(KeyboardCallback);
	sei();

	while(true)
	{
		TM_Task();
	}
}

void TIMER0_Init(void)
{
	TCCR0 |= (1 << WGM01) | (1 << CS02) | (1 << CS00);//ctc, F_CPU/1024
	OCR0 = AUTO_OCR;
	TIMSK |= (1 << OCIE0);
}

void KeyboardCallback(uint8_t code)
{
	static uint8_t cnt, dim = 8, custom = 1;


	switch(code)
	{
	case TM_KEYCODE_0:
		dim = 0;
		break;
	case TM_KEYCODE_1:
		dim = 1;
		break;
	case TM_KEYCODE_2:
		dim = 2;
		break;
	case TM_KEYCODE_3:
		dim = 3;
		break;
	case TM_KEYCODE_4:
		dim = 4;
		break;
	case TM_KEYCODE_5:
		dim = 5;
		break;
	case TM_KEYCODE_6:
		dim = 6;
		break;
	case TM_KEYCODE_7:
		dim = 7;
		break;
	case TM_KEYCODE_8:
		dim = 8;
		break;
	case TM_KEYCODE_9:

		break;
	case TM_KEYCODE_A:

		break;
	case TM_KEYCODE_B:
		cnt = 0;//clear counter
		break;
	case TM_KEYCODE_UP:
		cnt++;//increment sample counter
		break;
	case TM_KEYCODE_DOWN:
		cnt--;//decrement sample counter
		break;
	case TM_KEYCODE_LEFT:
		custom <<= 1;
		if(custom == 0x40) custom = 0x01;
		break;
	case TM_KEYCODE_RIGHT:
		custom >>= 1;
		if(custom == 0x00) custom = 0x20;
		break;
	case TM_KEYCODE_NONE:
		//key released! You can add an extra code here if release of the key also should be managed
		break;
	default:

		break;
	}

	//display counter on the left three digits
	TM_SetDigit(0, cnt / 100 % 10, TM_CHAR_REGULAR );
	TM_SetDigit(1, cnt / 10 % 10, TM_CHAR_REGULAR );
	TM_SetDigit(2, cnt % 10, TM_CHAR_WITH_DP );

	//display raw key code on the right three digits
	TM_SetDigit(3, custom, TM_CHAR_CUSTOM );
	TM_SetDigit(4, code / 10 % 10, TM_CHAR_REGULAR );
	TM_SetDigit(5, code % 10, TM_CHAR_REGULAR );

	TM_SetDuty(dim);
}

ISR(TIMER0_COMP_vect)
{
	TM_ISR();
}
