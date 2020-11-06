/*
 * movements.c
 *
 *	Implement the following sequences to make movements on hid device
 *  Created on: Nov 2, 2020
 */

#include "movements.h"
#include "stdio.h"


static int8_t x = 40U;
static int8_t y = 0U;
//static uint8_t dir = step1;

void delay(uint32_t max)
{
	uint32_t delay_counter = 0;
	while (max > delay_counter)
		delay_counter++;
}

uint8_t openPaint(uint8_t * bufferKey)
{
	static uint8_t flag = running;
	static uint8_t keys_array[] = {0x00, MODIFERKEYS_LEFT_CTRL, KEY_ESCAPE, KEY_P, KEY_A, KEY_I, KEY_N, KEY_T, KEY_ENTER};
	static uint8_t dir = step1;
	bufferKey[1] = 0x00U;
	bufferKey[3] = 0x00U;
	if(running == flag)
	{
		if(step2 == dir)
		{
			bufferKey[1] = keys_array[dir];
			bufferKey[3] = keys_array[dir + 1];
			dir++;
		}
		else
		{
			bufferKey[3] = keys_array[dir];
		}

		dir++;
		if(dir == step12)
		{
			dir = step1;
			flag = ready;
			bufferKey[3] = 0x00U;
		}
	}
	delay(KEYBOARD_DELAY);
	return flag;
}

