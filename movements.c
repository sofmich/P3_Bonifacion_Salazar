/*
 * movements.c
 *
 *	Implement the following sequences to make movements on hid device
 *  Created on: Nov 2, 2020
 */

#include "movements.h"

#define KEYBOARD_DELAY 	400000U
#define MOUSE_DELAY 	10000U



static int8_t x = 40U;
static int8_t y = 0U;
static uint8_t dir = step1;
static uint8_t status = step1;

void delay(uint32_t max) {
	uint32_t delay_counter = 0;
	while (max > delay_counter)
		delay_counter++;
}



uint8_t openPaint(uint8_t * bufferKey)
{
	static uint8_t flag = running;
	switch (status) {
	case step1: {
		/* Open windows searcher*/
		bufferKey[3] = KEY_LEFT_GUI;
		bufferKey[4] = KEY_R;
		delay(KEYBOARD_DELAY);
	}
		break;
	case step2: {
		/* Start writing mspaint*/
		bufferKey[3] = KEY_M;
		delay(KEYBOARD_DELAY);
	}
		break;
	case step3: {
		bufferKey[3] = KEY_S;
		delay(KEYBOARD_DELAY);
	}
		break;
	case step4: {
		bufferKey[3] = KEY_P;
		delay(KEYBOARD_DELAY);
	}
		break;
	case step5: {
		bufferKey[3] = KEY_A;
		delay(KEYBOARD_DELAY);
	}
		break;
	case step6: {
		bufferKey[3] = KEY_I;
		delay(KEYBOARD_DELAY);
	}
		break;
	case step7: {
		bufferKey[3] = KEY_N;
		delay(KEYBOARD_DELAY);
	}
		break;
	case step8: {
		bufferKey[3] = KEY_T;
		delay(KEYBOARD_DELAY);
	}
		break;
	case step9:
		bufferKey[3] = KEY_ENTER;
		delay(KEYBOARD_DELAY);
		break;
	case step10:
		/*Idle and flag complete*/
		flag = ready;
		break;
	default:
		break;
	}

	if (status == step10) {
		flag = ready;
	} else {
		status++;
	}

	return flag;
}

uint8_t  drawNumber6(uint8_t *hid_buffer)
{

	static int8_t x = 99U;
	static int8_t y = 0U;

	static uint8_t dir = step3;
	static uint8_t done = -1;
	static uint8_t flag = running;
	switch (dir)
	{
	case step1:
		/* Move right. Increase X value. */
		hid_buffer[0] = 1U;
		hid_buffer[1] = 2U;
		hid_buffer[2] = 0U;
		x++;
		if (x > 99U)
		{
			dir = step4;
		}
		break;
	case step2:
		/* Move down. Increase Y value. */
		hid_buffer[0] = 1U;
		hid_buffer[1] = 0U;
		hid_buffer[2] = 2U;
		y++;
		if (y > 200U)
		{
			dir = step1;
		}
		break;
	case step3:
		/* Move left. Discrease X value. */
		hid_buffer[0] = 1U;
		hid_buffer[1] = (uint8_t)(-2);
		hid_buffer[2] = 0U;
		x--;

		if (x < 2U)
		{
			done ++;
			dir= step2;
			if(done == ready)
			{
				dir= step5;
				done = -1;
			}
		}
		break;
	case step4:
		/* Move up. Discrease Y value. */
		hid_buffer[0] = 1U;
		hid_buffer[1] = 0U;
		hid_buffer[2] = (uint8_t)(-2);
		y--;
		if (y < 70U)
		{
			dir = step3;
		}
		break;
	case step5:
		/* IDLE status */
		hid_buffer[0] = 0U;
		hid_buffer[1] = 0U;
		hid_buffer[2] = 0U;
		done ++;
		if(ready == done)
		{
			flag = ready;
		}
		break;
	default:
		break;
	}
	return flag;
}




uint8_t movetoLeft(uint8_t *hid_buffer)
{
	static int8_t x = 150U;
	static int8_t y = 0U;

	static uint8_t dir = step1;
	static uint8_t flag = running;
	switch (dir)
	{
	case step1:
		/* Move left. Discrease X value. */
		hid_buffer[0] = 0U;
		hid_buffer[1] = (uint8_t)(-8);
		hid_buffer[2] = 0U;
		x--;
		if (x < 2U)
		{
			dir = step2;
		}
		break;
	case step2:
		/* Do not move. Make click */
		hid_buffer[0] = 1U;
		hid_buffer[1] = 0U;
		hid_buffer[2] = 0U;
		dir = step3;
		break;
	case step3:
		/* Stop the click */
		hid_buffer[0] = 0U;
		hid_buffer[1] = 0U;
		hid_buffer[2] = 0U;
		dir = step4;
	case step4:
		flag = ready;
		break;
	default:
		break;
	}
	return flag;

}
uint8_t openTxt(int8_t * bufferKey)
{

}

uint8_t copyLeftToRigth(uint8_t *hid_buffer)
{
	static int8_t x = 255U;
	static int8_t y = 0U;

	static uint8_t dir = step1;
	static uint8_t flag = running;
	switch (dir)
	{
	case step1:
		/* Move left. Discrease X value. */
		hid_buffer[0] = 0U;
		hid_buffer[1] = 4U;
		hid_buffer[2] = 0U;
		x--;
		if (x < 2U)
		{
			dir = step2;
		}
		break;
	case step2:
		/* Do not move. Make click */
		hid_buffer[0] = 1U;
		hid_buffer[1] = 0U;
		hid_buffer[2] = 0U;
		dir = step3;
		break;
	case step3:
		/* Stop the click */
		hid_buffer[0] = 0U;
		hid_buffer[1] = 0U;
		hid_buffer[2] = 0U;
		dir = step4;
		break;
	case step4:
		flag = ready;
		break;
	default:
		break;
	}
	return flag;

}
