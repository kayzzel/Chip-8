#include "chip_8.h"
#include "utils.h"

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

uint8_t	*get_file_content(char *filename, t_Chip8 *chip8)
{
	uint8_t *content;
	int 	char_read;
	int 	fd;

	content = malloc(sizeof(uint8_t) * MEMORY_SIZE - 200 + 2);
	if (content == NULL)
	{
		chip8->error_message = "Error during the memory allocation";
		return (NULL);
	}

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free(content);
		chip8->error_message = "couldn't open the file given";
		return (NULL);
	}

	char_read = read(fd, content, MEMORY_SIZE - 200 + 2);
	if (char_read > MEMORY_SIZE - 200)
	{
		free(content);
		chip8->error_message = "Content of the file to large for the memory";
		return (NULL);
	}

	content[char_read] = '\0';
	return (content);
}
