/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 21:19:44 by judecuyp          #+#    #+#             */
/*   Updated: 2020/11/18 21:19:44 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int		checker_max_meals(t_glob *g)
{
	if (g->meals_max_count >= g->nop)
	{
		pthread_mutex_lock(&g->print_m);
		if (ft_print_all_meals(g))
			return (0);
		g->is_die = 1;
		return (1);
	}
	return (0);
}

void	*checker_death(void *arg)
{
	t_phil					*p;
	long long unsigned int 	cur_time;

	p = (t_phil *)arg;
	while (1)
	{
		if (get_time(&cur_time, p->glob->time_start))
			return ((void *)TIMERR);
		if (!p->is_eating && cur_time > (p->glob->ttd + p->last_eat))
		{
			pthread_mutex_lock(&p->glob->print_m);
			ft_print(p, "  died");
			p->glob->is_die = 1;		
			return (NULL);
		}
		if (p->glob->notepme > 0)
			if (checker_max_meals(p->glob))
				return (NULL);
		usleep(100);
	}
	return (NULL);
}

void	*states(void *arg)
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

int		starting_threads(t_glob *g)
{
	int		i;
	t_phil	*p;
	
	i = 0;
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

int		main(int argc, char **argv)
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