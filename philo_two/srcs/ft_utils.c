/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:03:11 by judecuyp          #+#    #+#             */
/*   Updated: 2021/01/18 19:30:30 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
	g->die_tester = 1;
	usleep(100);
	sem_unlink("forks");
	sem_unlink("eat_max");
	if (g->tab_th)
		free(g->tab_th);
	if (g->phil)
		free(g->phil);
	sem_unlink("print");
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
