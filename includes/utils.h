// INCLUDES

# include "chip_8.h"

# include <stdint.h>

// FUNCS

void	putstr(char *str);
void putline(char *str);
void printError(char *err);

uint8_t	*get_file_content(char *filename, t_Chip8 *chip8);
