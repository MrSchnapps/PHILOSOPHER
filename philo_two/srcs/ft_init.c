/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:02:23 by judecuyp          #+#    #+#             */
/*   Updated: 2021/01/18 14:12:51 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int			parse_args(int argc, char **argv, t_glob *g)
{
	if (argc < 5 || argc > 6)
		return (printerr(INVNB, g));
	if ((g->nop = ft_atoi(argv[1])) < 2
		|| (g->ttd = ft_atoi(argv[2])) < 60
		|| (g->tte = ft_atoi(argv[3])) < 60
		|| (g->tts = ft_atoi(argv[4])) < 60)
		return (printerr(INVVAL, g));
	if (g->nop > 200)
		return (printerr(INVVAL, g));
	if (argc == 5)
		g->notepme = -1;
	else
	{
		if ((g->notepme = ft_atoi(argv[5])) <= 0)
			return (printerr(INVVAL, g));
	}
	return (0);
}

static int	init_after(t_glob *g)
{
	g->is_die = 0;
	g->die_tester = 0;
	if (!(g->tab_th = (pthread_t *)malloc(g->nop * sizeof(pthread_t))))
	{
		free(g->phil);
		return (printerr(MERR, g));
	}
	sem_unlink("forks");
	if ((g->forks_sem = sem_open("forks", O_CREAT | O_EXCL, S_IRWXU, g->nop)) == SEM_FAILED)
		return (printerr(SEMERR, g));
	sem_unlink("print");
	if ((g->print_sem = sem_open("print", O_CREAT | O_EXCL, S_IRWXU, 1)) == SEM_FAILED)
		return (printerr(SEMERR, g));
	sem_unlink("eat_max");
	if ((g->eat_max_sem = sem_open("eat_max", O_CREAT | O_EXCL, S_IRWXU, 1)) == SEM_FAILED)
		return (printerr(SEMERR, g));
	return (0);
}

int			ft_init(t_glob *g)
{
	int i;

	i = 0;
	if (g->notepme > 0)
		g->meals_max_count = 0;
	else
		g->meals_max_count = -2;
	g->tab_th = NULL;
	if (!(g->phil = (t_phil *)malloc(g->nop * sizeof(t_phil))))
		return (printerr(MERR, g));
	while (i < g->nop)
	{
		g->phil[i].glob = g;
		g->phil[i].nb_of_eat = 0;
		g->phil[i].is_eating = 0;
		g->phil[i].last_eat = 0;
		i++;
	}
	if (init_after(g))
	{
		free(g->phil);
		return (ERR);
	}
	return (0);
}
