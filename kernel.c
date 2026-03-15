#include <stdint.h>

/* VGA text mode buffer - 0xB8000 is the memory-mapped display */
#define VGA_BUFFER 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

/* VGA color codes */
enum vga_color {
    VGA_BLACK = 0,
    VGA_BLUE = 1,
    VGA_GREEN = 2,
    VGA_CYAN = 3,
    VGA_RED = 4,
    VGA_MAGENTA = 5,
    VGA_BROWN = 6,
    VGA_LIGHT_GREY = 7,
    VGA_DARK_GREY = 8,
    VGA_LIGHT_BLUE = 9,
    VGA_LIGHT_GREEN = 10,
    VGA_LIGHT_CYAN = 11,
    VGA_LIGHT_RED = 12,
    VGA_LIGHT_MAGENTA = 13,
    VGA_YELLOW = 14,
    VGA_WHITE = 15,
};

/* Create a VGA character with color */
static inline uint16_t vga_entry(char c, uint8_t color) {
    return (uint16_t)c | ((uint16_t)color << 8);
}

/* Global cursor position */
static size_t cursor_row = 0;
static size_t cursor_col = 0;

/* Get pointer to VGA buffer */
static uint16_t* get_vga_buffer(void) {
    return (uint16_t*)VGA_BUFFER;
}

/* Print a character to screen */
static void putchar(char c) {
    uint16_t* vga = get_vga_buffer();
    uint8_t color = vga_entry(' ', VGA_LIGHT_GREEN | VGA_BLACK << 4);

    if (c == '\n') {
        cursor_col = 0;
        cursor_row++;
    } else if (c == '\r') {
        cursor_col = 0;
    } else if (c == '\t') {
        cursor_col += 4;
    } else {
        size_t idx = cursor_row * VGA_WIDTH + cursor_col;
        vga[idx] = vga_entry(c, VGA_LIGHT_GREEN | VGA_BLACK << 4);
        cursor_col++;
    }

    /* Scroll if we reach bottom */
    if (cursor_row >= VGA_HEIGHT) {
        cursor_row = VGA_HEIGHT - 1;
        /* Simple scroll: move all lines up */
        for (int row = 0; row < VGA_HEIGHT - 1; row++) {
            for (int col = 0; col < VGA_WIDTH; col++) {
                vga[row * VGA_WIDTH + col] = vga[(row + 1) * VGA_WIDTH + col];
            }
        }
        /* Clear last line */
        for (int col = 0; col < VGA_WIDTH; col++) {
            vga[(VGA_HEIGHT - 1) * VGA_WIDTH + col] = vga_entry(' ', VGA_LIGHT_GREEN | VGA_BLACK << 4);
        }
    }
}

/* Print a string */
static void print(const char* str) {
    while (*str) {
        putchar(*str);
        str++;
    }
}

/* Clear the screen */
static void clear_screen(void) {
    uint16_t* vga = get_vga_buffer();
    for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga[i] = vga_entry(' ', VGA_LIGHT_GREY | VGA_BLACK << 4);
    }
    cursor_row = 0;
    cursor_col = 0;
}

/* Kernel entry point - called from boot.asm */
void kernel_main(void) {
    clear_screen();

    print("================================\n");
    print("   HELLO FROM MY TOY OS!        \n");
    print("================================\n\n");
    print("If you can read this, the kernel\n");
    print("booted successfully!\n\n");
    print("VGA text buffer: 0xB8000\n");
    print("Running in 32-bit protected mode\n");
    print("\nPress Ctrl+C in QEMU to exit.\n");

    /* Halt */
    __asm__ __volatile__("cli; hlt");
}
