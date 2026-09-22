#include "opcode.h"
#include "chip_8.h"

#include <stdint.h>

uint8_t	set_I_to_NNN(t_Chip8 *chip8, t_nibble nibble)
{
	chip8->I = nibble.nnn;
	return (0);
}

uint8_t	add_VX_to_I(t_Chip8 *chip8, t_nibble nibble)
{
	chip8->I += chip8->V[nibble.x];
	return (0);
}

uint8_t set_I_to_VX_font(t_Chip8 *chip8, t_nibble nibble)
{
	chip8->I = 5 * chip8->V[nibble.x];
	return (0);
}

uint8_t store_VX_BCD(t_Chip8 *chip8, t_nibble nibble)
{
	if (chip8->I + 2 >= MEMORY_SIZE)
	{
		chip8->error_message = "I is to close to the memory end to store the BCD representation";
		return (1);
	}

	chip8->memory[chip8->I] = chip8->V[nibble.x] / 100;
	chip8->memory[chip8->I + 1] = chip8->V[nibble.x] / 10 % 10;
	chip8->memory[chip8->I + 2] = chip8->V[nibble.x] % 10;
	return (0);
}

uint8_t store_registers_in_memory(t_Chip8 *chip8, t_nibble nibble)
{
	uint8_t register_index;

	if (chip8->I + nibble.x >= MEMORY_SIZE)
	{
		chip8->error_message = "I is to close to the memory end to store all the registers";
		return (1);
	}

	register_index = 0;
	while (register_index <= nibble.x)
	{
		chip8->memory[chip8->I + register_index] = chip8->V[register_index];
		register_index++;
	}
	return (0);
}

uint8_t get_registers_from_memory(t_Chip8 *chip8, t_nibble nibble)
{
	uint8_t register_index;

	if (chip8->I + nibble.x >= MEMORY_SIZE)
	{
		chip8->error_message = "I is to close to the memory end to get all the registers";
		return (1);
	}

	register_index = 0;
	while (register_index <= nibble.x)
	{
		chip8->V[register_index] = chip8->memory[chip8->I + register_index];
		register_index++;
	}
	return (0);
}
