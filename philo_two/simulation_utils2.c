/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 00:26:03 by miphigen          #+#    #+#             */
/*   Updated: 2021/03/03 00:33:04 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			check_if_dead(t_arguments *args)
{
	int				dead;
	const size_t	check = time_now();

	dead = 0;
	if ((unsigned long)args->ttd < check - args->last_meal_time)
	{
		sem_wait(args->print);
		printf("%zu phylo %d is dead\n",
				check - args->simulation_start, args->phylo_index);
		dead = 1;
	}
    return (dead);
}

int			check_meals(t_arguments **args)
{
	int			i;
	int			checker;
	const int	must_eat = args[0]->must_eat;

	i = 0;
	checker = 1;
	while (i < args[0]->number_of_philo && checker == 1)
	{
		if (args[i]->meals_total < must_eat)
			checker = 0;
		++i;
	}
	if (checker == 1)
	{
		sem_wait(args[0]->print);
		printf("%zu philosophers are full now\n",
				time_now() - args[0]->simulation_start);
	}


    return (checker);
}

void		free_allocs(t_arguments **args)
{
	free(args);
}

void		add_info(t_arguments *args, t_arguments *info, int i)
{
	args->number_of_args = info->number_of_args;
	args->number_of_philo = info->number_of_philo;
	args->ttd = info->ttd;
	args->tte = info->tte;
	args->tts = info->tts;
	args->must_eat = info->must_eat;
	args->phylo_index = i;
	args->meals_total = 0;
	args->sem = info->sem;
}
