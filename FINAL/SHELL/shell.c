#pragma once

#include "VGA_driv.c"

char ker_tty[4000];

int CommandCursor;
uint16_t CursorPosSh;
volatile int curModeSh;

int curColor;

const char* currentTask;

void fillColour(int y, int colour)
{
    for (int i = 0; i < 81; i++)
    {
        kprintc('a', colour, colour, i, y);
        kprintc('a', colour, colour, i, y+1);
    }
    
}

void load_shell()
{
    char Welcome[19] = {'W', 'e', 'l', 'c', 'o', 'm', 'e', ' ', 't', 'o', ' ', 'P', 'l', 'a', 's', 'm', 'a', 'O', 'S'};
    kClearScreen();
    fillColour(0, VGA_COLOR_GREEN);
    fillColour(23, VGA_COLOR_GREEN);
    kprintf(VGA_COLOR_WHITE, VGA_COLOR_BLACK, Welcome, 0, 2, 19);
    SetCursorPos(0, 3);
    return;
}

void refresh_shell()
{
    char Welcome[7] = {'W', 'e', 'l', 'c', 'o', 'm', 'e'};
    kClearScreen();
    SetCursorPos(0, 0);
    kprintf(VGA_COLOR_WHITE, VGA_COLOR_BLACK, Welcome, 0, 0, 7);
    return;
}

/*char CommandBuffer[128];
void findCommand(){
    SetCursorPosRaw(CommandCursor);
    char* c = (char*)(0xB8000 + 2 * 1920);
	int i;
	for(i = 0; i < 2000 - CursorPos; i += 1)
		CommandBuffer[i] = *(c + 2 * i);
	CommandBuffer[i] = 0;
}*/

/*void parseCommand(){
    findCommand();
    memrec();
    if(CommandBuffer[0] == 0){;}
    else{
        shellfunction* cmd = TryGetCMD(CommandBuffer);
        if(cmd != 0){
            cmd->fptr(strDecapitate(CommandBuffer, strLen(cmd->alias)));
        }
        else {kprint("\""); kprint(CommandBuffer); kprint("\" is not a command");}
    }
    memunrec();
    kprint("\n");
    CommandCursor = CursorPos;
    clr_tty_line(24, ker_tty);
    display_tty(ker_tty);
    //SetCursorPosRaw(1920);
    refreshShell();
}*/
