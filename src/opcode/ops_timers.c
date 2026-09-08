#include "chip_8.h"
#include "opcode.h"

#include <stdint.h>

uint8_t	set_VX_to_delay_timer(t_Chip8 *chip8, t_nibble nibble)
{
	chip8->V[nibble.x] = chip8->delay_timer;
	return (0);
}

uint8_t	set_delay_timer_to_VX(t_Chip8 *chip8, t_nibble nibble)
{
	chip8->delay_timer = chip8->V[nibble.x];
	return (0);
}

uint8_t	set_sound_timer_to_VX(t_Chip8 *chip8, t_nibble nibble)
{
	chip8->sound_timer = chip8->V[nibble.x];
	return (0);
}
