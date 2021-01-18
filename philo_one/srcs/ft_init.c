/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:02:23 by judecuyp          #+#    #+#             */
/*   Updated: 2021/01/18 13:38:52 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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

static int	mut_init(t_glob *g)
{
	int i;

	g->is_die = 0;
	g->die_tester = 0;
	if (!(g->tab_th = (pthread_t *)malloc(g->nop * sizeof(pthread_t))))
	{
		free(g->phil);
		return (printerr(MERR, g));
	}
	pthread_mutex_init(&g->eat_max_m, NULL);
	pthread_mutex_init(&g->print_m, NULL);
	if (!(g->forks_m = (pthread_mutex_t *)malloc(g->nop *
					sizeof(pthread_mutex_t))))
	{
		free(g->phil);
		free(g->tab_th);
		return (printerr(MERR, g));
	}
	i = 0;
	while (i < g->nop)
	{
		pthread_mutex_init(&g->forks_m[i], NULL);
		i++;
	}
	return (0);
}

int			ft_init(t_glob *g)
{
	int i;

	i = -1;
	if (g->notepme > 0)
		g->meals_max_count = 0;
	else
		g->meals_max_count = -2;
	g->tab_th = NULL;
	g->forks_m = NULL;
	if (!(g->phil = (t_phil *)malloc(g->nop * sizeof(t_phil))))
		return (printerr(MERR, g));
	while (++i < g->nop)
	{
		g->phil[i].glob = g;
		g->phil[i].l_fork = i;
		g->phil[i].is_eating = 0;
		g->phil[i].nb_of_eat = 0;
		g->phil[i].last_eat = 0;
		if (i == 0)
			g->phil[i].r_fork = g->nop - 1;
		else
			g->phil[i].r_fork = i - 1;
	}
	return (mut_init(g));
}
