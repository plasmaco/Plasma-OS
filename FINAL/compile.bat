@echo off

echo Compiling

COLOR 6

nasm boot.asm -f bin -o boot.bin

nasm kernel_entry.asm -f elf -o kernel_entry.o

echo NASM Compiled

gcc -ffreestanding -m32 -g -c kernel.c -o kernel.o

echo GCC Compiled

echo LINKING

COLOR C

ld -T NUL -o kernel.tmp -Ttext 0x1000 kernel_entry.o kernel.o gdt.o gdtc.o

objcopy -O binary -j .text kernel.tmp kernel.bin

cat boot.bin kernel.bin > raw.bin

cat raw.bin zero.bin > plasmaos.bin

echo Finished linking

echo Compiled, closing the app

COLOR 2

echo Enjoy PlasmaOs 32bit

COLOR 7

echo Closing the app
