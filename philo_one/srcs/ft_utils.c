/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:03:11 by judecuyp          #+#    #+#             */
/*   Updated: 2021/01/18 19:25:04 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		get_time(long long unsigned int *time, t_glob *g)
{
	struct timeval t;

	if (gettimeofday(&t, NULL) < 0)
		return (printerr(TIMERR, g));
	*time = (long long unsigned int)((t.tv_sec * 1000) + (t.tv_usec / 1000));
	*time = *time - g->time_start;
	return (0);
}

int		get_start_time(long long unsigned int *time, t_glob *g)
{
	struct timeval t;

	if (gettimeofday(&t, NULL) < 0)
		return (printerr(TIMERR, g));
	*time = (long long unsigned int)((t.tv_sec * 1000) + (t.tv_usec / 1000));
	return (0);
}

int		free_all(t_glob *g, int err)
{
	int i;

	i = 0;
	usleep(100);
	if (g->forks_m)
	{
		while (i < g->nop)
			pthread_mutex_destroy(&g->forks_m[i++]);
		free(g->forks_m);
	}
	pthread_mutex_destroy(&g->eat_max_m);
	if (g->phil)
		free(g->phil);
	if (g->tab_th)
		free(g->tab_th);
	return (err);
}

int		nb_len(int nb)
{
	int i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

void	utos(unsigned int nb, char str[255], int i)
{
	if (nb > 9)
	{
		utos(nb / 10, str, i - 1);
	}
	str[i] = nb % 10 + '0';
}
