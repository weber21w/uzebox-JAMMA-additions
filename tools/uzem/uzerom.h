/*
(The MIT License)

Copyright (c) 2008-2016 by
David Etherton, Eric Anderton, Alec Bourque (Uze), Filipe Rinaldi,
Sandor Zsuga (Jubatian), Matt Pandina (Artcfox)
	
Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdint.h>

#ifndef UZEROM_H
#define UZEROM_H

#define HEADER_VERSION	1
#define VERSION_MAJOR	1
#define VERSION_MINOR	0
#define MAX_PROG_SIZE	61440 //65536-4096
#define HEADER_SIZE	512

#define PERIPHERAL_MOUSE	1
#define PERIPHERAL_KEYBOARD	2
#define PERIPHERAL_MULTITAP	4
#define PERIPHERAL_ESP8266	8
#define PERIPHERAL_LIGHTGUN	16

#define JAMMA_ROTATE_90		1
#define JAMMA_ROTATE_180	2
#define JAMMA_ROTATE_270	4
#define JAMMA_FLIP_H		8
#define JAMMA_FLIP_V		16
#define JAMMA_B0		32 //future use...
#define JAMMA_B1		64
#define JAMMA_B2		128

#pragma pack( 1 )
struct RomHeader{//if this is modified, packrom.cpp needs to be updated
    //Header fields (512 bytes)
    uint8_t marker[6]; //'UZEBOX'
    uint8_t version; //header version
    uint8_t target; //AVR target (ATmega644=0, ATmega1284=1)
    uint32_t progSize; //program memory size in bytes
    uint16_t year;
    uint8_t name[32];
    uint8_t author[32];
    uint8_t icon[16*16];
    uint32_t crc32;
    uint8_t psupport; //supported peripherals
    uint8_t description[64];
    uint8_t pdefault; //default enabled peripherals(Emulator only)
    uint8_t jamma; //JAMMA options
    uint8_t reserved[112];
};
#pragma pack()


/*
    isUzeromFile - returns true if the file is indeed an .uze file
*/
bool isUzeromFile(char* in_filename);

/*
    readUzeImage - reads an .uze file into the header and buffer structures provided.
*/
bool loadUzeImage(char* in_filename,RomHeader *header,unsigned char *buffer);

/*
    load_hex - loads a hex image into the buffer provided, and provides the number of bytes read.
*/
bool loadHex(const char *in_filename,unsigned char *buffer,unsigned int *bytesRead = 0);

#endif
