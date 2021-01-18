/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 21:19:44 by judecuyp          #+#    #+#             */
/*   Updated: 2021/01/18 19:11:09 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int				checker_max_meals(t_phil *p)
{
	if (p->glob->meals_max_count >= p->glob->nop)
	{
		pthread_mutex_lock(&p->glob->print_m);
		if (ft_print_end(p, 2))
			return (0);
		p->glob->is_die = 1;
		return (1);
	}
	return (0);
}

static void		*checker_death(void *arg)
{
	t_phil					*p;
	long long unsigned int	cur_time;
	t_glob					*g;
	
	p = (t_phil *)arg;
	g = p->glob;
	while (!g->die_tester)
	{
		if (get_time(&cur_time, g))
			return ((void *)TIMERR);
		if (!p->is_eating && cur_time > (g->ttd + p->last_eat))
		{
			g->die_tester = 1;
			pthread_mutex_lock(&g->print_m);
			ft_print_end(p, 1);
			g->is_die = 1;
			return (NULL);
		}
		if (g->notepme > 0)
			if (checker_max_meals(p))
				return (NULL);
		usleep(30);
	}
	return (NULL);
}

static void		*states(void *arg)
{
	t_phil		*p;
	pthread_t	id;

	p = (t_phil *)arg;
	if (pthread_create(&id, NULL, &checker_death, arg))
		return ((void *)ERR);
	pthread_detach(id);
	while (!p->glob->is_die)
	{
		start_forks(p);
		eating(p);
		sleeping(p);
		thinking(p);
	}
	return (NULL);
}

static int		starting_threads(t_glob *g)
{
	int		i;
	t_phil	*p;

	i = 0;
	if (get_start_time(&g->time_start, g) < 0)
		return (TIMERR);
	while (i < g->nop)
	{
		g->phil[i].order = i + 1;
		p = (void *)&g->phil[i];
		if (pthread_create(&g->tab_th[i], NULL, &states, p))
			return (THDERR);
		pthread_detach(g->tab_th[i]);
		usleep(100);
		i++;
	}
	return (0);
}

int				main(int argc, char **argv)
{
	int			err;
	t_glob		g;

	if (parse_args(argc, argv, &g))
		return (EXIT_FAILURE);
	if (ft_init(&g))
		return (EXIT_FAILURE);
	if ((err = starting_threads(&g)))
		return (printerr(err, &g));
	while (!g.is_die)
		usleep(1000);
	free_all(&g, 0);
	return (0);
}
