#include "chip_8.h"
#include "opcode.h"
#include "utils.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>

int main_loop(t_Chip8 *chip8)
{
	bool		running;
	t_nibble	nibble;
	long		last_time;
	long		elapsed_time;

	init_time();

	last_time = get_time_usec();
	running = true;
	set_conio_terminal_mode();
	while (running)
	{
		for (int i = 0; i < INSTRUCTIONS_PER_FRAME; i++)
		{
			nibble = fetch_nibble(chip8->pc, chip8->memory);
			chip8->pc += 2;
			if (exec_opcode(nibble))
				return (1);
		}

		elapsed_time = get_time_usec() - last_time ;
		if (elapsed_time >= US_PER_FRAME)
		{
			if (chip8->delay_timer > 0) chip8->delay_timer--;
			if (chip8->sound_timer > 0) chip8->sound_timer--;

			last_time = get_time_usec();

			aff_screen(chip8->display);
			poll_keypad_input(chip8);
		}
		else
			usleep(US_PER_FRAME - elapsed_time);
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
