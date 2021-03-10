/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 00:00:08 by miphigen          #+#    #+#             */
/*   Updated: 2021/03/03 20:29:42 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int				main(int ac, char **av)
{
	t_arguments args;

	if (ac != 6 && ac != 5)
	{
		write(1, "Wrong arguments!\n", 17);
		return (1);
	}
	if (parse_args(ac, av, &args) != NULL)
	{
		create_sem(&args);
		simulate(init_philos(&args));
	}
	else
	{
		write(1, "Invalid arguments\n", 18);
		return (1);
	}
	return (0);
}

void			create_sem(t_arguments *args)
{
	const int	number_of_sem = args->number_of_philo;

	sem_unlink("/namee");
	args->sem = sem_open("/namee", O_CREAT | O_RDWR, S_IRWXU, number_of_sem);
	sem_unlink("/namee2");
	args->print = sem_open("/namee2", O_CREAT | O_RDWR, S_IRWXU, 1);
}

t_arguments		**init_philos(t_arguments *info)
{
	t_arguments	**args;
	int			i;

	args = malloc(sizeof(t_arguments *) * info->number_of_philo);
	i = 0;
	while (i < info->number_of_philo)
	{
		args[i] = malloc(sizeof(t_arguments));
		++i;
	}
	i = 0;
	while (i < info->number_of_philo)
	{
		add_info(args[i], info, i);
		args[i]->print = info->print;
		++i;
	}
	return (args);
}

void			simulate(t_arguments **args)
{
	int				i;
	int				dead;
	const size_t	time_start = time_now();

	dead = 0;
	i = -1;
	while (++i < args[0]->number_of_philo)
	{
		args[i]->simulation_start = time_start;
		args[i]->last_meal_time = args[i]->simulation_start;
		pthread_create(&args[i]->thread, NULL, hello, args[i]);
	}
	i = -1;
	while (!dead)
	{
		usleep(3000);
		while (++i < args[0]->number_of_philo && !dead)
		{
			dead = check_if_dead(args[i]);
			if (args[0]->must_eat != -1 && !dead)
				dead = check_meals(args);
		}
		i = 0;
	}
	free_allocs(args);
}

void			*hello(void *v_args)
{
	t_arguments	*args;

	args = v_args;
	if (args->phylo_index % 2 == 0)
		ft_sleep(10);
	while (1)
	{
		philo_eat(args);
		philo_sleep(args);
		philo_think(args);
	}
	return (NULL);
}