uint8_t  drawNumber6(uint8_t *hid_buffer)
{

	static int8_t x = 99U;
	static int8_t y = 0U;
	static uint8_t done = -1;
	static uint8_t flag = running;
	static uint8_t dir = step3;

	switch (dir)
	{
	case step1:
		/* Move right. Increase X value. */
		hid_buffer[1] = 1U;
		hid_buffer[2] = 2U;
		hid_buffer[3] = 0U;
		x++;
		if (x > 99U)
		{
			dir = step4;
		}
		break;
	case step2:
		/* Move down. Increase Y value. */
		hid_buffer[1] = 1U;
		hid_buffer[2] = 0U;
		hid_buffer[3] = 2U;
		y++;
		if (y > 200U)
		{
			dir = step1;
		}
		break;
	case step3:
		/* Move left. Discrease X value. */
		hid_buffer[1] = 1U;
		hid_buffer[2] = (uint8_t)(-2);
		hid_buffer[3] = 0U;
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
		hid_buffer[1] = 1U;
		hid_buffer[2] = 0U;
		hid_buffer[3] = (uint8_t)(-2);
		y--;
		if (y < 70U)
		{
			dir = step3;
		}
		break;
	case step5:
		/* IDLE status */
		hid_buffer[1] = 0U;
		hid_buffer[2] = 0U;
		hid_buffer[3] = 0U;
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
	static uint8_t flag = running;
	static uint8_t dir = step1;
	switch (dir)
	{
	case step1:
		/* Move left. Discrease X value. */
		hid_buffer[1] = 0U;
		hid_buffer[2] = (uint8_t)(-8);
		hid_buffer[3] = 0U;
		x--;
		if (x < 2U)
		{
			dir = step2;
		}
		break;
	case step2:
		/* Do not move. Make click */
		hid_buffer[1] = 1U;
		hid_buffer[2] = 0U;
		hid_buffer[3] = 0U;
		dir = step3;
		break;
	case step3:
		/* Stop the click */
		hid_buffer[1] = 0U;
		hid_buffer[2] = 0U;
		hid_buffer[3] = 0U;
		dir = step4;
	case step4:
		/* Stop the click */
		hid_buffer[1] = 0U;
		hid_buffer[2] = 0U;
		hid_buffer[3] = 0U;
		flag = ready;
		dir = step1;
		break;
	default:
		break;
	}
	return flag;
}

uint8_t openTxt(uint8_t * bufferKey)
{
	 static uint8_t flag = running;
	 static uint8_t notepad = 1;
	 static uint8_t keys_array[] = {0x00, MODIFERKEYS_LEFT_CTRL, KEY_ESCAPE, KEY_N, KEY_O, KEY_T, KEY_E, KEY_P, KEY_A, KEY_D, KEY_ENTER, 0x00};
	 static uint8_t dir = step1;
	 bufferKey[1] = 0x00U;
	 bufferKey[3] = 0x00U;
	 if(running == flag)
	 {
		 if(step13 != dir)
		 {
			 if(step2 == dir)
			 {
				 bufferKey[1] = keys_array[dir];
				 bufferKey[3] = keys_array[dir + 1];
				 delay(KEYBOARD_DELAY);
				 dir++;
			 }
			 else
			 {
				 bufferKey[3] = keys_array[dir];
				 delay(KEYBOARD_DELAY);
				 dir++;
				 if(step15 == dir)
				 {
					 bufferKey[1] = 0x00;
					 bufferKey[3] = 0x00;
					 dir = step1;
					 flag = ready;
				 }
			 }
		 }
		 else
		 {
			 if(1 == notepad)
			 {
				 /* Windows + left */
				 delay(20000000);
				 bufferKey[1] = MODIFERKEYS_LEFT_GUI;
				 bufferKey[3] = KEY_LEFTARROW;
				 delay(20000000);
				 notepad++;
				 dir = step1;

			 }
			 else
			 {
				 /* Windows + right */
				 delay(20000000);
				 bufferKey[1] = MODIFERKEYS_LEFT_GUI;
				 bufferKey[3] = KEY_RIGHTARROW;
				 delay(20000000);
				 notepad = 1;
				 dir ++;
			 }
		 }
	 }
	 return flag;
}

uint8_t writeTxt(uint8_t * bufferKey)
{
	 static uint8_t flag = running;
	 static uint8_t dir = step1;
	 bufferKey[1] = 0x00U;
	 bufferKey[3] = 0x00U;
	 if(running == flag)
	 {
	 switch(dir)
		 {
		 case(step1):
		{
			 bufferKey[1] = 0x00;
			 bufferKey[3] = 0x00;
			 dir++;
		}
		 break;
		 case(step2):
		{
			 bufferKey[3] = KEY_H;
			 dir++;
		}
		break;
		 case(step3):
		{
			 bufferKey[3] = KEY_O;
			 dir++;
		}
		 break;
		 case(step4):
		{
			 bufferKey[3] = KEY_L;
			 dir++;
		}
		 break;
		 case(step5):
		{
			 bufferKey[3] = KEY_A;
			 dir ++;
		}
		 break;
		 case(step6):
					{
			 bufferKey[1] = 0x00U;
			 bufferKey[3] = 0x00U;
			 dir ++;
					}
		 break;
		 case(step7):
		{
			 printf("LLEGAMOS ACÁ");
			 flag = ready;
			 dir = step1;
		}
		 break;
		 default:
			 break;
		 }
	 }

	 return flag;
}

uint8_t selectCopy(uint8_t * bufferKey)
{
	static uint8_t flag = running;
	static uint8_t dir = step1;
	bufferKey[1] = 0x00U;
	bufferKey[3] = 0x00U;
	if(running == flag)
	{
		switch(dir)
		{
		case(step1):
		bufferKey[1] = MODIFERKEYS_LEFT_CTRL;
		bufferKey[3] = KEY_A;
		dir++;
		break;
		case(step2):
		bufferKey[1] = MODIFERKEYS_LEFT_CTRL;
		bufferKey[3] = KEY_C;
		delay(20000000);
		dir++;
		break;
		case(step3):
		bufferKey[1] = 0x00;
		bufferKey[3] = 0x00;
		dir++;
		break;
		case(step4):
		flag = ready;
		dir = step1;
		delay(20000000);
		break;
		}
	}
	return flag;
}

uint8_t pasteTxt(uint8_t * bufferKey)
{
	static uint8_t flag = running;
	static uint8_t dir = step1;
	bufferKey[1] = 0x00U;
	bufferKey[3] = 0x00U;
	if(flag == running)
	{
		switch(dir)
		{
		case(step1):
							{
			bufferKey[1] = 0x00;
			bufferKey[3] = 0x00;
			dir++;
							}
		break;
		case(step2):
						bufferKey[1] = MODIFERKEYS_LEFT_CTRL;
		bufferKey[3] = KEY_V;
		dir++;
		break;
		case(step3):
		bufferKey[1] = 0x00;
		bufferKey[3] = 0x00;
		dir++;
		

		break;
		default:
		flag = ready;
		break;
		}

	}

	return flag;
}

uint8_t copyLeftToRigth(uint8_t *hid_buffer)
{
	static int8_t x = 255U;
	static int8_t y = 0U;
	static uint8_t flag = running;
	static uint8_t dir = step1;
	switch (dir)
	{
	case step1:
		/* Move left. Discrease X value. */
		hid_buffer[1] = 0U;
		hid_buffer[2] = 4U;
		hid_buffer[3] = 0U;
		x--;
		if (x < 2U)
		{
			dir = step2;
		}
		break;
	case step2:
		/* Do not move. Make click */
		hid_buffer[1] = 1U;
		hid_buffer[2] = 0U;
		hid_buffer[3] = 0U;
		dir = step3;
		break;
	case step3:
		/* Stop the click */
		hid_buffer[1] = 0U;
		hid_buffer[2] = 0U;
		hid_buffer[3] = 0U;
		dir = step4;
		break;
	case step4:
		/* Stop the click */
		hid_buffer[1] = 0U;
		hid_buffer[2] = 0U;
		hid_buffer[3] = 0U;
		flag = ready;
		break;
	default:
		break;
	}
	return flag;
}
