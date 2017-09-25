global _loader                   ; the entry symbol for ELF
global loader

MAGIC_NUMBER  equ 0x1BADB002     ; define the magic number constant
ALIGN_MODULES equ 0x00000001
CHECKSUM      equ -(MAGIC_NUMBER + ALIGN_MODULES)  ; calculate the checksum
                                ; (magic number + checksum + flags should equal 0)
KERNEL_STACK_SIZE equ 4096      ; size of stack in bytes
KERNEL_VIRTUAL_BASE equ 0xC0000000
KERNEL_PAGE_NUM equ (KERNEL_VIRTUAL_BASE >> 22)

section .data
align 0x1000 ; 4 KB alignment

; create a boot PDT for the 1st 4MB to load higher half kernel
kernel_boot_pdt:
    dd 0x00000083
    times (KERNEL_PAGE_NUM - 1) dd 0
    dd 0x00000083
    times (0x400 - KERNEL_PAGE_NUM - 1) dd 0

section .bss
align 4                         ; align at 4 bytes
kernel_stack:                   ; label points to beginning of memory
    resb KERNEL_STACK_SIZE      ; reserve stack for the kernel

section .text                   ; start of the text (code) section
align 4                         ; the code must be 4 byte aligned
    dd MAGIC_NUMBER             ; write the magic number to the machine code,
    dd ALIGN_MODULES                    ; the flags,
    dd CHECKSUM                 ; and the checksum


; adjust linker entry point
loader equ (_loader - 0xC0000000)

_loader:                         ; the loader label (defined as entry point in linker script)
    ; set up the temporary boot pdt
    mov ecx, (kernel_boot_pdt - KERNEL_VIRTUAL_BASE)
    mov cr3, ecx

    ; enable 4 MB pages
    mov ecx, cr4
    or  ecx, 0x10
    mov cr4, ecx

    ; set PG bit and enabling paging
    mov ecx, cr0
    or ecx, 0x80000000
    mov cr0, ecx

    lea ecx, [higher_half]
    jmp ecx

higher_half:
    ; get rid of the temporary 4MB mapping
    mov dword [kernel_boot_pdt], 0
    invlpg [0]

    mov esp, kernel_stack + KERNEL_STACK_SIZE   ; point esp to the start of the
                                                ; stack (end of memory area)
    extern kmain
    push ebx
    call kmain

.loop:
    jmp .loop                   ; loop forever

