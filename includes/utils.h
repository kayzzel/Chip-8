// INCLUDES

# include "chip_8.h"

# include <stdint.h>

// FUNCS

void	putstr(char *str);
void 	putline(char *str);
void 	printError(char *err);

uint8_t	*get_file_content(char *filename, t_Chip8 *chip8);

long	get_time_usec(void);
void	init_time(void);
void	set_wait_start(long usec);
void	wait_time(void);
