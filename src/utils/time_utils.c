#include "utils.h"

#include <stdbool.h>
#include <sys/time.h>
#include <unistd.h>

long	get_time_usec(void)
{
	static int		start_time = -1;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (start_time == -1)
		start_time = tv.tv_sec * 1000000 + tv.tv_usec;
	return ((tv.tv_sec * 1000000 + tv.tv_usec) - start_time);
}

static void	precise_usleep(long usec, bool start)
{
	static long	time_goal;

	if (start)
	{
		time_goal = get_time_usec() + usec;
		return;
	}
	while (time_goal > get_time_usec())
	{
		usleep(100);
	}
	return ;
}

void	init_time(void)
{
	get_time_usec();
}

void	set_wait_start(long usec)
{
	precise_usleep(usec, true);
}

void	wait_time(void)
{
	precise_usleep(0, false);
}

