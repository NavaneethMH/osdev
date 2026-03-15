; Multiboot header for GRUB
; This makes our kernel bootable with GRUB bootloader

MBALIGN  equ  1 << 0             ; Align loaded modules on page boundaries
MEMINFO  equ  1 << 1             ; Request memory map from bootloader
FLAGS    equ  MBALIGN | MEMINFO  ; Multiboot flag field
MAGIC    equ  0xe85250d6         ; Multiboot2 magic number
CHECKSUM equ -(MAGIC + FLAGS)    ; Checksum to make header valid

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .bss
align 16
stack_bottom:
    resb 16384                  ; 16 KB stack
stack_top:

section .text
global _start
extern kernel_main

_start:
    ; Set up stack pointer
    mov esp, stack_top

    ; Call the kernel main function (no arguments)
    push dword 0
    push dword 0
    call kernel_main

    ; If kernel returns, hang the CPU
    cli                         ; Disable interrupts
.hang:
    hlt                         ; Halt CPU
    jmp .hang                   ; Loop forever
