#include "opcode.h"

#include <stdint.h>

static uint8_t	select_opcode_8(t_nibble nibble)
{
	if (nibble.n == 0)
		return (2); // 8XY0 | LD VX, VY - set VX = VY
	else if (nibble.n == 1)
		return (2); // 8XY1 | OR VX, VY - set VX = VX | VY
	else if (nibble.n == 2)
		return (2); // 8XY2 | AND VX, VY - set VX = VX & VY
	else if (nibble.n == 3)
		return (2); // 8XY3 | XOR VX, VY - set VX = VX ^ VY
	else if (nibble.n == 4)
		return (2); // 8XY4 | ADD VX, VY - VX += VY, VF = carry
	else if (nibble.n == 5)
		return (2); // 8XY5 | SUB VX, VY - VX -= VY, VF = 1 if no borrow
	else if (nibble.n == 6)
		return (2); // 8XY6 | SHR VX - VF = VX & 0x1, VX >>= 1
	else if (nibble.n == 7)
		return (2); // 8XY7 | SUBN VX, VY - VX = VY - VX, VF = 1 if no borrow
	else if (nibble.n == 0xE)
		return (2); // 8XYE | SHL VX - VF = (VX >> 7) & 0x1, VX <<= 1
	return (1);
}

static uint8_t	select_opcode_ex(t_nibble nibble)
{
	if (nibble.nn == 0x9E)
		return (2); // EX9E | SKP VX - skip if key VX pressed
	else if (nibble.nn == 0xA1)
		return (2); // EXA1 | SKNP VX - skip if key VX not pressed
	return (1);
}

static uint8_t	select_opcode_fx(t_nibble nibble)
{
	if (nibble.nn == 0x07)
		return (2); // FX07 | LD VX, DT - VX = delay timer
	else if (nibble.nn == 0x0A)
		return (2); // FX0A | LD VX, K - wait for key press
	else if (nibble.nn == 0x15)
		return (2); // FX15 | LD DT, VX - delay timer = VX
	else if (nibble.nn == 0x18)
		return (2); // FX18 | LD ST, VX - sound timer = VX
	else if (nibble.nn == 0x1E)
		return (2); // FX1E | ADD I, VX - I += VX
	else if (nibble.nn == 0x29)
		return (2); // FX29 | LD F, VX - I = font sprite addr
	else if (nibble.nn == 0x33)
		return (2); // FX33 | LD B, VX - store BCD at I
	else if (nibble.nn == 0x55)
		return (2); // FX55 | LD [I], VX - store V0..VX in memory
	else if (nibble.nn == 0x65)
		return (2); // FX65 | LD VX, [I] - load V0..VX from memory
	return (1);
}

uint8_t	exec_opcode(t_nibble nibble)
{
	if (nibble.opcode == 0x00E0)
		return (2); // 00E0 | CLS - clear screen
	else if (nibble.opcode == 0x00EE)
		return (2); // 00EE | RET - return from subroutine
	else if (nibble.t == 1)
		return (2); // 1NNN | JP NNN - jump to address NNN
	else if (nibble.t == 2)
		return (2); // 2NNN | CALL NNN - call subroutine at NNN
	else if (nibble.t == 3)
		return (2); // 3XNN | SE VX, NN - skip if VX == NN
	else if (nibble.t == 4)
		return (2); // 4XNN | SNE VX, NN - skip if VX != NN
	else if (nibble.t == 5 && nibble.n == 0)
		return (2); // 5XY0 | SE VX, VY - skip if VX == VY
	else if (nibble.t == 6)
		return (2); // 6XNN | LD VX, NN - set VX = NN
	else if (nibble.t == 7)
		return (2); // 7XNN | ADD VX, NN - VX += NN
	else if (nibble.t == 8)
		return (select_opcode_8(nibble)); // 8XY_ | ALU ops
	else if (nibble.t == 9 && nibble.n == 0)
		return (2); // 9XY0 | SNE VX, VY - skip if VX != VY
	else if (nibble.t == 0xA)
		return (2); // ANNN | LD I, NNN - set I = NNN
	else if (nibble.t == 0xB)
		return (2); // BNNN | JP V0, NNN - jump to NNN + V0
	else if (nibble.t == 0xC)
		return (2); // CXNN | RND VX, NN - VX = random & NN
	else if (nibble.t == 0xD)
		return (2); // DXYN | DRW VX, VY, N - draw sprite
	else if (nibble.t == 0xE)
		return (select_opcode_ex(nibble)); // EX9E/EXA1 | key skip
	else if (nibble.t == 0xF)
		return (select_opcode_fx(nibble)); // FX__ | timer/key/mem ops
	return (1);
}
