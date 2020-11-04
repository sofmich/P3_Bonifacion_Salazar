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
	 static int x = 0U;
	 static uint8_t flag = running;

	 static uint8_t dir = step1;
	 static uint8_t keys_array[] = {KEY_RIGHT_GUI, KEY_P, KEY_A, KEY_I, KEY_N, KEY_T, KEY_ENTER};

	 bufferKey[2] = 0x00U;
	 if(flag == 0)
	 {
		 x++;
		 if (x > 200U)
		 {
			 bufferKey[2] = keys_array[dir];
			 dir++;
			 x = 0;
			 if(dir == 8)
			 {
				 dir = step1;
				 flag = ready;
				 bufferKey[2] = 0x00U;
			 }
		 }
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
	 static int x = 0U;
		 static uint8_t flag = running;

		 static first_notepad = 0;
		 static uint8_t dir = step1;
		 static uint8_t keys_array[] = {KEY_LEFT_GUI, KEY_N, KEY_O, KEY_T, KEY_E, KEY_P, KEY_A, KEY_D, KEY_ENTER, KEY_LEFT_GUI};

		 bufferKey[2] = 0x00U;
		 if(flag == 0)
		 {
			 x++;
			 if (x > 200U)
			 {
				 if(dir== step1)
				 {
					 bufferKey[3] = KEY_R;
				 }
				 if(dir == step9)
				 {
					 /*Windows + left*/
					 if(first_notepad == 0) bufferKey[3] = KEY_LEFTARROW;
					 if(first_notepad == 1) bufferKey[3] = KEY_RIGHTARROW;
				 }
				 bufferKey[2] = keys_array[dir];
				 dir++;
				 x = 0;
				 if(dir == 12)
				 {
					 first_notepad ++;
					 dir = step1;
					 if(first_notepad == 2)
					 {
						 flag = ready;
					 }
					 bufferKey[2] = 0x00U;
				 }
			 }
		 }
		 return flag;

}

uint8_t writeTxt(uint8_t * bufferKey)
{
	 static int x = 0U;
	 static uint8_t flag = running;

	 static uint8_t dir = step1;
	 static uint8_t keys_array[] = {KEY_A, KEY_U, KEY_X, KEY_I, KEY_L, KEY_I, KEY_O, KEY_LEFTCONTROL, KEY_LEFTCONTROL};

	 bufferKey[2] = 0x00U;
	 if(flag == 0)
	 {
		 x++;
		 if (x > 200U)
		 {
			 bufferKey[2] = keys_array[dir];
			 dir++;
			 x = 0;
			 if(dir == 8)
			 {
				 bufferKey[3] = KEY_A;
			 }
			 if(dir = 9)
			 {
				 bufferKey[3] = KEY_C;
			 }
			 if(dir == 10)
			 {
				 dir = step1;
				 flag = ready;
				 bufferKey[2] = 0x00U;
			 }
		 }
	 }
	 return flag;
}

uint8_t copyTxt(uint8_t * bufferKey)
{
	 static int x = 0U;
	 static uint8_t flag = running;

	 static uint8_t dir = step1;
	 static uint8_t keys_array[] = {KEY_LEFTCONTROL, KEY_ENTER};

	 bufferKey[2] = 0x00U;
	 if(flag == 0)
	 {
		 x++;
		 if (x > 200U)
		 {
			 bufferKey[2] = keys_array[dir];
			 dir++;
			 x = 0;
			 if(dir == 1)
			 {
				 bufferKey[3] = KEY_V;
			 }
			 if(dir == 3)
			 {
				 dir = step1;
				 flag = ready;
				 bufferKey[2] = 0x00U;
			 }
		 }
	 }
	 return flag;
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
