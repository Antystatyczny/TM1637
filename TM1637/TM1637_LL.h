/*
 * TM1637_LL.h
 *
 *  Created on: 29 cze 2019
 *      Author: Arkadiusz Pytlik
 */

#ifndef TM1637_TM1637_LL_H_
#define TM1637_TM1637_LL_H_


#include <avr/io.h>
#include <util/delay.h>

#define TM_DIO_PORT		PORTB
#define TM_DIO_PIN		PINB
#define TM_DIO_DDR		DDRB
#define TM_DIO_BIT		0

#define TM_CLK_PORT		PORTB
#define TM_CLK_PIN		PINB
#define TM_CLK_DDR		DDRB
#define TM_CLK_BIT		1

/* DIO pin hardware layer */
#define TM_DIO_IN		TM_DIO_DDR &= ~(1 << TM_DIO_BIT)
#define TM_DIO_OUT		TM_DIO_DDR |= (1 << TM_DIO_BIT)

#define TM_DIO_HIGH		TM_DIO_PORT |= (1 << TM_DIO_BIT)
#define TM_DIO_LOW		TM_DIO_PORT &= ~(1 << TM_DIO_BIT)

#define TM_DIO_IS_HIGH	((TM_DIO_PIN & (1 << TM_DIO_BIT)) == (1 << TM_DIO_BIT))
#define TM_DIO_IS_LOW	(!TM_DIO_IS_HIGH)

/* CLK pin hardware layer */
#define TM_CLK_IN		TM_CLK_DDR &= ~(1 << TM_CLK_BIT)
#define TM_CLK_OUT		TM_CLK_DDR |= (1 << TM_CLK_BIT)

#define TM_CLK_HIGH		TM_CLK_PORT |= (1 << TM_CLK_BIT)
#define TM_CLK_LOW		TM_CLK_PORT &= ~(1 << TM_CLK_BIT)

/* Delay macro with 1us resolution */
#define DELAY_US(x)		_delay_us(x)


#endif /* TM1637_TM1637_LL_H_ */
