#ifndef OPCODE_H
# define OPCODE_H

// INCLUDES

# include <stdint.h>

// STRUCTS

typedef struct s_Chip8 t_Chip8;

typedef struct s_nibble
{
	uint16_t	opcode;
	uint8_t		t;
	uint8_t		x;
	uint8_t		y;
	uint8_t		n;
	uint8_t		nn;
	uint16_t	nnn;
} t_nibble;

// FUNCS

uint8_t	exec_opcode(t_nibble nibble, t_Chip8 *chip8);

	// flow
uint8_t	jump_to_NNN(t_Chip8 *chip8, t_nibble nibble);
uint8_t	call_NNN(t_Chip8 *chip8, t_nibble nibble);
uint8_t ret_from_subroutine(t_Chip8 *chip8);
uint8_t	jump_to_NNN_plus_V0(t_Chip8 *chip8, t_nibble nibble);
uint8_t	skip_if_VX_equal_NN(t_Chip8 *chip8, t_nibble nibble);
uint8_t	skip_if_VX_not_equal_NN(t_Chip8 *chip8, t_nibble nibble);
uint8_t	skip_if_VX_equal_VY(t_Chip8 *chip8, t_nibble nibble);
uint8_t	skip_if_VX_not_equal_VY(t_Chip8 *chip8, t_nibble nibble);

	// register
uint8_t	set_VX_to_NN(t_Chip8 *chip8, t_nibble nibble);
uint8_t	add_NN_TO_VX(t_Chip8 *chip8, t_nibble nibble);
uint8_t	set_VY_to_VX(t_Chip8 *chip8, t_nibble nibble);
uint8_t or_XY_to_VX(t_Chip8 *chip8, t_nibble nibble);
uint8_t and_XY_to_VX(t_Chip8 *chip8, t_nibble nibble);
uint8_t xor_XY_to_VX(t_Chip8 *chip8, t_nibble nibble);
uint8_t	add_VY_to_VX_carry(t_Chip8 *chip8, t_nibble nibble);
uint8_t	sub_VY_to_VX_carry(t_Chip8 *chip8, t_nibble nibble);
uint8_t	shr_VY_to_VX_carry(t_Chip8 *chip8, t_nibble nibble);
uint8_t	subn_VY_to_VX_carry(t_Chip8 *chip8, t_nibble nibble);
uint8_t	shl_VY_to_VX_carry(t_Chip8 *chip8, t_nibble nibble);
uint8_t set_VX_rnd_and_NN(t_Chip8 *chip8, t_nibble nibble);

	// memory
uint8_t	set_I_to_NNN(t_Chip8 *chip8, t_nibble nibble);
uint8_t	add_VX_to_I(t_Chip8 *chip8, t_nibble nibble);
uint8_t set_I_to_VX_font(t_Chip8 *chip8, t_nibble nibble);
uint8_t store_VX_BCD(t_Chip8 *chip8, t_nibble nibble);
uint8_t store_registers_in_memory(t_Chip8 *chip8, t_nibble nibble);
uint8_t get_registers_from_memory(t_Chip8 *chip8, t_nibble nibble);


	// display
uint8_t	clear_screen(t_Chip8 *chip8);
uint8_t	draw_sprite(t_Chip8 *chip8, t_nibble nibble);

	// keypad
uint8_t	skip_if_VX_pressed(t_Chip8 *chip8, t_nibble nibble);
uint8_t	skip_if_VX_not_pressed(t_Chip8 *chip8, t_nibble nibble);
uint8_t	wait_VX_press(t_Chip8 *chip8, t_nibble nibble);

	// timer
uint8_t	set_VX_to_delay_timer(t_Chip8 *chip8, t_nibble nibble);
uint8_t	set_delay_timer_to_VX(t_Chip8 *chip8, t_nibble nibble);
uint8_t	set_sound_timer_to_VX(t_Chip8 *chip8, t_nibble nibble);

#endif
