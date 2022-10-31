#include"VGA_driv.c"
#include"memory.c"
#include"idt.c"
#include"isr.c"
#include"irq.c"
#include"gdt.h"
#include"shell.c"

extern void _kpanic(struct regs* r)
{
    return;
}

extern void _main()
{
    kClearScreen();
    GDT_Init();
    //init_paging();
    /*idt_install();
    isrs_install();
    irq_install();
    asm volatile ("sti");*/
    //timer_install();
    initializeMem();
    SetCursorPos(0, 0);
    char FirstStringtest[28] = {'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 'a', ' ', 't', 'e', 's', 't', ' ', 'o', 'f', ' ','t', 'h', 'e', ' ', 's', 'y', 's', 't', 'e', 'm'};
    char Warning[40] = {'I', 'f', ' ', 'y', 'o', 'u', ' ', 's', 'e', 'e', ' ', 't', 'h', 'i', 's', ',', 'y', 'o', 'u', 'r', ' ', 's', 'y', 's', 't', 'e', 'm', ' ', 'i', 's', 'n', 't', ' ', 'l' , 'o', 'a', 'd', 'i', 'n', 'g'};
    kprintf(VGA_COLOR_GREEN, VGA_COLOR_BLACK, FirstStringtest, 0, 0, 28);
    SetCursorPos(0, 1);
    kprintf(VGA_COLOR_RED, VGA_COLOR_BLACK, Warning, 0, 1, 40);
    SetCursorPos(0, 2);
    load_shell();
    return;
}