#pragma once

#include"Typedefs.h"
#include"IO.c"
#include"colors.c"

/*
###########################################################
##                   -- VGA DRIVER --                    ##
##         > MADE BY PLASMA COMPANY                      ##
##         > DO NOT COPY WHITOUT PERMISSION              ##
##                                                       ##
##                                                       ##
###########################################################
*/

// ## ENVIOREMENT VARIABLES ##
// |                |
//\/               \/
#define VIDEO_MEMORY		(char*)0xB8000
#define VGA_WIDTH	80

volatile int curMode = 0;
char ker_tty[4000];
int curColor = VGA_COLOR_BLACK | VGA_COLOR_WHITE;
uint16_t CursorPos = 0;

void display_tty(char* tty){
	for(int i = (int)VIDEO_MEMORY; i < (int)VIDEO_MEMORY + 4000; i += 1)
			*((char*)i) = tty[i - (int)VIDEO_MEMORY];
}

void display_tty_line(char* tty, int line){
	for(int i = (int)VIDEO_MEMORY + (line * 160); i < (int)VIDEO_MEMORY + ((line + 1) * 160); i += 1)
			*((char*)i) = tty[i - (int)VIDEO_MEMORY];
}

void kClearScreen() // clear the entire text screen
{
    char *vidmem = (char *) 0xb8000;
    unsigned int i=0;
    while(i < (80*25*2))
    {
        vidmem[i]=' ';
        i++;
        vidmem[i]=VGA_COLOR_WHITE;
        i++;
    };
};

void SetCursorPosRaw(uint16_t pos){	// Does some I/O black magic 
	if(pos >= 0 && pos < 2000) {
		outb(0x3d4, 0x0f);
		outb(0x3d5, (uint8_t)(pos & 0xff));
		outb(0x3d4, 0x0e);
		outb(0x3d5, (uint8_t)((pos >> 8) & 0xff));
		CursorPos = pos;
	}
	return;
}

void SetCursorPos(int x, int y){
	uint16_t pos;
            
			pos = y * VGA_WIDTH + x;
			SetCursorPosRaw(pos);
	return;
}

uint16_t GetCursorPos()
{
	uint16_t pos = 0;
	outb(0x3D4, 0x0F);
	pos |= inb(0x3D5);
	outb(0x3D4, 0x0E);
	pos |= ((uint16_t)inb(0x3D5)) << 8;
	return pos;
}
void disable_cursor()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void clear_tty(int col, char *tty){	//col...or
	if(col == -1) col = curColor;		//-1: maintain current colour
	for(int i = 0; i < 4000; i += 1) {
			if(i % 2 == 0) tty[i] = 32;	//Default is spaces
			else tty[i] = col;
	}

}


void col_tty(int col, char* tty){
		for(int i = 1; i < 4000; i += 2)
			tty[i] = col;
}

					// SET LINE COLOUR
void col_tty_line(int line, int col, char* tty){
	for(int i = VGA_WIDTH * 2 * line + 1;
	i < VGA_WIDTH * 2 * (line + 1) + 1; i += 2)  tty[i] = col;
}

void clr_tty_line(int line, char *tty){
	for(int i = VGA_WIDTH * 2 * line;
	i < VGA_WIDTH * 2 * (line + 1); i += 2)  tty[i] = 0; 	// CLR WITH 0s
		
}

void kprintc(unsigned char c, unsigned char forecolour, unsigned char backcolour, int x, int y)
{
     uint16_t attrib = (backcolour << 4) | (forecolour & 0x0F);
     volatile uint16_t * where;
     where = (volatile uint16_t *)0xB8000 + (y * 80 + x) ;
     *where = c | (attrib << 8);
	 SetCursorPos(x + 1, y + 0);
}

void kprintf(int forecolour, unsigned char backcolour, const char *string, int x, int y, int char_num)
{
    volatile char *video = (volatile char*)0xB8000;         // VGA
    uint16_t attrib = (backcolour << 4) | (forecolour & 0x0f);  //set background and text color
    volatile uint16_t * where;
    int i = 0;                          // counter
    while (i < char_num)                // algorithm that takes every character of the list and prints it
    {
        where = (volatile uint16_t *) 0xB8000 + (y * 80 + x + i);
        *where = *string++ | (attrib << 8);
        i++;
    }
	SetCursorPos(char_num, y);
}


void MoveCursorLR(int i){			// MOVE CURSOR HORIZONTALLY
	if((CursorPos > 0 && i < 0) || (CursorPos < 1999 && i > 0)){
		switch(curMode){
			case 0:
				CursorPos += i;
				SetCursorPosRaw(CursorPos);
				break;
			default:
				if(!(i < 0 && CursorPos == 1920)){
					CursorPos += i;
					SetCursorPosRaw(CursorPos);
				}	
		}
	}
	else if (i < 0) {
		CursorPos = 0;
		SetCursorPosRaw(CursorPos);
	}
	else {
		CursorPos = 1999;
		SetCursorPosRaw(CursorPos);
	}
	return;
}

void MoveCursorUD(int i){			// MOVE CURSOR VERTICALLY

	if((CursorPos / 80 < 24 && i > 0) || (CursorPos / 80 > 0 && i < 0)){
		switch(curMode){
			case 0:
				CursorPos += VGA_WIDTH * i;
				SetCursorPosRaw(CursorPos);
				break;
		}
	}
	else if (i < 0) {
		CursorPos = 0;
		SetCursorPosRaw(CursorPos);
	}
	else {
		CursorPos = 1999;
		SetCursorPosRaw(CursorPos);
	}
	return;
}

void kprintn(int x,int y)
{
	char empty[1] = {' '};
	kprintf(VGA_COLOR_WHITE, VGA_COLOR_BLACK, empty, x, y, 1);
	SetCursorPos(x, y);
}

/*
############################ SYSTEM PRINT ############################
Why? It's easier.
BETA /!\



void set_char_at_video_memory(char character, int offset) {
    unsigned char *vidmem = (unsigned char *) VIDEO_MEMORY;
    vidmem[offset] = character;
    vidmem[offset + 1] = VGA_COLOR_WHITE;
}


int get_row_from_offset(int offset) {
    return offset / (2 * 80);
}

int get_offset(int col, int row) {
    return 2 * (row * 80 + col);
}

int move_offset_to_new_line(int offset) {
    return get_offset(0, get_row_from_offset(offset) + 1);
}


void kprintsys(char *string) {
    int offset = GetCursorPos();
    int i = 0;
    while (string[i] != 0) {
        if (string[i] == '\n') {
            offset = move_offset_to_new_line(offset);
        } else {
            set_char_at_video_memory(string[i], offset);
            offset += 2;
        }
        i++;
    }
    SetCursorPos(offset, offset);
}
*/