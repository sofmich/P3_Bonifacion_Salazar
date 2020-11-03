/*
 * movements.c
 *
 *	Implement the following sequences to make movements on hid device
 *  Created on: Nov 2, 2020
 */
#define CLICK 0x01
#include "mouse.h"
uint8_t drawNumber(usb_hid_mouse_struct_t *Hid_mouse);
uint8_t copyLeftToRigth(void);
uint8_t openPaint(void);
uint8_t openTxt(void);


void  drawNumber(usb_hid_mouse_struct_t *Hid_mouse)
{
    static int8_t x = 99U;
    static int8_t y = 0U;
    enum
    {
        DIAGONAL,
        CIRCLE,
		IDLE
    };

    static uint8_t dir = DIAGONAL;

    switch (dir)
    {
        case DIAGONAL:
            /* Move left and down.*/
        	Hid_mouse->buffer[0] = CLICK;
        	Hid_mouse->buffer[1] = x;
        	Hid_mouse->buffer[2] = y;
            x--;
            y--;
            if (x == 0)
            {
                dir++;
            }
            break;
        case CIRCLE:
        	 /* Move left and down.*/
        	Hid_mouse->buffer[0] = CLICK;
        	Hid_mouse->buffer[1] = x;
        	Hid_mouse->buffer[2] = y;
        	x--;
        	y--;
        	if (x == 0)
        	{
        		dir++;
        	}
            break;
        case IDLE:
        	break;
        default:
            break;
    }
}

uint8_t copyLeftToRigth(void)
{

}

uint8_t openPaint(void)
{

}

uint8_t openTxt(void)
{

}
