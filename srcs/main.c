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

/*
** TODO
** Attention aux msg à afficher (pt enlever left / right hands)
**
*/
int		checker_max_meals(t_glob *g)
{
	if (g->meals_max_count >= g->nop)
	{
		pthread_mutex_lock(&g->print_m);
		if (ft_print_all_meals(g))
			return (0); //refaire ce msg d'erreur
		//pthread_mutex_unlock(&p->glob->print_m);
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
		//mettre mutex
		if (get_time(&cur_time, p->glob->time_start))
			return ((void *)TIMERR);
		if (!p->is_eating && cur_time > (p->glob->ttd + p->last_eat))
		{
			pthread_mutex_lock(&p->glob->print_m);
			ft_print(p, " is DIE !!!!!!!!!!!!!!!!!!!!"); //modif message
			p->glob->is_die = 1;
			//pthread_mutex_unlock(&p->glob->print_m);		
			return (NULL);
		}
		if (p->glob->notepme > 0)
			if (checker_max_meals(p->glob))
				return (NULL);
		usleep(1000);
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
		if (g->notepme < 0)
		{
			if (pthread_create(&g->tab_th[i], NULL, &states, p))
				return (printerr(THDERR));
			
		}
		else
		{
			printf("\ntest1\n");
			if (pthread_create(&g->tab_th[i], NULL, &states_max_eat, p))
				return (printerr(THDERR));
			printf("\ntest2\n");
		}
		pthread_detach(g->tab_th[i]);
		usleep(100);
		printf("\ntest3\n");
		i++;
	}
	return (0);
}

int		parse_args(int argc, char **argv, t_glob *g)
{
	/*
	** a enlever attention
	** -----------------------
	*/
	if (argc == 2)
	{
		g->nop = 5;
		g->ttd = 4000;
		g->tte = 4000;
		g->tts = 4000;
		g->notepme = 3;
	}
	else
	{ // ---------------------
		if (argc < 5 || argc > 6)
			return (printerr(INVNB));
		if (!(g->nop = ft_atoi(argv[1])) || !(g->ttd = ft_atoi(argv[2])) 
			|| !(g->tte = ft_atoi(argv[3])) || !(g->tts = ft_atoi(argv[4])))
			return (printerr(INVVAL));
		if (argc == 5)
			g->notepme = -1;
		else
		{
			if ((g->notepme = ft_atoi(argv[5])) <= 0)
				return (printerr(INVVAL));
		}
	} // --------------
	return (0);
}

/*
** TODO
*/
//printf("\ntest\n");
//micro =  10^-6
//milli =  10^^-3
//modif putstr endl etc dans mylib
// verif si il faut faire gettime au tout debut pour le time_start


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
	while (!g.is_die) //&& g.meals_max_count < g.notepme)  //meals max count a -2 ou 0 merci
		usleep(1000);
	free_all(&g, 0);
	return (0);
}