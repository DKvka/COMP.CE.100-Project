/*
 * Pixel.c
 *
 *  Created on: 11-11-26
 *      Author: Diego Koivukangas && Ossi H�rk�nen
 */

#include "Pixel.h"


//Table for pixel dots.
//				 dots[X][Y][COLOR]
volatile uint8_t dots[8][8][3]={0};


void set_bit(uint8_t* addr, uint8_t mask) {
	*addr |= mask;
}

void unset_bit(uint8_t* addr, uint8_t mask) {
	*addr &= ~mask;
}

void send_byte(uint8_t byte)
{
	for (uint8_t mask = 0b10000000; mask != 0; mask >>= 1) {
		if (mask & byte) {
			set_bit(CTRL_ADDR, SDA_MASK);
		} else {
			unset_bit(CTRL_ADDR, SDA_MASK);
		}

		set_bit(CTRL_ADDR, SCK_MASK);
		unset_bit(CTRL_ADDR, SCK_MASK);
		
	}
};


// Here the setup operations for the LED matrix will be performed
void setup(){
	*CHANNEL_ADDR = 0;
	*CTRL_ADDR = 0;

	// Resetting the screen at start is a MUST to operation (Set RSTn to 1).

	unset_bit(CTRL_ADDR, RST_MASK);
	usleep(500);
	set_bit(CTRL_ADDR, RST_MASK);

	//Write code that sets 6-bit values in register of DM163 chip. Recommended that every bit in that register is set to 1. 6-bits and 24 "bytes", so some kind of loop structure could be nice.
	//24*6 bits needs to be transmitted

	set_bit(CTRL_ADDR, SDA_MASK);
	// 24x
	for (uint8_t j = 0; j < 24; j++) {
		// Single mini-byte inner loop
		for (uint8_t i = 0; i < 6; i++) {
			set_bit(CTRL_ADDR, SCK_MASK);

			unset_bit(CTRL_ADDR, SCK_MASK);
		}
	}


	//Final thing in this function is to set SB-bit to 1 to enable transmission to 8-bit register.

	set_bit(CTRL_ADDR, SB_MASK);
}

//Change value of one pixel at led matrix. This function is only used for changing values of dots array
void SetPixel(uint8_t x,uint8_t y, uint8_t r, uint8_t g, uint8_t b){
	dots[x][y][0] = b;
	dots[x][y][1] = g;
	dots[x][y][2] = r;
}


//Put new data to led matrix. Hint: This function is supposed to send 24-bytes and parameter x is for channel x-coordinate.
void run(uint8_t x){
	//Write code that writes data to led matrix driver (8-bit data). Use values from dots array
	//Hint: use nested loops (loops inside loops)
	//Hint2: loop iterations are 8,3,8 (pixels,color,8-bitdata)

	for (uint8_t y = 0; y < 8; y++ ) {
		for (uint8_t color = 0; color < 3; color++) {
			send_byte(dots[x][y][color]);
		}
	}
	latch();
}

//Latch signal. See colorsshield.pdf or DM163.pdf in project folder on how latching works
void latch(){
	set_bit(CTRL_ADDR, LAT_MASK);
	unset_bit(CTRL_ADDR, LAT_MASK);
}


//Set one line (channel) as active, one at a time.
void open_line(uint8_t x){
	*CHANNEL_ADDR = 1 << x;
}



