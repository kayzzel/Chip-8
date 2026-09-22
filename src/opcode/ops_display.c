#include "chip_8.h"
#include "opcode.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>


uint8_t	clear_screen(t_Chip8 *chip8)
{
	memset(chip8->display, 0, (SCREEN_HEIGHT * SCREEN_WIDTH) * sizeof(uint8_t));
	return (0);
}

uint8_t	draw_sprite(t_Chip8 *chip8, t_nibble nibble)
{
	uint8_t	start_x;
	uint8_t	start_y;
	uint8_t	row;
	uint8_t	col;
	uint8_t	sprite_byte;
	uint8_t	sprite_pixel;
	size_t	target;

	start_x = chip8->V[nibble.x] % SCREEN_WIDTH;
	start_y = chip8->V[nibble.y] % SCREEN_HEIGHT;
	chip8->V[0xF] = 0;

	row = 0;
	while (row < nibble.n && start_y + row < SCREEN_HEIGHT)
	{
		sprite_byte = chip8->memory[chip8->I + row];
		col = 0;
		while (col < 8 && start_x + col < SCREEN_WIDTH)
		{
			sprite_pixel = (sprite_byte >> (7 - col)) & 0x1;
			if (sprite_pixel)
			{
				target = (start_y + row) * SCREEN_WIDTH + (start_x + col);
				if (chip8->display[target] == 1)
					chip8->V[0xF] = 1;
				chip8->display[target] ^= 1;
			}
			col++;
		}
		row++;
	}
	return (0);
}
