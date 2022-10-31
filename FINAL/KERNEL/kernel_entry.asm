section .text
[BITS 32]

global MemSize
    MemSize: db 0, 0
    mov [MemSize], bx

[EXTERN __main]
[EXTERN __kpanic]
call __main

jmp $

%include "../CPU/oldin.asm"
%include "../Paging/paging.asm"

section .rodata

%include "IncBins.asm"