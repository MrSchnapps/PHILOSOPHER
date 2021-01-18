/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:02:23 by judecuyp          #+#    #+#             */
/*   Updated: 2021/01/18 12:43:16 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			starting_threads(t_glob *g)
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
		g->tab_pid[i] = fork();
		if (g->tab_pid[i] < 0)
			return (printerr(FORKERR));
		else if (g->tab_pid[i] == 0)
		{
			states(p);
			exit(0);
		}
		usleep(35);
		i++;
	}
	return (0);
}

int			parse_args(int argc, char **argv, t_glob *g)
{
	if (argc < 5 || argc > 6)
		return (printerr(INVNB));
	if ((g->nop = ft_atoi(argv[1])) < 2
		|| (g->ttd = ft_atoi(argv[2])) < 60
		|| (g->tte = ft_atoi(argv[3])) < 60
		|| (g->tts = ft_atoi(argv[4])) < 60)
		return (printerr(INVVAL));
	if (g->nop > 200)
		return (printerr(INVVAL));
	if (argc == 5)
		g->notepme = -1;
	else
	{
		if ((g->notepme = ft_atoi(argv[5])) <= 0)
			return (printerr(INVVAL));
	}
	return (0);
}

static int	init_after(t_glob *g)
{
	if (!(g->tab_pid = (pid_t *)malloc(g->nop * sizeof(pid_t))))
		return (printerr(MERR));
	sem_unlink("forks");
	g->forks_sem = sem_open("forks", O_CREAT | O_EXCL, S_IRWXU, g->nop);
	sem_unlink("print");
	g->print_sem = sem_open("print", O_CREAT | O_EXCL, S_IRWXU, 1);
	return (0);
}

int			ft_init(t_glob *g)
{
	int i;

	i = 0;
	g->is_die = 0;
	g->die_tester = 0;
	if (g->notepme > 0)
		g->meals_max_count = 0;
	else
		g->meals_max_count = -2;
	g->tab_pid = NULL;
	if (!(g->phil = (t_phil *)malloc(g->nop * sizeof(t_phil))))
		return (printerr(MERR));
	while (i < g->nop)
	{
		g->phil[i].glob = g;
		g->phil[i].nb_of_eat = 0;
		g->phil[i].is_eating = 0;
		g->phil[i].last_eat = 0;
		i++;
	}
	return (init_after(g));
}
