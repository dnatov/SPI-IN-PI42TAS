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

#include "IN_PI42TAS.h"
#include <stdlib.h>
#include <string.h>

// Shift from LSB to MSB in color, assign an 8bit logic high or low byte and increment buffer pointer
#define IN_PI42TAS_FillBuffer(COLOR)\
{\
    uint8_t bits = COLOR;\
    for (int pos = 7 ; pos >= 0 ; pos--) \
    {\
        if (bits & (1 << pos)) \
        {\
            *Ptr++ = LOGIC_LED_1;   \
        } \
        else \
        {                           \
            *Ptr++ = LOGIC_LED_0;\
        }\
    }\
}\

const int LED_BYTE_SIZE = 24;
const int LED_RESET_PULSE = 10;
const uint8_t LOGIC_LED_0 = 0xC0;
const uint8_t LOGIC_LED_1 = 0xF0;

enum IN_PI42TAS_Colors_t
{
    Red = 0x00FF00,
    Green = 0xFF0000,
    Blue = 0x0000FF
};

void IN_PI42TAS_Init(struct IN_PI42TAS_t* instance, uint16_t amountOfLeds)
{
    instance->_bufferSize = LED_BYTE_SIZE * amountOfLeds + LED_RESET_PULSE;
    instance->_numberOfLeds = amountOfLeds;
    // Allocate 192 bits per LED address. 8 spi bits per LED protocol bit. 24bits x 8
    instance->_buffer = (uint8_t *) malloc(instance->_bufferSize);
    IN_PI42TAS_TurnOffAll(instance);
}

static inline void ClearLEDBuffer(struct IN_PI42TAS_t* instance)
{
    memset(instance->_buffer, 0x00, instance->_bufferSize);
}

void IN_PI42TAS_TurnOffAll(struct IN_PI42TAS_t* instance)
{
    // Fill buffer with 0s
    ClearLEDBuffer(instance);

    // Set SPI buffer
    instance->SPI_ReadWriteMethodPtr(instance->_buffer, instance->_bufferSize, 0, spmMode0);
}

static inline void FillBufferForLED(struct IN_PI42TAS_t* instance, uint16_t index, uint8_t color[3])
{
    uint8_t *Ptr = &instance->_buffer[24 * index];
    IN_PI42TAS_FillBuffer(color[0]); //g
    IN_PI42TAS_FillBuffer(color[1]); //r
    IN_PI42TAS_FillBuffer(color[2]); //b
}

void IN_PI42TAS_SetAndWriteAllToColor(struct IN_PI42TAS_t* instance, uint8_t color[3])
{
    for(int i = 0; i < instance->_numberOfLeds; i++)
    {
        FillBufferForLED(instance, i, color);
    }

    instance->SPI_ReadWriteMethodPtr(instance->_buffer, instance->_bufferSize, 0, spmMode0);
}

void IN_PI42TAS_SetAndWriteLED(struct IN_PI42TAS_t* instance, uint16_t index, uint8_t color[3])
{
    FillBufferForLED(instance, index, color);

    instance->SPI_ReadWriteMethodPtr(instance->_buffer, instance->_bufferSize, 0, spmMode0);
}

void IN_PI42TAS_SetLED(struct IN_PI42TAS_t* instance, uint16_t index, uint8_t color[3])
{
    FillBufferForLED(instance, index, color);
}

void IN_PI42TAS_WriteBufferToSPI(struct IN_PI42TAS_t* instance)
{
    instance->SPI_ReadWriteMethodPtr(instance->_buffer, instance->_bufferSize, 0, spmMode0);
}