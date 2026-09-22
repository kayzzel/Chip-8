#include "opcode.h"
#include "chip_8.h"

#include <stdint.h>

uint8_t	jump_to_NNN(t_Chip8 *chip8, t_nibble nibble)
{
	if (nibble.nnn % 2 != 0)
	{
		chip8->error_message = "The jump adress must be an even number";
		return (1);
	}

	chip8->pc = nibble.nnn;
	return (0);
}

uint8_t	call_NNN(t_Chip8 *chip8, t_nibble nibble)
{
	if (nibble.nnn % 2 != 0)
	{
		chip8->error_message = "The call adress must be an even number";
		return (1);
	}

	if (chip8->sp >= 16)
	{
		chip8->error_message = "No more space in the stack for function call";
		return (1);
	}

	chip8->stack[chip8->sp] = chip8->pc;
	chip8->sp++;
	chip8->pc = nibble.nnn;

	return (0);
}

uint8_t	ret_from_subroutine(t_Chip8 *chip8)
{
	if (chip8->sp == 0)
	{
		chip8->error_message = "No address in the stack to return to";
		return (1);
	}

	chip8->sp--;
	chip8->pc = chip8->stack[chip8->sp];

	return (0);
}

uint8_t	jump_to_NNN_plus_V0(t_Chip8 *chip8, t_nibble nibble)
{
	if ((nibble.nnn + chip8->V[0x0]) >= MEMORY_SIZE)
	{
		chip8->error_message = "Adress to jump is out of the memory plage";
		return (1);
	}

	if ((nibble.nnn + chip8->V[0x0]) % 2 != 0)
	{
		chip8->error_message = "The jump adress must be an even number";
		return (1);
	}

	chip8->pc = nibble.nnn + chip8->V[0x0];
	return (0);
}

uint8_t	skip_if_VX_equal_NN(t_Chip8 *chip8, t_nibble nibble)
{
	if (chip8->V[nibble.x] == nibble.nn)
		chip8->pc += 2;
	return (0);
}

uint8_t	skip_if_VX_not_equal_NN(t_Chip8 *chip8, t_nibble nibble)
{
	if (chip8->V[nibble.x] != nibble.nn)
		chip8->pc += 2;
	return (0);
}

uint8_t	skip_if_VX_equal_VY(t_Chip8 *chip8, t_nibble nibble)
{
	if (chip8->V[nibble.x] == chip8->V[nibble.y])
		chip8->pc += 2;
	return (0);
}


uint8_t	skip_if_VX_not_equal_VY(t_Chip8 *chip8, t_nibble nibble)
{
	if (chip8->V[nibble.x] != chip8->V[nibble.y])
		chip8->pc += 2;
	return (0);
}
