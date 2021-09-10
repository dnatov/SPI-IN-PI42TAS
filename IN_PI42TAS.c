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

#define SETBIT(byte,bitIndex) ((byte) |= 1 << (bitIndex) ? (byte):(bitIndex))

const int LED_BYTE_SIZE = 9;

enum IN_PI42TAS_Colors_t
{
	Red = 0x00FF00,
	Green = 0xFF0000,
	Blue = 0x0000FF
};

void IN_PI42TAS_Init(struct IN_PI42TAS_t* instance, uint16_t amountOfLeds)
{
	//Allocate 72 bits per LED address. 3 spi bits per LED protocol bit. 24bits x 3
	instance->buffer = (uint8_t *) malloc(LED_BYTE_SIZE * amountOfLeds);
}

void IN_PI42TAS_TurnOffAll(struct IN_PI42TAS_t* instance)
{
	
}

void IN_PI42TAS_SetAllToColor(struct IN_PI42TAS_t* instance, uint8_t color[3])
{
	
}

void IN_PI42TAS_SetLED(struct IN_PI42TAS_t* instance, uint16_t index, uint8_t color[3])
{
	// Translate 24 bit color to a 72bit SPI communication
	for (size_t bitNumber = 0; bitNumber < 24; bitNumber++)
	{
		// Get color bit from 24bit color
		bool bit = (color[((bitNumber) % 8)] >> (bitNumber % 8)) & 1;

		uint8_t spiBits = bit ? 0b110 : 0b100;

		// Set bits
		for (size_t i = 0; i < 3; i++)
		{
			// Current Byte index of the buffer
			uint8_t byteIndex = (index * 9) + (bitNumber * 3) / 8;
			
			// Get current bit index in the byte for the bit we are about to set
			uint8_t bitIndex = ((bitNumber % 8) * 3) + i;

			SETBIT(instance->buffer[byteIndex], bitIndex);
		}
		
		instance->buffer[(index*LED_BYTE_SIZE)] = spiBits;
	}
}

inline void IN_PI42TAS_Bitshift()