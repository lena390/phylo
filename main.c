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
	free_forks(&args);
	return 0;
}

void init_forks(t_arguments *args)
{
	int i;
	int number_of_mutex;

    number_of_mutex = args->number_of_phylo + 2;
	args->mutex_array = malloc(sizeof(pthread_mutex_t) * number_of_mutex);
	i = 0;
	while (i < number_of_mutex)
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
		args[i]->must_eat = info->must_eat;
		args[i]->one = &info->mutex_array[i];
		args[i]->two = i + 1 == info->number_of_phylo ? &info->mutex_array[0] : &info->mutex_array[i + 1];
		args[i]->print = &info->mutex_array[info->number_of_phylo];
        args[i]->lmt_change = &info->mutex_array[info->number_of_phylo + 1];
		args[i]->phylo_index = i;
		args[i]->meals_total = 0;
		++i;
	}
	return (args);
}

void simulate(t_arguments **args)
{
	int i;
	int dead = 0;
	size_t	time_start;

	i = 0;
	time_start = time_now();
	while (i < args[0]->number_of_phylo)
	{
		args[i]->simulation_start = time_start;
		args[i]->last_meal_time = args[i]->simulation_start;
		pthread_create(&args[i]->thread, NULL, hello, args[i]);
		i++;
	}
	i = 0;
	while (!dead) 
	{
		while (i < args[0]->number_of_phylo && !dead)
		{
            dead = check_if_dead(args[i]);
            if (args[0]->must_eat != -1)
                dead = check_meals(args);
            i++;
		}
		i = 0;
	}
	free_allocs(args);
}

void *hello(void *v_args)
{
t_arguments *args = v_args;
	if (args->phylo_index % 2 == 0)
	 	ft_sleep(10);
	 while (1)
	 {
	     phylo_eat(args);
         phylo_sleep(args);
         phylo_think(args);
	 }
	 return NULL;
}