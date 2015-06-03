#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/vga.h>

/* Defines the current terminal cursor location */
size_t terminal_row;
size_t terminal_column;

uint8_t terminal_color;
uint16_t *terminal_buffer;

/* Initialize the terminal */
void terminal_init(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_vga_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = VGA_MEMORY_LOCATION;
	for (size_t row = 0; row < VGA_HEIGHT; row++) {
		for (size_t column = 0; column < VGA_WIDTH; column++) {
			const size_t index = row * VGA_WIDTH + column;
			terminal_buffer[index] =
			    make_vga_entry(' ', terminal_color);
		}
	}
}

void terminal_putentryat(char c, uint8_t color, size_t row, size_t column)
{
    const size_t index = row * VGA_WIDTH + column;
    terminal_buffer[index] = make_vga_entry(character, color);
}


/* Write a single character to the terminal */
void terminal_putchar(char c);
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
				terminal_buffer[entry - VGA_WIDTH] = terminal_buffer[entry];
				terminal_buffer[entry] = make_vgaentry(' ', terminal_color);
			}
		}

		terminal_column = 0;
		terminal_row--;
    }
}

/* Write non-null terminated data to the terminal */
void terminal_putdata(const char *data, size_t length);
{
    for(int i = 0; i < length; i++)
    {
        terminal_putchar(data[i]);
    }
}

/* Write a null terminated string to the terminal */
void terminal_putstring(const char *string); 
{
    terminal_putdata(string, strlen(string));
}
