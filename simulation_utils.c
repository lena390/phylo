#include "phylo.h"

size_t	time_now()
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void ft_sleep(unsigned int i)
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

void phylo_eat(t_arguments* args)
{
    pthread_mutex_lock(args->one);
    pthread_mutex_lock(args->print);
    printf("%ld phylo %d has taken a left fork\n", time_now() - args->simulation_start, args->phylo_index);
    pthread_mutex_unlock(args->print);
    pthread_mutex_lock(args->two);
    pthread_mutex_lock(args->print);
    printf("%ld phylo %d has taken two forks\n", time_now() - args->simulation_start, args->phylo_index);
    pthread_mutex_unlock(args->print);
    pthread_mutex_lock(args->lmt_change);
    args->last_meal_time = time_now();
    pthread_mutex_unlock(args->lmt_change);
    pthread_mutex_lock(args->print);
    printf("%ld phylo %d is eating\n", time_now() - args->simulation_start, args->phylo_index);
    pthread_mutex_unlock(args->print);
    ft_sleep(args->tte);
    ++args->meals_total;
	pthread_mutex_unlock(args->one);
    pthread_mutex_unlock(args->two);
}

void phylo_sleep(t_arguments *args)
{
    pthread_mutex_lock(args->print);
    printf("%ld phylo %d is sleeping\n", time_now() - args->simulation_start, args->phylo_index);
    pthread_mutex_unlock(args->print);
    ft_sleep(args->tts);
}
void phylo_think(t_arguments *args)
{
    pthread_mutex_lock(args->print);
    printf("%ld phylo %d is thinking\n", time_now() - args->simulation_start, args->phylo_index);
    pthread_mutex_unlock(args->print);
}
int check_if_dead(t_arguments *args)
{
    int dead = 0;
    size_t	check_time;

    pthread_mutex_lock(args->lmt_change);
    if (args->ttd < (check_time = time_now()) - args->last_meal_time)
    {
        pthread_mutex_lock(args->print);
        printf("%zu phylo %d is dead\n",
               check_time - args->simulation_start, args->phylo_index);
        dead = 1;
    }
    pthread_mutex_unlock(args->lmt_change);
    return (dead);
}

int     check_meals(t_arguments **args)
{
    int i;
    int checker;
    int must_eat;

    must_eat = args[0]->must_eat;
    i = 0;
    checker = 1;
    while(i < args[0]->number_of_phylo && checker == 1)
    {
        if (args[i]->meals_total < must_eat)
           checker = 0;
    	++i;
	}
    if (checker == 1)
    {
        printf("%zu philosophers are full now\n", time_now() - args[0]->simulation_start);
    }
    return (checker);
}

void    free_forks(t_arguments *args)
{
    int i;

    i = -1;
    while (++i < args->number_of_phylo + 2)
    {
        pthread_mutex_destroy(&args->mutex_array[i]);
    }
    free(args->mutex_array);
}

void    free_allocs(t_arguments **args)
{
    int i;

    i = -1;
    while (++i < args[0]->number_of_phylo)
    {
        free(args[i]);
    }
    free(args);
}