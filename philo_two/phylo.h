/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phylo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 23:46:20 by miphigen          #+#    #+#             */
/*   Updated: 2021/03/03 00:17:03 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYLO_H
# define PHYLO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include "phylo.h"
# include <sys/time.h>
# include <fcntl.h>           /* For O_* constants */
# include <sys/stat.h>        /* For mode constants */
# include <semaphore.h>

typedef struct		s_arguments
{
	int				number_of_args;
	int				number_of_phylo;
	int				ttd;
	int				tte;
	int				tts;
	int				must_eat;
	sem_t			*sem;
	int				meals_total;

	pthread_t		thread;
	sem_t			*print;
	int				phylo_index;
	size_t			last_meal_time;
	size_t			simulation_start;

}					t_arguments;

t_arguments			*parse_args(int ac, char **av, t_arguments *args);
void				ft_sleep(unsigned int i);
int					ft_atoi(const char *s);
size_t				time_now(void);
void				phylo_eat(t_arguments *args);
void				phylo_sleep(t_arguments *args);
void				phylo_think(t_arguments *args);
int					check_if_dead(t_arguments *args);
int					check_meals(t_arguments **args);
void				free_allocs(t_arguments **args);
void				free_forks(t_arguments *args);
t_arguments			*parse_args(int ac, char **av, t_arguments *args);
void				simulate(t_arguments **args);
int					check_values(t_arguments *pArguments);
void				init_forks(t_arguments *args);
t_arguments			**init_phylos(t_arguments *args);
void				*hello(void *v_args);
void				add_info(t_arguments *args, t_arguments *info, int i);

#endif
