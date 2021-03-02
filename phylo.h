#ifndef PHYLO_H
# define PHYLO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include "phylo.h"
# include <sys/time.h>

typedef struct      s_arguments
{
	int             number_of_args;
    int             number_of_phylo;
    int             ttd;
    int             tte;
    int             tts;
    int             must_eat;
	pthread_mutex_t *mutex_array;
    int             meals_total;

    pthread_t       thread;
    pthread_mutex_t *one;
    pthread_mutex_t *two;
    pthread_mutex_t *print;
    pthread_mutex_t *lmt_change;
    int             phylo_index;
    size_t          last_meal_time;
    size_t          simulation_start;

}                   t_arguments;

t_arguments*        parse_args(int ac, char** av, t_arguments *args);
void                ft_sleep(unsigned int);
int		            ft_atoi(const char *s);
size_t	            time_now(void);
void                phylo_eat(t_arguments* args);
void                phylo_sleep(t_arguments* args);
void                phylo_think(t_arguments* args);
int                 check_if_dead(t_arguments *args);
int                 check_meals(t_arguments **args);
void                free_allocs(t_arguments **args);
void                free_forks(t_arguments *args);

#endif