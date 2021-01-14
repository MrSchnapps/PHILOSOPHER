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

//** démarrer le prog à 0 secondes


#include "philo_three.h"

int		get_ret(pid_t pid)
{
	int ret;

	ret = 0;
	waitpid(pid, &ret, WNOHANG);
	if (WIFEXITED(ret))
	{
		if (WEXITSTATUS(ret) == DIED_EXIT)
			return (DIED_EXIT);
		else if (WEXITSTATUS(ret) == ALL_MEAT_EXIT)
				return (ALL_MEAT_EXIT);
	}
	return (0);
}

void	tension(t_glob *g)
{
	int i;
	int ret;

	i = 0;
	while (i < g->nop)
	{
		ret = get_ret(g->tab_pid[i]);
		if (ret == DIED_EXIT)
			break ;
		if (ret == ALL_MEAT_EXIT)
		{
			g->meals_max_count += 1;
			if (g->meals_max_count == g->nop)
				break ;
		}
		i++;
		if (i == g->nop)
			i = 0;
		usleep(30);
	}
	while (i < g->nop)
		kill(g->tab_pid[i++], SIGKILL);
	if (ret == ALL_MEAT_EXIT)
		if (ft_print_end(&g->phil[0], 2))
			(exit(ERR));
}

void	*checker_death(void *arg)
{
	t_phil					*p;
	long long unsigned int 	cur_time;

	p = (t_phil *)arg;
	while (1)
	{
		if (get_time(&cur_time, p->glob->time_start))
			return (exit(ERR));
		if (!p->is_eating && cur_time > (p->glob->ttd + p->last_eat))
		{
			sem_wait(p->glob->print_sem);
			ft_print_end(p, 1);
			p->glob->is_die = 1;		
			exit(DIED_EXIT);
		}
		if (p->glob->notepme > 0)
		{
			if (p->nb_of_eat == p->glob->notepme)
				exit(ALL_MEAT_EXIT);
		}
		usleep(35);
	}
	return (NULL);
}


void	states(void *arg)
{
	t_phil		*p;
	pthread_t	id;

	p = (t_phil *)arg;
	if (get_time(&p->last_eat, p->glob->time_start) < 0)
		exit(ERR);
	if (pthread_create(&id, NULL, &checker_death, arg))
		exit(ERR);
	pthread_detach(id);
	while (!p->glob->is_die)
	{
		if (start_forks(p))
			exit(ERR);
		if (eating(p))
			exit(ERR);
		if (sleeping(p))
			exit(ERR);
		if (thinking(p))
			exit(ERR);
	}
	exit(19);
}

int		starting_threads(t_glob *g)
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
	tension(&g);
	free_all(&g, 0);
	return (0);
}
