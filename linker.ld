/* Linker script - tells linker where to place sections in memory */

/* Load kernel at 1MB (multiboot standard) */
ENTRY(_start)

SECTIONS {
    . = 1M;

    /* Multiboot header must be first */
    .multiboot : {
        *(.multiboot)
    }

    .text : {
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }
}
