/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 21:19:44 by judecuyp          #+#    #+#             */
/*   Updated: 2021/01/18 19:40:48 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int		get_ret(pid_t pid)
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

static void		tension(t_glob *g)
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
		if (ret == ERR)
			kill(0, SIGQUIT);
		i++;
		if (i == g->nop)
			i = 0;
		usleep(30);
	}
	check_end(g, ret);
}

static void		*checker_death(void *arg)
{
	t_phil					*p;
	long long unsigned int	cur_time;

	p = (t_phil *)arg;
	while (!p->glob->is_die)
	{
		if (get_time(&cur_time, p->glob->time_start))
			exit(ERR);
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

void			states(void *arg)
{
	t_phil		*p;
	pthread_t	id;

	p = (t_phil *)arg;
	if (pthread_create(&id, NULL, &checker_death, arg))
		exit(ERR);
	pthread_detach(id);
	while (!p->glob->is_die)
	{
		start_forks(p);
		eating(p);
		sleeping(p);
		thinking(p);
	}
	exit(19);
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
	tension(&g);
	free_all(&g, 0);
	return (0);
}
