/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:02:23 by judecuyp          #+#    #+#             */
/*   Updated: 2020/11/19 17:02:23 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	mut_init(t_glob *g)
{
	int i;

	pthread_mutex_init(&g->eat_max_m, NULL);
	pthread_mutex_init(&g->print_m, NULL);
	if (!(g->forks_m = (pthread_mutex_t *)malloc(g->nop * sizeof(pthread_mutex_t))))
		return (printerr(MERR));
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

	i = 0;
	g->is_die = 0;
	if (g->notepme > 0)
		g->meals_max_count = 0;
	else
		g->meals_max_count = -2; //for the final loop in main process
	g->tab_th = NULL;
	g->forks_m = NULL;
	if (!(g->phil = (t_phil *)malloc(g->nop * sizeof(t_phil))))
		return (printerr(MERR));
	while (i < g->nop)
	{
		g->phil[i].glob = g;
		g->phil[i].l_fork = i;
		g->phil[i].nb_of_eat = 0;
		if (i == 0)
			g->phil[i].r_fork = g->nop - 1;
		else
			g->phil[i].r_fork = i - 1;
		i++;
	}
	if (!(g->tab_th = (pthread_t *)malloc(g->nop * sizeof(pthread_t))))
		return (printerr(MERR));
	if (get_start_time(&g->time_start) < 0)
		return (TIMERR);
	return (mut_init(g));
}
