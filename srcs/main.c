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

int		parse_args(int argc, char **argv, t_glob *g)
{
	if (argc < 5 || argc > 6)
		return (printerr("Invalid number of arguments", EXIT_FAILURE));
	if (!(g->nop = ft_atoi(argv[1])) || !(g->ttd = ft_atoi(argv[2])) 
		|| !(g->tte = ft_atoi(argv[3])) || !(g->tts = ft_atoi(argv[4])))
		return (printerr("Invalid value in arguments", EXIT_FAILURE));
	if (argc == 5)
		g->notepme = -1;
	else
	{
		if (!(g->notepme = ft_atoi(argv[5])))
			return (printerr("Invalid value in arguments", EXIT_FAILURE));
	}
	return (0);
}

int		eat_func(t_phil *p)
{
	long long unsigned int cur_time;

	if (get_time(&cur_time) < 0)
		return (printerr("Time error", TIMERR));
	ft_putnbr_fd(cur_time - p->glob->time_start, 1);
	ft_putstr_fd("x se met à manger.\n", 1);
	return (0);
}

void	*philo(void *arg)
{
	t_phil *p;

	p = (t_phil *)arg;
	while (1)
	{
		/*pthread_mutex_lock(&p->glob->print_m);
		eat_func(p);
		pthread_mutex_unlock(&p->glob->print_m);*/
		ft_print(p, " is eating.\n");
		usleep(p->glob->tte);
		ft_print(p, " is sleeping.\n");
		

		/*pthread_mutex_lock(&p->glob->print_m);
		ft_putstr_fd("le philosophe numero x se met à dormir.\n", 1);
		pthread_mutex_unlock(&p->glob->print_m);*/
		
		usleep(p->glob->tts);
		ft_print(p, " is thinking.\n");
		/*pthread_mutex_lock(&p->glob->print_m);
		ft_putstr_fd("le philosophe numero x se met à penser.\n", 1);
		pthread_mutex_unlock(&p->glob->print_m);*/
		
	}
	return (0);
}

int		starting_threads(t_glob *g)
{
	int		i;
	int		err;
	t_phil	*p;

	i = 0;
	while (i < g->nop)
	{
		g->phil[i].order = i + 1;
		p = (void *)&g->phil[i];
		//printf("\ntest |%d|\n", p->glob->tts);
		if ((err = pthread_create(&(g->tab_th[i]), NULL, philo, p)))
			return (err);
		i++;
	}
	i = 0;
	while (i < g->nop)
	{
		pthread_join(g->tab_th[i], NULL);
		usleep(100);
		i++;
	}
	return (0);
}

int		ft_init(t_glob *g)
{
	int i;

	i = 0;
	g->tab_th = NULL;
	if (!(g->phil = (t_phil *)malloc(g->nop * sizeof(t_phil))))
		return (printerr("Memory error", MERR));
	while (i < g->nop)
	{
		g->phil[i].glob = g;
		i++;
	}
	if (!(g->tab_th = (pthread_t *)malloc(g->nop * sizeof(pthread_t))))
		return (printerr("Memory error", MERR));
	if (get_time(&g->time_start) < 0)
		return (TIMERR);
	pthread_mutex_init(&g->print_m, NULL);
	return (0);
}



/*
** TODO
*/
//printf("\ntest\n");
//micro =  10^-6
//milli =  10^^-3
//Convertir l'entree en mili -> micro pour usleep (/ 1000 askip)
//modif putstr endl etc dans mylib
// verif si il faut faire gettime au tout debut pour le time_start

int		main(int argc, char **argv)
{
	int			err;
	t_glob		g;

	if (parse_args(argc, argv, &g))
		return (free_all(&g, EXIT_FAILURE));
	if (ft_init(&g))
		return (EXIT_FAILURE);
	if ((err = starting_threads(&g)))
		return (free_all(&g, err));
	free_all(&g, 0);
	return (0);
}