#include "phylo.h"

t_arguments *parse_args(int ac, char **av, t_arguments *args);
void simulate();
int check_values(t_arguments *pArguments);
void init_forks(t_arguments *args);
t_arguments **init_phylos(t_arguments *args);
void *hello(void *v_args);

int main(int ac, char **av)
{
	t_arguments args;

	if (ac != 6 && ac != 5)
	{
		write(1, "Wrong arguments!\n", 17);
		return (1);
	}
	if (parse_args(ac, av, &args) != NULL)
	{
		init_forks(&args);
		simulate(init_phylos(&args));
	}
	else
	{
		write(1, "Invalid arguments\n", 18);
		return (1);
	}
	return 0;
}

void init_forks(t_arguments *args)
{
	int i;

	args->mutex_array = malloc(sizeof(pthread_mutex_t) * args->number_of_phylo + 1);
	i = 0;
	while (i < args->number_of_phylo + 1)
	{
		pthread_mutex_init(&args->mutex_array[i], NULL);
		i++;
	}
}

t_arguments **init_phylos(t_arguments *info)
{
	t_arguments **args;
	int i;

	args = malloc(sizeof(t_arguments *) * info->number_of_phylo);
	i = 0;
	while (i < info->number_of_phylo)
	{
		args[i] = malloc(sizeof(t_arguments));
		++i;
	}
	i = 0;
	while (i < info->number_of_phylo)
	{
		args[i]->number_of_args = info->number_of_args;
		args[i]->number_of_phylo = info->number_of_phylo;
		args[i]->ttd = info->ttd;
		args[i]->tte = info->tte;
		args[i]->tts = info->tts;
		args[i]->number_of_times_each_phylo_must_eat = info->number_of_times_each_phylo_must_eat;

		args[i]->thread = malloc(sizeof(pthread_t));
		args[i]->one = &info->mutex_array[i];
		args[i]->two = i + 1 == info->number_of_phylo ? &info->mutex_array[0] : &info->mutex_array[i + 1];
		args[i]->print = &info->mutex_array[info->number_of_phylo];
		args[i]->phylo_index = i;
		args[i]->meals_total = 0;
		++i;
	}
	return (args);
}

void simulate(t_arguments **args)
{
	int i;
	int status_addr;
	int dead = 0;
	size_t	time_start;

	i = 0;
	time_start = time_now();
	while (i < args[0]->number_of_phylo)
	{
		args[i]->simulation_start = time_now();
		args[i]->last_meal_time = args[i]->simulation_start;
		int result = pthread_create(&args[i]->thread, NULL, hello, args[i]);
		i++;
	}
	i = 0;
	while (!dead) 
	{
		while (i < args[0]->number_of_phylo)
		{		
			if (time_now() - args[i]->last_meal_time > args[0]->ttd)
				{ 
				    printf("%zu phylo %d is dead (%zu) ttd: %d\n", 
					time_now() - args[i]->simulation_start, args[i]->phylo_index, time_now() - args[i]->simulation_start, args[0]->ttd);
					dead = 1;
    				exit(0);
				}		
			i++;
		}
		i = 0;
	}
}

void *hello(void *v_args)
{
	struct timeval tmp;
	t_arguments *args = v_args;
	if (args->phylo_index % 2 == 0)
	 	ft_sleep(50);
	 while (1)
	 {
    	pthread_mutex_lock(args->one);
		// pthread_mutex_lock(args->print);
		// printf("%ld phylo %d has taken a left fork\n", time_now(), args->phylo_index);
		// pthread_mutex_unlock(args->print);
		pthread_mutex_lock(args->two);
		// pthread_mutex_lock(args->print);
		// printf("%ld phylo %d has taken two forks\n", time_now(), args->phylo_index);
		// pthread_mutex_unlock(args->print);
		args->last_meal_time = time_now();
		pthread_mutex_lock(args->print);
		printf("%04ld phylo %d is eating\n", time_now() - args->simulation_start, args->phylo_index);// - simulation start
		pthread_mutex_unlock(args->print);
		ft_sleep(args->tte);
		++args->meals_total;
		args->last_meal_time = time_now();
		pthread_mutex_unlock(args->one);
		pthread_mutex_unlock(args->two);

		pthread_mutex_lock(args->print);
		printf("%04ld phylo %d is sleeping\n", time_now() - args->simulation_start, args->phylo_index);
		pthread_mutex_unlock(args->print);
		ft_sleep(args->tts);

		pthread_mutex_lock(args->print);
		printf("%04ld phylo %d is thinking\n", time_now() - args->simulation_start, args->phylo_index);
		pthread_mutex_unlock(args->print);
	 }
	return 0;
}