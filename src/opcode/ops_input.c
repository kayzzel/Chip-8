#include "chip_8.h"
#include "opcode.h"

#include <stdint.h>
uint8_t	skip_if_VX_pressed(t_Chip8 *chip8, t_nibble nibble)
{
	if (chip8->keypad[chip8->V[nibble.x]] == 1)
		chip8->pc += 2;

	return (0);
}

uint8_t	skip_if_VX_not_pressed(t_Chip8 *chip8, t_nibble nibble)
{
	if (chip8->keypad[chip8->V[nibble.x]] == 0)
		chip8->pc += 2;

	return (0);
}

uint8_t	wait_VX_press(t_Chip8 *chip8, t_nibble nibble)
{
	uint8_t	key;
	uint8_t	pressed;

	pressed = 0;
	key = 0;
	while (key < 16)
	{
		if (chip8->keypad[key] == 1)
		{
			chip8->V[nibble.x] = key;
			pressed = 1;
			break ;
		}
		key++;
	}
	if (!pressed)
		chip8->pc -= 2;
	return (0);
}
