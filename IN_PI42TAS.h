//MIT License
//
//Copyright (c) 2021 Dana Natov
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#ifndef IN_PI42TAS_LIBRARY_H
#define IN_PI42TAS_LIBRARY_H

#include <stdbool.h>
#include <stdint.h>
#include "LL_spi.h"

struct IN_PI42TAS_t
{
    size_t _bufferSize;
    uint8_t *_buffer;
    uint16_t _numberOfLeds;
    LL_SPIMaster_ReadWriteMethod_t SPI_ReadWriteMethodPtr;
};

/// Initialization function
/// \param instance a pointer to the instance struct
/// \param amountOfLeds the amount of LEDs in series.
void IN_PI42TAS_Init(struct IN_PI42TAS_t* instance, uint16_t amountOfLeds);

/// Turns off all LEDs in the string and resets the byte buffer
/// \param instance a pointer to the instance of the object
void IN_PI42TAS_TurnOffAll(struct IN_PI42TAS_t* instance);

/// Sets all of the LEDs to a certain color
/// \param instance a pointer to the instance of the object
/// \param color 24 bit uint for representing color (GRB)
void IN_PI42TAS_SetAllToColor(struct IN_PI42TAS_t* instance, uint8_t color[3]);

/// Sets a particular LED to a certain color
/// \param instance a pointer to the instance of the object
/// \param index The index of the LED in the chain
/// \param color 24 bit uint for representing color (GRB)
void IN_PI42TAS_SetLED(struct IN_PI42TAS_t* instance, uint16_t index, uint8_t color[3]);

#endif //IN_PI42TAS_LIBRARY_H
