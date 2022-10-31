# How to use the Plasma Bootloader
Download the file (boot.bin) or download the RAW files and compile them using:

nasm boot.asm -f bin -o boot.bin

OR:

nasm boot.asm -f bin -o boot.img

# HOW DO I KNOW IF IT'S WORKING?

To know if Plasma Bootloader is working, you need to boot it up using a virtual machine and then, if it's working, it will print '0050' to the screen.
'0050' means that the bootloader is working and reading fron the disk.
