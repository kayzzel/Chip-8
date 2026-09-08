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
