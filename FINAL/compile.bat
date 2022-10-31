@echo off

echo Compiling

COLOR 6

gcc -ffreestanding -m32 -g -c kernel.c -o kernel.o

gcc -ffreestanding -m32 -g -c gdt.c -o gdtc.o

echo GCC Compiled

echo LINKING

COLOR C

ld -T NUL -o kernel.tmp -Ttext 0x1000 kernel_entry.o kernel.o gdt.o gdtc.o

objcopy -O binary -j .text kernel.tmp kernel.bin

echo Finished linking

echo Compiled, closing the app

COLOR 2

echo Enjoy PlasmaOs 32bit

COLOR 7

echo Closing the app