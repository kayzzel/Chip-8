# CHIP-8 Reference

Everything needed to implement a CHIP-8 interpreter in C: memory layout, registers, the full opcode table, font data, timing, and common pitfalls.

## 1. Overview

CHIP-8 is an interpreted virtual machine from the mid-1970s, originally built to make writing simple games easier on 8-bit microcomputers. It's not real hardware — you're implementing an interpreter, not emulating a physical CPU. That makes it forgiving: no clock-accurate timing, no undocumented quirks (mostly), and a small, closed instruction set (~35 opcodes).

## 2. Memory Layout

- **Size**: 4096 bytes (4KB), addresses `0x000`–`0xFFF`
- `0x000`–`0x1FF`: reserved. Originally held the interpreter itself. By convention, the built-in font set is stored here (commonly starting at `0x050`).
- `0x200`–`0xFFF`: program space. ROMs are loaded starting at `0x200`. (Some ETI-660 era programs started at `0x600`, but `0x200` is the standard for almost everything you'll test with.)

```c
uint8_t memory[4096];
```

## 3. Registers

| Register | Size | Purpose |
|---|---|---|
| `V0`–`VF` | 8-bit each | 16 general-purpose registers. `VF` is also used as a flag (carry, borrow, collision) by several instructions — don't rely on its value being preserved. |
| `I` | 16-bit | Index register, generally holds a memory address (e.g. pointer to sprite data). |
| `PC` | 16-bit | Program counter. Starts at `0x200`. |
| `SP` | 8-bit | Stack pointer. |
| Stack | 16 x 16-bit | Stores return addresses for subroutine calls. 16 levels is the traditional limit. |
| `DT` | 8-bit | Delay timer. Decrements at 60Hz when nonzero. General purpose (used for game timing). |
| `ST` | 8-bit | Sound timer. Decrements at 60Hz when nonzero. Should trigger a beep while nonzero (optional to implement). |

## 4. Display

- **Resolution**: 64 x 32 pixels, monochrome (on/off).
- Represent as a separate buffer, **not** part of `memory[]`:
  ```c
  uint8_t display[64 * 32]; // one byte per pixel for simplicity
  ```
- Drawing is XOR-based: sprites are XORed onto the screen. If any pixel goes from set to unset as a result, `VF` is set to 1 (this is how collision detection works), otherwise `VF` is set to 0.
- Sprites are always 8 pixels wide (1 byte = 1 row, MSB first) and 1–15 pixels tall.
- Coordinates wrap around screen edges.
- Original CHIP-8 clears the screen (`00E0`) to start; nothing is drawn until the program says so.

## 5. Keypad

16 keys, labeled `0`–`F`, originally laid out as:

```
1 2 3 C
4 5 6 D
7 8 9 E
A 0 B F
```

Common modern keyboard mapping:

```
1 2 3 4        1 2 3 C
q w e r   ->   4 5 6 D
a s d f        7 8 9 E
z x c v        A 0 B F
```

Track state as `uint8_t keypad[16]` (pressed = 1). Two opcodes check it directly (`EX9E`, `EXA1`), and one (`FX0A`) blocks execution until a key is pressed.

## 6. Font Set

CHIP-8 programs expect a built-in hex font (characters `0`–`F`), 5 bytes each, representing a 4x5 pixel sprite. Load this into memory at startup (conventionally at `0x050`):

```c
uint8_t fontset[80] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};
```

`FX29` points `I` at the sprite for the hex digit in `VX`, using this table.

## 7. Instruction Format

- All opcodes are **2 bytes**, stored big-endian.
- Fetch: `opcode = (memory[pc] << 8) | memory[pc + 1]`
- Increment `pc` by 2 *before* executing (so jump/call opcodes can safely overwrite it).
- Decode by nibbles. Common notation used in opcode tables:
  - `N` — a 4-bit constant
  - `NN` — an 8-bit constant
  - `NNN` — a 12-bit address
  - `X`, `Y` — register indices (each a nibble)

## 8. Opcode Table

| Opcode | Mnemonic | Description |
|---|---|---|
| `00E0` | `CLS` | Clear the display. |
| `00EE` | `RET` | Return from subroutine: pop address from stack into `PC`. |
| `1NNN` | `JP NNN` | Jump to address `NNN`. |
| `2NNN` | `CALL NNN` | Push current `PC` onto stack, call subroutine at `NNN`. |
| `3XNN` | `SE VX, NN` | Skip next instruction if `VX == NN`. |
| `4XNN` | `SNE VX, NN` | Skip next instruction if `VX != NN`. |
| `5XY0` | `SE VX, VY` | Skip next instruction if `VX == VY`. |
| `6XNN` | `LD VX, NN` | Set `VX = NN`. |
| `7XNN` | `ADD VX, NN` | Set `VX = VX + NN` (no carry flag affected). |
| `8XY0` | `LD VX, VY` | Set `VX = VY`. |
| `8XY1` | `OR VX, VY` | Set `VX = VX \| VY`. |
| `8XY2` | `AND VX, VY` | Set `VX = VX & VY`. |
| `8XY3` | `XOR VX, VY` | Set `VX = VX ^ VY`. |
| `8XY4` | `ADD VX, VY` | `VX += VY`; `VF = 1` if carry, else `0`. |
| `8XY5` | `SUB VX, VY` | `VX -= VY`; `VF = 1` if `VX >= VY` (no borrow), else `0`. |
| `8XY6` | `SHR VX` | `VF = VX & 0x1`; `VX >>= 1`. (See quirks section — behavior varies by implementation.) |
| `8XY7` | `SUBN VX, VY` | `VX = VY - VX`; `VF = 1` if `VY >= VX`, else `0`. |
| `8XYE` | `SHL VX` | `VF = (VX >> 7) & 0x1`; `VX <<= 1`. (See quirks.) |
| `9XY0` | `SNE VX, VY` | Skip next instruction if `VX != VY`. |
| `ANNN` | `LD I, NNN` | Set `I = NNN`. |
| `BNNN` | `JP V0, NNN` | Jump to `NNN + V0`. |
| `CXNN` | `RND VX, NN` | Set `VX = random_byte() & NN`. |
| `DXYN` | `DRW VX, VY, N` | Draw N-byte sprite starting at address `I` at position `(VX, VY)`; `VF = 1` if any pixel collision. |
| `EX9E` | `SKP VX` | Skip next instruction if key in `VX` is pressed. |
| `EXA1` | `SKNP VX` | Skip next instruction if key in `VX` is **not** pressed. |
| `FX07` | `LD VX, DT` | Set `VX = delay timer`. |
| `FX0A` | `LD VX, K` | Wait for a key press, store key value in `VX` (blocking). |
| `FX15` | `LD DT, VX` | Set delay timer `= VX`. |
| `FX18` | `LD ST, VX` | Set sound timer `= VX`. |
| `FX1E` | `ADD I, VX` | `I += VX`. |
| `FX29` | `LD F, VX` | Set `I` to the address of the font sprite for digit `VX`. |
| `FX33` | `LD B, VX` | Store BCD representation of `VX` in memory at `I`, `I+1`, `I+2` (hundreds, tens, ones). |
| `FX55` | `LD [I], VX` | Store registers `V0` through `VX` into memory starting at `I`. |
| `FX65` | `LD VX, [I]` | Read registers `V0` through `VX` from memory starting at `I`. |

## 9. Main Loop Structure

```
load font into memory
load ROM into memory starting at 0x200
set pc = 0x200

loop:
    opcode = fetch(pc)
    pc += 2
    decode and execute opcode
    if 60Hz tick has elapsed:
        if delay_timer > 0: delay_timer--
        if sound_timer > 0: sound_timer--
    render display if it changed
    poll keypad input
```

CPU instruction speed and the 60Hz timer speed are **decoupled** in real implementations — instructions typically run much faster than 60Hz (roughly 500-700 instructions/sec is a common target), while timers always tick at 60Hz regardless. A simple approach: run several instructions per frame, then decrement timers once per frame at ~60Hz.

## 10. Known Ambiguities / Quirks

Different original interpreters (and later CHIP-8 variants like SUPER-CHIP) disagree on a few behaviors. These cause the most "why doesn't this ROM work" confusion:

- **`8XY6` / `8XYE` (shift instructions)**: original COSMAC VIP behavior shifts `VY` and stores into `VX`. Many later interpreters (and most test ROMs) just shift `VX` in place, ignoring `VY`. Pick one; if a ROM behaves oddly, try the other.
- **`BNNN` (jump with offset)**: original behavior is `PC = NNN + V0`. Some SUPER-CHIP-influenced interpreters use `PC = NNN + VX` (using the top nibble of NNN as the register index). Stick with the `V0` version for classic ROMs.
- **`FX55` / `FX65` (register load/store)**: on the original interpreter, `I` itself is incremented as a side effect during the operation. Many modern implementations leave `I` unchanged. Either is fine unless a ROM specifically depends on it.
- **`DXYN` clipping vs wrapping**: original behavior clips sprites at the screen edge (pixels off-screen are simply not drawn); some implementations wrap around instead. Clipping is the more common default.

If you hit weird behavior on a specific ROM, these four are the first things to check.

## 11. Test ROMs (public domain, good for verification)

- **IBM Logo** — draws a static logo. Exercises only `00E0`, `1NNN`, `6XNN`, `ANNN`, `DXYN`. Best first target — if this renders correctly, your fetch/decode loop and draw instruction are solid.
- **Chip8 test suite ROMs** (widely available, e.g. Timendus's `chip8-test-suite`) — checks opcodes, quirks, and keypad handling individually with pass/fail output on screen.
- **Pong, Tetris, Space Invaders** — classic playable ROMs, good end-to-end tests once the basics work.

## 12. Build Notes (macOS, terminal-only)

```bash
clang -o chip8 main.c -Wall -Wextra
./chip8 roms/IBM_Logo.ch8
```

Terminal rendering avoids any external dependency (no SDL2 needed):

```c
void draw_screen(uint8_t display[64*32]) {
    printf("\x1b[H"); // cursor to top-left, avoids full-clear flicker
    for (int y = 0; y < 32; y++) {
        for (int x = 0; x < 64; x++)
            putchar(display[y*64+x] ? '#' : ' ');
        putchar('\n');
    }
}
```

## 13. Reference Links

- Cowgod's Chip-8 Technical Reference — the de facto canonical opcode spec most implementers use.
- Timendus's `chip8-test-suite` on GitHub — automated ROM tests covering opcodes and quirks.
- `awesome-chip-8` on GitHub — curated list of ROMs, docs, and implementations for comparison.
