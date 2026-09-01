#include "chip_8.h"
#include "opcode.h"
#include "utils.h"

#include <stdint.h>
#include <stdlib.h>
#include <sys/select.h>

int main_loop(t_Chip8 *chip8)
{
	t_nibble nibble;

	while (1)
	{
		nibble = fetch_nibble(chip8->pc, chip8->memory);
		chip8->pc += 2;
		select_opcode(nibble);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_Chip8	*chip8;

	// look if there is only a filename as an arg
	if (argc != 2)
		return (1);

	// allocat memory for the main struct
	chip8 = calloc(1, sizeof(t_Chip8));
	if (chip8 == NULL)
		return (1);

	// load everything needed in memory
	load_font(chip8);
	if (load_rom(argv[1], chip8))
	{
		printError(chip8->error_message);
		free(chip8);
		return (1);
	}
	
	chip8->pc = 0x200;
	if (main_loop(chip8))
	{
		printError(chip8->error_message);
		free(chip8);
		return (1);
	}

	free(chip8);
	return (0);
}
