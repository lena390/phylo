/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 00:00:08 by miphigen          #+#    #+#             */
/*   Updated: 2021/03/03 00:17:14 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phylo.h"

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
		init_forks(&args);
		simulate(init_phylos(&args));
	}
	else
	{
		write(1, "Invalid arguments\n", 18);
		return (1);
	}
	return (0);
}

void			init_forks(t_arguments *args)
{
	const int	number_of_sem = args->number_of_phylo;

	sem_unlink("/name");
	args->sem = sem_open("/name", O_CREAT, S_IRWXU, number_of_sem);
    sem_unlink("/name2");
    args->print = sem_open("/name2", O_CREAT, S_IRWXU, 1);
}

t_arguments		**init_phylos(t_arguments *info)
{
	t_arguments	**args;
	int			i;

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
	while (++i < args[0]->number_of_phylo)
	{
	    args[i]->phylo_index = i;
		args[i]->simulation_start = time_start;
		args[i]->last_meal_time = args[i]->simulation_start;
		pid_t pid = fork();
		if (pid < 0)
		{
			printf("fork error\n");
			exit(pid);
		}
		if (pid == 0)
		{
			pthread_create(&args[i]->thread, NULL, hello, args[i]);
			i = -1;
			while (!dead)
			{
				usleep(3000);
				while (++i < args[0]->number_of_phylo && !dead) {
                    dead = check_if_dead(args[i]);
                    if (args[0]->must_eat != -1 && !dead)
                        dead = check_meals(args);
                }
			i = 0;
			}
		}
		else
		{
			int state;

			waitpid(pid, &state, 0);
			exit(9);
		}
	}
	sem_post(args[0]->print);
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
		phylo_eat(args);
		phylo_sleep(args);
		phylo_think(args);
	}
	return (NULL);
}
