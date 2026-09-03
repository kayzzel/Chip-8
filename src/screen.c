#include "chip_8.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

static uint8_t did_screen_changed(const uint8_t current_screen[SCREEN_HEIGHT * SCREEN_WIDTH])
{
	static uint8_t previous_screen[SCREEN_HEIGHT * SCREEN_WIDTH];
    static bool first_run = true;

    if (first_run) {
        memcpy(previous_screen, current_screen, SCREEN_HEIGHT * SCREEN_WIDTH);
        first_run = false;
        return 1;
    }

    if (memcmp(current_screen, previous_screen, SCREEN_HEIGHT * SCREEN_WIDTH) != 0) {
        memcpy(previous_screen, current_screen, SCREEN_HEIGHT * SCREEN_WIDTH);
        return 1;
    }

    return 0;
}

int aff_screen(const uint8_t screen[SCREEN_HEIGHT * SCREEN_WIDTH])
{
    if (!did_screen_changed(screen))
        return (0);

    // 1. Move cursor to top-left corner
    write(1, "\x1b[H", 3);

    // 2. Draw Top Border (╔═════════════╗)
    fputs("╔", stdout);
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        fputs("═", stdout);
    }
    fputs("╗\n", stdout);

    // 3. Draw Screen Content with Side Borders (║ █ ║)
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        fputs("║", stdout); // Left border
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            // Uses solid block '█' for 1, space ' ' for 0
            fputs(screen[y * SCREEN_WIDTH + x] ? "█" : " ", stdout);
        }
        fputs("║\n", stdout); // Right border
    }

    // 4. Draw Bottom Border (╚═════════════╝)
    fputs("╚", stdout);
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        fputs("═", stdout);
    }
    fputs("╝\n", stdout);

    // Flush stream to draw everything in a single pass (prevents flicker)
    fflush(stdout);

    return (0);
}
