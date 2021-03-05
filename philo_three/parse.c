/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miphigen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 23:56:14 by miphigen          #+#    #+#             */
/*   Updated: 2021/03/02 23:57:45 by miphigen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phylo.h"

int			check_values(t_arguments *args)
{
	int flag;

	flag = 1;
	if (args->number_of_phylo < 2)
		flag = 0;
	if (args->ttd < 1)
		flag = 0;
	if (args->tts < 1)
		flag = 0;
	if (args->tte < 1)
		flag = 0;
	if (args->number_of_args == 6 && args->must_eat < 0)
		flag = 0;
	return (flag);
}

t_arguments	*parse_args(int ac, char **av, t_arguments *args)
{
	args->number_of_args = ac;
	args->number_of_phylo = ft_atoi(av[1]);
	args->ttd = ft_atoi(av[2]);
	args->tte = ft_atoi(av[3]);
	args->tts = ft_atoi(av[4]);
	args->must_eat = ac == 6 ? ft_atoi(av[5]) : -1;
	if (check_values(args) == 1)
		return (args);
	else
		return (NULL);
}
