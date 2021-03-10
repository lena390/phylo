#include "phylo.h"

void	kill_processes(t_arguments **args)
{
	int i = -1;
	while (++i < args[0]->number_of_phylo)
	{
		kill(args[i]->pid, SIGKILL);
	}
}

void child_routine(t_arguments **args, int i)
{
	int dead;
	
	dead = 0;
	pthread_create(&args[i]->thread, NULL, hello, args[i]);
	while (!dead)
	{
		usleep(3000);
        dead = check_if_dead(args[i]);
  	    if (args[i]->must_eat != -1 && !dead)
     	    dead = check_meals(args);
	}
}
