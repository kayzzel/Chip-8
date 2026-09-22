#include "chip_8.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;

static void reset_terminal_mode()
{
    tcsetattr(0, TCSANOW, &orig_termios);
}

void set_conio_terminal_mode()
{
    struct termios new_termios;

    /* take two copies - one for now, one for later */
    tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));

    /* register cleanup handler, and set the new terminal mode */
    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
}

static int kbhit()
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv) > 0;
}

static int getch()
{
    int r;
    unsigned char c;
    if ((r = read(0, &c, sizeof(c))) < 0) {
        return r;
    } else {
        return c;
    }
}

int poll_keypad_input(t_Chip8 *chip_8)
{
    int char_read;

    memset(chip_8->keypad, 0, 16 * sizeof(uint8_t));

    while (kbhit())
    {
        char_read = getch();
        switch (char_read) {
            case 27: return (1); // Esc quits

			case '1': chip_8->keypad[0x1] = 1; break;
			case '2': chip_8->keypad[0x2] = 1; break;
			case '3': chip_8->keypad[0x3] = 1; break;
			case '4': chip_8->keypad[0xC] = 1; break;

			case 'q': chip_8->keypad[0x4] = 1; break;
			case 'w': chip_8->keypad[0x5] = 1; break;
			case 'e': chip_8->keypad[0x6] = 1; break;
			case 'r': chip_8->keypad[0xD] = 1; break;

			case 'a': chip_8->keypad[0x7] = 1; break;
			case 's': chip_8->keypad[0x8] = 1; break;
			case 'd': chip_8->keypad[0x9] = 1; break;
			case 'f': chip_8->keypad[0xE] = 1; break;

			case 'z': chip_8->keypad[0xA] = 1; break;
			case 'x': chip_8->keypad[0x0] = 1; break;
			case 'c': chip_8->keypad[0xB] = 1; break;
			case 'v': chip_8->keypad[0xF] = 1; break;
        }
    }
    return (0);
}
