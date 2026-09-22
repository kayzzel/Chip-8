#include "chip_8.h"
#include "opcode.h"

#include <stdint.h>
#include <stdlib.h>

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

uint8_t	set_VY_to_VX(t_Chip8 *chip8, t_nibble nibble)
{
	chip8->V[nibble.x] = chip8->V[nibble.y];
	return (0);
}

uint8_t or_XY_to_VX(t_Chip8 *chip8, t_nibble nibble)
{
	chip8->V[nibble.x] |= chip8->V[nibble.y];
	return (0);
}

uint8_t and_XY_to_VX(t_Chip8 *chip8, t_nibble nibble)
{
	chip8->V[nibble.x] &= chip8->V[nibble.y];
	return (0);
}

uint8_t xor_XY_to_VX(t_Chip8 *chip8, t_nibble nibble)
{
	chip8->V[nibble.x] ^= chip8->V[nibble.y];
	return (0);
}

uint8_t	add_VY_to_VX_carry(t_Chip8 *chip8, t_nibble nibble)
{
	uint16_t	result;

	result = chip8->V[nibble.x] + chip8->V[nibble.y];

	if (result > 0xFF)
		chip8->V[0xF] = 1;
	else
		chip8->V[0xF] = 0;
	chip8->V[nibble.x] = result & 0xFF;
	return (0);
}

uint8_t	sub_VY_to_VX_carry(t_Chip8 *chip8, t_nibble nibble)
{
	int16_t	result;

	result = chip8->V[nibble.x] - chip8->V[nibble.y];

	if (result >= 0x0)
		chip8->V[0xF] = 1;
	else
		chip8->V[0xF] = 0;
	chip8->V[nibble.x] = result & 0xFF;
	return (0);
}

uint8_t	shr_VY_to_VX_carry(t_Chip8 *chip8, t_nibble nibble)
{
	int16_t	result;

	chip8->V[0xF] = chip8->V[nibble.x] & 0x1;
	result = chip8->V[nibble.x] >> 0x1;

	chip8->V[nibble.x] = result & 0xFF;
	return (0);
}

uint8_t	subn_VY_to_VX_carry(t_Chip8 *chip8, t_nibble nibble)
{
	int16_t	result;

	result = chip8->V[nibble.x] - chip8->V[nibble.y];

	if (result >= 0x0)
		chip8->V[0xF] = 1;
	else
		chip8->V[0xF] = 0;
	chip8->V[nibble.x] = result & 0xFF;
	return (0);
}

uint8_t	shl_VY_to_VX_carry(t_Chip8 *chip8, t_nibble nibble)
{
	int16_t	result;

	chip8->V[0xF] = (chip8->V[nibble.x] >> 7) & 0x1;
	result = chip8->V[nibble.x] << 0x1;

	chip8->V[nibble.x] = result & 0xFF;
	return (0);
}

uint8_t set_VX_rnd_and_NN(t_Chip8 *chip8, t_nibble nibble)
{
	chip8->V[nibble.x] = (rand() % 256) & nibble.nn;
	return (0);
}
