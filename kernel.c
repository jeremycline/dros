#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#error "Use a cross-compiler"
#endif

#if !defined(__i386__)
#error "This targets x86 only, so use the proper compiler"
#endif

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

/* Hardware text mode color constants. */
enum vga_color {
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};

uint8_t make_color(enum vga_color foreground, enum vga_color background)
{
	return foreground | background << 4;
}

uint16_t make_vgaentry(char character, uint8_t color)
{
	uint16_t character16 = character;
	uint16_t color16 = color;
	return character16 | color16 << 8;
}

size_t strlen(const char *string)
{
	size_t size = 0;
	while (string[size] != 0) {
		size++;
	}
	return size;
}

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;

void terminal_initialize()
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = (uint16_t *) 0xB8000;
	for (size_t row = 0; row < VGA_HEIGHT; row++) {
		for (size_t column = 0; column < VGA_WIDTH; column++) {
			const size_t index = row * VGA_WIDTH + column;
			terminal_buffer[index] =
			    make_vgaentry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t column, size_t row)
{
	const size_t index = row * VGA_WIDTH + column;
	terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_putchar(char c)
{
	if (c == '\n') {
		terminal_column = 0;
		terminal_row++;
		return;
	}

	if (terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		terminal_row++;
	}
	if (terminal_row == VGA_HEIGHT) {
		// Shift everyone up to make a new row available
		for (size_t row = 1; row < VGA_HEIGHT; row++) {
			for (size_t column = 0; column < VGA_WIDTH; column++) {
				const size_t entry = row * VGA_WIDTH + column;
				terminal_buffer[entry - VGA_WIDTH] =
				    terminal_buffer[entry];
				terminal_buffer[entry] =
				    make_vgaentry(' ', terminal_color);
			}
		}

		terminal_column = 0;
		terminal_row--;
	}

	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	terminal_column++;
}

void terminal_writestring(const char *data)
{
	size_t datalen = strlen(data);
	for (size_t i = 0; i < datalen; i++) {
		terminal_putchar(data[i]);
	}
}

void kernel_main()
{
	terminal_initialize();
	terminal_writestring
	    ("a\nb\nc\n.\n.\n.\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nx\ny\nz\n");
}
