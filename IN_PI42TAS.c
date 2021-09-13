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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SETBIT(byte,nbit)   ((byte) |=  (1U<<(nbit)))
#define CLEARBIT(byte,nbit) ((byte) &= ~(1U<<(nbit)))
#define CHECK_BIT(byte,nbit) ((byte) &   (1UL<<(nbit)))

const int LED_BYTE_SIZE = 9;

enum IN_PI42TAS_Colors_t
{
    Red = 0x00FF00,
    Green = 0xFF0000,
    Blue = 0x0000FF
};

void IN_PI42TAS_Init(struct IN_PI42TAS_t* instance, uint16_t amountOfLeds)
{
    instance->_bufferSize = LED_BYTE_SIZE * amountOfLeds;

    // Allocate 72 bits per LED address. 3 spi bits per LED protocol bit. 24bits x 3
    instance->_buffer = (uint8_t *) malloc(instance->_bufferSize);
    IN_PI42TAS_TurnOffAll(instance);
}

void IN_PI42TAS_TurnOffAll(struct IN_PI42TAS_t* instance)
{
    // Fill buffer with 0s
    memset(instance->_buffer, 0, instance->_bufferSize);

    // Set SPI buffer
    instance->SPI_ReadWriteMethodPtr(instance->_buffer, instance->_bufferSize, 0);
}

void IN_PI42TAS_SetAllToColor(struct IN_PI42TAS_t* instance, uint8_t color[3])
{

}

static inline uint8_t EvalBitIndex(size_t bitNumber)
{
    return (((bitNumber % 8) * 3) % 8);
}

static inline uint16_t EvalByteIndex(uint16_t index, size_t bitNumber)
{
    return (index * 9) + (bitNumber * 3) / 8;
}

void IN_PI42TAS_SetLED(struct IN_PI42TAS_t* instance, uint16_t index, uint8_t color[3])
{
    // Translate 24 bit color to a 72bit SPI communication
    for (size_t bitNumber = 0; bitNumber < 24; bitNumber++)
    {
        // Get color bit from 24bit color
        bool bit = CHECK_BIT(color[((bitNumber) / 8)], (bitNumber % 8));

        uint8_t spiBits = bit ? 0b110 : 0b100;

        // Current Byte index of the buffer
        uint16_t byteIndex = EvalByteIndex(index, bitNumber);

        // Get current bit index in the byte for the bit we are about to set
        uint8_t bitIndex = EvalBitIndex(bitNumber);

        SETBIT(instance->_buffer[byteIndex], (7-bitIndex));
        if (bit)
        {
            byteIndex = (bitIndex + 1 >= 8) ? byteIndex + 1 : byteIndex;
            bitIndex = (bitIndex + 1) % 8; //keep within 8 bits
            SETBIT(instance->_buffer[byteIndex], (7-bitIndex));
        }
        else
        {
            byteIndex = (bitIndex + 1 >= 8) ? byteIndex + 1 : byteIndex;
            bitIndex = (bitIndex + 1) % 8; //keep within 8 bits
            CLEARBIT(instance->_buffer[byteIndex], (7-bitIndex));
        }
        byteIndex = (bitIndex + 1 >= 8) ? byteIndex + 1 : byteIndex;
        bitIndex = (bitIndex + 1) % 8; //keep within 8 bits
        CLEARBIT(instance->_buffer[byteIndex], (7-bitIndex));
    }

    instance->SPI_ReadWriteMethodPtr(instance->_buffer, instance->_bufferSize, 0);
}