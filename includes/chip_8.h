#ifndef CHIP_8_H
# define CHIP_8_H

// INCLUDES

# include "opcode.h"

# include <stdint.h>

// CONST

# define MEMORY_SIZE 4096
# define ROM_OFFSET 0x200

# define SCREEN_WIDTH 64
# define SCREEN_HEIGHT 32
#define TARGET_FPS 60

#define US_PER_FRAME (1000000L / TARGET_FPS)
#define INSTRUCTIONS_PER_FRAME 10

// STRUCTS

typedef struct s_Chip8
{
    uint8_t memory[MEMORY_SIZE];
    uint8_t V[16];
    uint16_t I;
    uint16_t pc;
    uint16_t stack[16];
    uint8_t sp;
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint8_t display[SCREEN_HEIGHT * SCREEN_WIDTH];   // separate from memory — 0 or 1 per pixel
    uint8_t keypad[16];
	char *error_message;
} t_Chip8;

// FUNCS

uint8_t		load_rom(char *filename, t_Chip8 *chip8);
void		load_font(t_Chip8 *chip8);

t_nibble	load_nibble(uint16_t opcode);
t_nibble	fetch_nibble(uint16_t pc, uint8_t memory[MEMORY_SIZE]);

int aff_screen(const uint8_t screen[SCREEN_HEIGHT * SCREEN_WIDTH]);

void poll_keypad_input(t_Chip8 *chip_8);
void set_conio_terminal_mode();

#endif
