#ifndef INPUT_H
#define INPUT_H

#include "stdint.h"

typedef struct {
    uint8_t buttons[4];
    uint8_t switches[2];
} Input_State;

#endif INPUT_H
