/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 00:26:03 by miphigen          #+#    #+#             */
/*   Updated: 2021/03/12 15:13:41 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phylo.h"

int		check_if_dead(t_arguments *args)
{
	int				dead;
	const size_t	check = time_now();

	dead = 0;
	if ((unsigned long)args->ttd < check - args->last_meal_time)
	{
		sem_wait(args->print);
		printf("%zu phylo %d is dead.\n",
			check - args->simulation_start, args->phylo_index);
		dead = 1;
	}
	return (dead);
}

int		check_meals(t_arguments *args)
{
	int			i;
	int			checker;
	const int	must_eat = args->must_eat;

	i = 0;
	checker = 1;
	if (args->meals_total >= must_eat)
	{
		printf("philisophers are full now.\n");
		return (13);
	}
	return (0);
}

void	add_info(t_arguments *args, t_arguments *info)
{
	args->number_of_args = info->number_of_args;
	args->number_of_phylo = info->number_of_phylo;
	args->ttd = info->ttd;
	args->tte = info->tte;
	args->tts = info->tts;
	args->must_eat = info->must_eat;
	args->meals_total = 0;
	args->sem = info->sem;
}

void	kill_processes(t_arguments **args)
{
	int i;

	sem_close(args[0]->sem);
	sem_close(args[0]->print);
	i = -1;
	while (++i < args[0]->number_of_phylo)
	{
		kill(args[i]->pid, SIGKILL);
	}
	free(args);
}

int		child_routine(t_arguments **args, int i)
{
	int dead;

	dead = 0;
	pthread_create(&args[i]->thread, NULL, hello, args[i]);
	while (!dead)
	{
		usleep(3000);
		dead = check_if_dead(args[i]);
		if (args[i]->must_eat != -1 && !dead)
			dead = check_meals(args[i]);
	}
	return (dead);
}
