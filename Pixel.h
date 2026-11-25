/*
 * Pixel.h
 *
 *  Created on: 25-11-2026
 *      Author: Ossi Härkönen, Diego Koivukangas
 */

#ifndef PIXEL_H_
#define PIXEL_H_

#include "platform.h"
#include "xil_printf.h"
#include "sleep.h"
#include "xgpiops.h"
#include "xttcps.h"
#include "xscugic.h"
#include "xparameters.h"

// MMIO locations
static uint8_t* const CHANNEL_ADDR = (uint8_t*) 0x41220000;
static uint8_t* const CTRL_ADDR = (uint8_t*) 0x41220008;
static uint8_t* const INPUT_ADDR = (uint8_t*) 0xE000A068;
static uint8_t* const LED_ADDR = (uint8_t*) 0x41200000;
static uint8_t* const RGB_ADDR = (uint8_t*) 0x41240000;

static const uint8_t SDA_MASK = 0b00010000;
static const uint8_t SCK_MASK = 0b00001000;
static const uint8_t SB_MASK = 0b00000100;
static const uint8_t LAT_MASK = 0b00000010;
static const uint8_t RST_MASK = 0b00000001;

void setup();
void SetPixel(uint8_t x,uint8_t y, uint8_t r, uint8_t g, uint8_t b);
void run(uint8_t x);
void latch();
void open_line(uint8_t x);

#endif PIXEL_H_