#include "phylo.h"

size_t	time_now()
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void ft_sleep(unsigned int i) //принимает микросекунды
{
	struct 	timeval tv1, tv2;
	size_t 	time;
	size_t	wake_up_time;
    
	gettimeofday(&tv1, NULL);
    wake_up_time = tv1.tv_sec * 1000 + tv1.tv_usec / 1000 + i;
	usleep(i * 0.9);
	while(1)
	{
		gettimeofday(&tv1, NULL);
		time = tv1.tv_sec * 1000 + tv1.tv_usec / 1000;
		if (time >= wake_up_time)
			break;
		usleep(500);
	}
}