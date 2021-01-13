/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:03:11 by judecuyp          #+#    #+#             */
/*   Updated: 2021/01/11 11:03:11 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		get_time(long long unsigned int *time, long long unsigned int t_start)
{
	struct	timeval t;

	if (gettimeofday(&t, NULL) < 0)
		return (printerr(TIMERR));
	*time = (long long unsigned int)((t.tv_sec * 1000) + (t.tv_usec / 1000));
	*time = *time - t_start;
	return (0);
}

int		get_start_time(long long unsigned int *time)
{
	struct	timeval t;

	if (gettimeofday(&t, NULL) < 0)
		return (printerr(TIMERR));
	*time = (long long unsigned int)((t.tv_sec * 1000) + (t.tv_usec / 1000)); 
	return (0);
}

int		free_all(t_glob *g, int err)
{
	int i;

	i = 0;
	if (g->tab_th)
		free(g->tab_th);
	if (g->forks_m)
	{
		while (i < g->nop)
			pthread_mutex_destroy(&g->forks_m[i++]);
		free(g->forks_m);
	}
	pthread_mutex_destroy(&g->print_m);
	pthread_mutex_destroy(&g->eat_max_m);
	if (g->phil)
		free(g->phil);
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

void	utos(int nb, char *str, int i)
{
	if (nb > 9)
	{
		utos(nb / 10, str, i - 1);
	}
	str[i] = nb % 10 + '0';
}
