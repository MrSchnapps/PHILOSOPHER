/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 21:19:44 by judecuyp          #+#    #+#             */
/*   Updated: 2021/01/14 16:37:30 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int		checker_max_meals(t_phil *p)
{
	if (p->glob->meals_max_count >= p->glob->nop)
	{
		sem_wait(p->glob->print_sem);
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

	p = (t_phil *)arg;
	while (1)
	{
		if (get_time(&cur_time, p->glob->time_start))
			return ((void *)TIMERR);
		if (!p->is_eating && cur_time > (p->glob->ttd + p->last_eat))
		{
			p->glob->die_tester = 1;
			sem_wait(p->glob->print_sem);
			ft_print_end(p, 1);
			p->glob->is_die = 1;
			return (NULL);
		}
		if (p->glob->notepme > 0)
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
	if (get_time(&p->last_eat, p->glob->time_start) < 0)
		return ((void *)ERR);
	if (pthread_create(&id, NULL, &checker_death, arg))
		return ((void *)ERR);
	pthread_detach(id);
	while (!p->glob->is_die)
	{
		if (start_forks(p))
			return ((void *)ERR);
		if (eating(p))
			return ((void *)ERR);
		if (sleeping(p))
			return ((void *)ERR);
		if (thinking(p))
			return ((void *)ERR);
	}
	return (NULL);
}

static int		starting_threads(t_glob *g)
{
	int		i;
	t_phil	*p;

	i = 0;
	if (get_start_time(&g->time_start) < 0)
		return (TIMERR);
	while (i < g->nop)
	{
		g->phil[i].order = i + 1;
		p = (void *)&g->phil[i];
		if (pthread_create(&g->tab_th[i], NULL, &states, p))
			return (printerr(THDERR));
		pthread_detach(g->tab_th[i]);
		usleep(1000);
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
		return (free_all(&g, err));
	while (!g.is_die)
		usleep(1000);
	free_all(&g, 0);
	return (0);
}
