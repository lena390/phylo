/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 23:54:08 by miphigen          #+#    #+#             */
/*   Updated: 2021/03/03 00:25:54 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t			time_now(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void			ft_sleep(unsigned int i)
{
	struct timeval	tv1;
	size_t			time;
	size_t			wake_up_time;

	gettimeofday(&tv1, NULL);
	wake_up_time = tv1.tv_sec * 1000 + tv1.tv_usec / 1000 + i;
	usleep(i * 0.9);
	while (1)
	{
		gettimeofday(&tv1, NULL);
		time = tv1.tv_sec * 1000 + tv1.tv_usec / 1000;
		if (time >= wake_up_time)
			break ;
		usleep(500);
	}
}

void			philo_eat(t_arguments *args)
{
	sem_wait(args->sem);
	sem_wait(args->print);
	printf("%ld phylo %d has taken a left fork\n",
			time_now() - args->simulation_start, args->phylo_index);
	sem_post(args->print);
	sem_wait(args->sem);
	sem_wait(args->print);
	printf("%ld phylo %d has taken two forks\n",
			time_now() - args->simulation_start, args->phylo_index);
	sem_post(args->print);
	args->last_meal_time = time_now();
	sem_wait(args->print);
	printf("%ld phylo %d is eating\n",
			time_now() - args->simulation_start, args->phylo_index);
	sem_post(args->print);
	ft_sleep(args->tte);
	++args->meals_total;
	sem_post(args->sem);
	sem_post(args->sem);
}

void			philo_sleep(t_arguments *args)
{
	sem_wait(args->print);
	printf("%ld phylo %d is sleeping\n",
			time_now() - args->simulation_start, args->phylo_index);
	sem_post(args->print);
	ft_sleep(args->tts);
}

void			philo_think(t_arguments *args)
{
	sem_wait(args->print);
	printf("%ld phylo %d is thinking\n",
			time_now() - args->simulation_start, args->phylo_index);
	sem_post(args->print);
}
