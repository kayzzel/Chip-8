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
	size_t	start;
	size_t	index;

	uint8_t x = chip8->V[nibble.x] % SCREEN_WIDTH;
	uint8_t y = chip8->V[nibble.y] % SCREEN_HEIGHT;

	index = 0;
	start = y * SCREEN_WIDTH + x;

	while (index < nibble.n && index + start < SCREEN_WIDTH)
	{
		if (chip8->V[0xF] != 1 && chip8->display[start + index] == 1)
			chip8->V[0xF] = 1;
		chip8->display[start + index] |= 1;
		index++;
	}
	return (0);
}
