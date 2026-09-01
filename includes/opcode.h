#ifndef OPCODE_H
# define OPCODE_H

// INCLUDES

# include <stdint.h>

// STRUCTS

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


#endif
