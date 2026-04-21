---
  Toy OS - Educational Operating System

  A minimal operating system that boots and prints "Hello World" to the VGA
  text buffer.

  What This Teaches You

  - Multiboot specification - How bootloaders (GRUB) load kernels
  - Protected mode - 32-bit x86 execution environment
  - VGA text buffer - Memory-mapped I/O at 0xB8000
  - Linker scripts - Controlling memory layout
  - Bare metal programming - No OS, no libc, just hardware

  Prerequisites (Windows)

  # Install QEMU
  winget install QEMU.QEMU

  # Install NASM assembler
  winget install NASM.NASM

  # Optional: Install cross-compiler (GCC multilib or OSDev cross-compiler)
  winget install MSYS2.MSYS2
  # Then follow OSDev wiki for cross-compiler setup

  Building & Running

  Quick build (Windows)

  build.bat

  Using Make

  make run

  Files Explained

  ┌──────────────┬─────────────────────────────────────────────────────┐
  │     File     │                       Purpose                       │
  ├──────────────┼─────────────────────────────────────────────────────┤
  │ src/boot.asm │ Multiboot header + stack setup + jump to kernel     │
  ├──────────────┼─────────────────────────────────────────────────────┤
  │ src/kernel.c │ Kernel code - writes directly to VGA memory         │
  ├──────────────┼─────────────────────────────────────────────────────┤
  │ linker.ld    │ Tells linker where to place code in memory (at 1MB) │
  ├──────────────┼─────────────────────────────────────────────────────┤
  │ Makefile     │ Build automation                                    │
  ├──────────────┼─────────────────────────────────────────────────────┤
  │ build.bat    │ Windows build script                                │
  └──────────────┴─────────────────────────────────────────────────────┘

  How It Works

  1. QEMU emulates an x86 PC
  2. GRUB (via -kernel flag) loads our multiboot-compliant binary
  3. boot.asm runs first, sets up stack, calls kernel_main()
  4. kernel.c writes characters to 0xB8000 (VGA text buffer)
  5. Text appears on screen!

  Expected Output

  HELLO FROM MY TOY OS!
  ================================

  If you can read this, the kernel
  booted successfully!

  VGA text buffer: 0xB8000
  Running in 32-bit protected mode

  Troubleshooting

  "linking failed": You need a cross-compiler or gcc with multilib support.
  - Install WSL and use sudo apt install gcc-multilib
  - Or build an OSDev cross-compiler (see OSDev wiki)

  "qemu not found": Install QEMU with winget install QEMU.QEMU then restart
  terminal.

  Next Steps

  Once this works, extend it:
  - Add keyboard input (read from 0x60 port)
  - Implement a simple monitor/shell
  - Add more colors and scrolling
  - Switch to 64-bit long mode
  - Write a basic memory allocator

  Resources

  - https://wiki.osdev.org/
  - https://www.gnu.org/software/grub/manual/multiboot/multiboot.html
  - https://en.wikipedia.org/wiki/VGA_hardware#Text_mode
