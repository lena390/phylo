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

#include "phylo.h"

int			check_if_dead(t_arguments *args)
{
	int		dead;
	size_t	check;

	dead = 0;
	if ((unsigned long)args->ttd < (check = time_now()) - args->last_meal_time)
	{
		pthread_mutex_lock(args->print);
		printf("%zu phylo %d is dead\n",
				check - args->simulation_start, args->phylo_index);
		dead = 1;
	}
	return (dead);
}

int			check_meals(t_arguments **args)
{
	int	i;
	int	checker;
	int	must_eat;

	must_eat = args[0]->must_eat;
	i = 0;
	checker = 1;
	while (i < args[0]->number_of_phylo && checker == 1)
	{
		if (args[i]->meals_total < must_eat)
			checker = 0;
		++i;
	}
	if (checker == 1)
	{
		printf("%zu philosophers are full now\n",
				time_now() - args[0]->simulation_start);
	}
	return (checker);
}

void		free_forks(t_arguments *args)
{
	int i;

	i = -1;
	while (++i < args->number_of_phylo + 1)
	{
		pthread_mutex_destroy(&args->mutex_array[i]);
	}
	free(args->mutex_array);
}

void		free_allocs(t_arguments **args)
{
	free(args);
}

void		add_info(t_arguments *args, t_arguments *info, int i)
{
	args->number_of_args = info->number_of_args;
	args->number_of_phylo = info->number_of_phylo;
	args->ttd = info->ttd;
	args->tte = info->tte;
	args->tts = info->tts;
	args->must_eat = info->must_eat;
	args->one = &info->mutex_array[i];
	args->two = i + 1 == info->number_of_phylo ?
		&info->mutex_array[0] : &info->mutex_array[i + 1];
	args->print = &info->mutex_array[info->number_of_phylo];
	args->phylo_index = i;
	args->meals_total = 0;
}
