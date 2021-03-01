#ifndef PHYLO_H
#define PHYLO_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <pthread.h>
#include "phylo.h"
#include <sys/time.h>

typedef struct  s_arguments
{
	int             number_of_args;
    int             number_of_phylo;
    int             ttd;
    int             tte;
    int             tts;
    int             number_of_times_each_phylo_must_eat;
	pthread_mutex_t *mutex_array;
    int             meals_total;

    pthread_t       thread;
    pthread_mutex_t *one;
    pthread_mutex_t *two;
    pthread_mutex_t *print;
    int             phylo_index;
    size_t          last_meal_time;
    size_t          simulation_start;

}               t_arguments;

t_arguments* parse_args(int ac, char** av, t_arguments *args);
void ft_sleep(unsigned int);
int					ft_atoi(const char *s);
size_t	time_now(void);


#endif