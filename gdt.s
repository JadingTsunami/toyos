global gdt_load

CODE_SEGMENT equ 0x08
DATA_SEGMENT equ 0x10


gdt_load:
    lgdt    [esp+4]
    ; far jump to initialize CS segment
    jmp     CODE_SEGMENT:load_segments


load_segments:
    mov     ax,DATA_SEGMENT
    mov     ds,ax
    mov     ss,ax
    mov     es,ax
    mov     gs,ax
    mov     fs,ax
    ret

