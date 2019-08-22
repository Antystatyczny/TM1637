/*
 * TM1637.h
 *
 *  Created on: 23 cze 2019
 *      Author: Arkadiusz Pytlik
 */

#ifndef TM1637_TM1637_H_
#define TM1637_TM1637_H_

#include <stdint.h>


//keyboard map (Anty's Dream version)

//                       1  2  3
//        UP
//                       4  5  6
//   LEFT    RIGHT
//                       7  8  9
//       DOWN
//                       A  0  B

#define TM_KEYCODE_NONE		0
#define TM_KEYCODE_0		20
#define TM_KEYCODE_1		14
#define TM_KEYCODE_2		9
#define TM_KEYCODE_3		10
#define TM_KEYCODE_4		22
#define TM_KEYCODE_5		17
#define TM_KEYCODE_6		18
#define TM_KEYCODE_7		13
#define TM_KEYCODE_8		12
#define TM_KEYCODE_9		15
#define TM_KEYCODE_A		21
#define TM_KEYCODE_B		23
#define TM_KEYCODE_UP		8
#define TM_KEYCODE_DOWN		19
#define TM_KEYCODE_LEFT		16
#define TM_KEYCODE_RIGHT	11

/*
 * Available digits and letters
 */
#define TM_DIGIT_VALUE_0		0
#define TM_DIGIT_VALUE_1		1
#define TM_DIGIT_VALUE_2		2
#define TM_DIGIT_VALUE_3		3
#define TM_DIGIT_VALUE_4		4
#define TM_DIGIT_VALUE_5		5
#define TM_DIGIT_VALUE_6		6
#define TM_DIGIT_VALUE_7		7
#define TM_DIGIT_VALUE_8		8
#define TM_DIGIT_VALUE_9		9
#define TM_DIGIT_VALUE_A		10
#define TM_DIGIT_VALUE_B		11
#define TM_DIGIT_VALUE_C		12
#define TM_DIGIT_VALUE_D		13
#define TM_DIGIT_VALUE_E		14
#define TM_DIGIT_VALUE_F		15
#define TM_DIGIT_VALUE_OFF		16


/*
 * Custom digit elements
 */
#define TM_CUSTOM_SEGMENT_A		0x01
#define TM_CUSTOM_SEGMENT_B		0x02
#define TM_CUSTOM_SEGMENT_C		0x04
#define TM_CUSTOM_SEGMENT_D		0x08
#define TM_CUSTOM_SEGMENT_E		0x10
#define TM_CUSTOM_SEGMENT_F		0x20
#define TM_CUSTOM_SEGMENT_G		0x40
#define TM_CUSTOM_SEGMENT_DP	0x80

/*
 * Prototype of pointer to the callback function
 */
typedef void (*OnPress)(uint8_t);

/*
 * Character type
 */
#define	TM_CHAR_REGULAR		0	/* Regular character */
#define	TM_CHAR_WITH_DP		1	/* Regular character with decimal point enabled */
#define TM_CHAR_CUSTOM		2	/* Custom character made from TM_CUSTOM_SEGMENT_x elements */



/*
 * MCU pins initialization
 * param: none
 * return: none
 */
void TM_Init(void);

/*
 * Attach callback function
 * param: pointer to the void fun(uint8_t) function prototype
 * return: none
 */
void TM_RegisterKeyboardCallback(OnPress cb);

/*
 * Function sets new digit on selected position.
 * param: digit - selected digit (0 to 5)
 * param: value - new value (0 to 16 or TM_DIGIT_VALUE_x) for selected digit or
 * custom character bitmap made from TM_CUSTOM_SEGMENT_x elements
 * param: character_type:
 * TM_CHAR_REGULAR treats parameter value as regular value to display (from 0h to Ah or off),
 * TM_CHAR_WITH_DP treats parameter value as regular value with decimal point enabled (from 0h to Ah or off but DP is on),
 * TM_CHAR_CUSTOM treats parameter value as custom bitmap made from TM_CUSTOM_SEGMENT_x elements
 * return: none
 */
void TM_SetDigit(uint8_t digit, uint8_t value, uint8_t character_type);

/*
 * Sets digits brightness.
 * param: duty - from 0 (display off) to 8 (display duty cycle 14/16)
 * return: none
 * */
void TM_SetDuty(uint8_t duty);

/*
 * Reads keyboard state.
 * param: none
 * return: key code or 0x00 when no key is pressed
 */
uint8_t TM_GetKeys(void);

/*
 * Automatic keyboard check & call (if registered) callback function.
 * param: none
 * return: none
 */
void TM_Task(void);

/*
 * Function which must be called periodically (ie. by interrupt subroutine) when TM_Task being used.
 * param: none
 * return: none
 */
void TM_ISR(void);

#endif /* TM1637_TM1637_H_ */
