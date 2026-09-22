#include "chip_8.h"
#include "opcode.h"

#include <iso646.h>
#include <stdint.h>

static uint8_t	select_opcode_8(t_nibble nibble, t_Chip8 *chip8)
{
	if (nibble.n == 0)
		return (set_VY_to_VX(chip8, nibble));
	else if (nibble.n == 1)
		return (or_XY_to_VX(chip8, nibble));
	else if (nibble.n == 2)
		return (and_XY_to_VX(chip8, nibble));
	else if (nibble.n == 3)
		return (xor_XY_to_VX(chip8, nibble));
	else if (nibble.n == 4)
		return (add_VY_to_VX_carry(chip8, nibble));
	else if (nibble.n == 5)
		return (sub_VY_to_VX_carry(chip8, nibble));
	else if (nibble.n == 6)
		return (shr_VY_to_VX_carry(chip8, nibble));
	else if (nibble.n == 7)
		return (subn_VY_to_VX_carry(chip8, nibble));
	else if (nibble.n == 0xE)
		return (shl_VY_to_VX_carry(chip8, nibble));
	return (1);
}

static uint8_t	select_opcode_ex(t_nibble nibble, t_Chip8 *chip8)
{
	if (nibble.nn == 0x9E)
		return (skip_if_VX_pressed(chip8, nibble));
	else if (nibble.nn == 0xA1)
		return (skip_if_VX_not_pressed(chip8, nibble));
	return (1);
}

static uint8_t	select_opcode_fx(t_nibble nibble, t_Chip8 *chip8)
{
	if (nibble.nn == 0x07)
		return (set_VX_to_delay_timer(chip8, nibble));
	else if (nibble.nn == 0x0A)
		return (wait_VX_press(chip8, nibble));
	else if (nibble.nn == 0x15)
		return (set_delay_timer_to_VX(chip8, nibble));
	else if (nibble.nn == 0x18)
		return (set_sound_timer_to_VX(chip8, nibble));
	else if (nibble.nn == 0x1E)
		return (add_VX_to_I(chip8, nibble));
	else if (nibble.nn == 0x29)
		return (set_I_to_VX_font(chip8, nibble));
	else if (nibble.nn == 0x33)
		return (store_VX_BCD(chip8, nibble));
	else if (nibble.nn == 0x55)
		return (store_registers_in_memory(chip8, nibble));
	else if (nibble.nn == 0x65)
		return (get_registers_from_memory(chip8, nibble));
	return (1);
}

uint8_t	exec_opcode(t_nibble nibble, t_Chip8 *chip8)
{
	(void)chip8;
	if (nibble.opcode == 0x00E0)
		return (clear_screen(chip8));
	else if (nibble.opcode == 0x00EE)
		return (ret_from_subroutine(chip8));
	else if (nibble.t == 1)
		return (jump_to_NNN(chip8, nibble));
	else if (nibble.t == 2)
		return (call_NNN(chip8, nibble));
	else if (nibble.t == 3)
		return (skip_if_VX_equal_NN(chip8, nibble));
	else if (nibble.t == 4)
		return (skip_if_VX_not_equal_NN(chip8, nibble));
	else if (nibble.t == 5 && nibble.n == 0)
		return (skip_if_VX_equal_VY(chip8, nibble));
	else if (nibble.t == 6)
		return (set_VX_to_NN(chip8, nibble));
	else if (nibble.t == 7)
		return (add_NN_TO_VX(chip8, nibble));
	else if (nibble.t == 8)
		return (select_opcode_8(nibble, chip8));
	else if (nibble.t == 9 && nibble.n == 0)
		return (skip_if_VX_not_equal_VY(chip8, nibble));
	else if (nibble.t == 0xA)
		return (set_I_to_NNN(chip8, nibble));
	else if (nibble.t == 0xB)
		return (jump_to_NNN_plus_V0(chip8, nibble));
	else if (nibble.t == 0xC)
		return (set_VX_rnd_and_NN(chip8, nibble));
	else if (nibble.t == 0xD)
		return (draw_sprite(chip8, nibble));
	else if (nibble.t == 0xE)
		return (select_opcode_ex(nibble, chip8));
	else if (nibble.t == 0xF)
		return (select_opcode_fx(nibble, chip8));
	return (1);
}
