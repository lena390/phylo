/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 00:26:03 by miphigen          #+#    #+#             */
/*   Updated: 2021/03/03 00:33:04 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phylo.h"

void	kill_processes(t_arguments **args)
{
	int i;

	i = -1;
	while (++i < args[0]->number_of_phylo)
	{
		kill(args[i]->pid, SIGKILL);
	}
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
