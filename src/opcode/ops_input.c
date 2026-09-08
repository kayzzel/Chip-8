#include "chip_8.h"
#include "opcode.h"

#include <stdint.h>

uint8_t	skip_if_VX_pressed(t_Chip8 *chip8, t_nibble nibble)
{
	if (chip8->V[nibble.x] == 1)
		chip8->pc += 2;

	return (0);
}

uint8_t	skip_if_VX_not_pressed(t_Chip8 *chip8, t_nibble nibble)
{
	if (chip8->V[nibble.x] == 0)
		chip8->pc += 2;

	return (0);
}

uint8_t	wait_VX_press(t_Chip8 *chip8, t_nibble nibble)
{
	if (chip8->V[nibble.x] == 0)
		chip8->pc -= 2;

	return (0);
}
