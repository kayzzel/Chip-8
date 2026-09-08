#include "chip_8.h"
#include "opcode.h"

#include <stdint.h>

uint8_t	set_VX_to_NN(t_Chip8 *chip8, t_nibble nibble)
{
	chip8->V[nibble.x] = nibble.nn;
	return (0);
}

uint8_t	add_NN_TO_VX(t_Chip8 *chip8, t_nibble nibble)
{
	chip8->V[nibble.x] += nibble.nn;
	return (0);
}

uint8_t	set_VX_to_VY(t_Chip8 *chip8, t_nibble nibble)
{
	chip8->V[nibble.x] = chip8->V[nibble.y];
	return (0);
}

uint8_t or_XY_to_VY(t_Chip8 *chip8, t_nibble nibble)
{
	chip8->V[nibble.x] |= chip8->V[nibble.y];
	return (0);
}

uint8_t AND_XY_to_VY(t_Chip8 *chip8, t_nibble nibble)
{
	chip8->V[nibble.x] &= chip8->V[nibble.y];
	return (0);
}

uint8_t xor_XY_to_VY(t_Chip8 *chip8, t_nibble nibble)
{
	chip8->V[nibble.x] ^= chip8->V[nibble.y];
	return (0);
}
