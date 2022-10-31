section .text
[BITS 32]

global MemSize
    MemSize: db 0, 0
    mov [MemSize], bx

[EXTERN __main]
[EXTERN __kpanic]
call __main

jmp $
