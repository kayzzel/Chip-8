#include "utils.h"

#include <unistd.h>

void	putstr(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		write(1, &str[index], 1);
		index++;
	}
}
void putline(char *str)
{
	putstr(str);
	write(1, "\n", 1);
}

void printError(char *err)
{
	int	index;

	index = 0;
	while (err[index] != '\0')
	{
		write(2, &err[index], 1);
		index++;
	}
}
