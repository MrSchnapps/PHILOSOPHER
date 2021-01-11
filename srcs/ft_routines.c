/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:52:14 by judecuyp          #+#    #+#             */
/*   Updated: 2021/01/11 11:52:14 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*states_max_eat(void *arg)
{
	t_phil		*p;
	pthread_t	id;

	p = (t_phil *)arg;
	if (get_time(&p->last_eat, p->glob->time_start) < 0)
		return ((void *)ERR);
	if (pthread_create(&id, NULL, &checker_death, arg))
		return ((void *)ERR);
	pthread_detach(id);
	while (!p->glob->is_die && p->nb_of_eat < p->glob->notepme)
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
	if (!p->glob->is_die)
	{
		pthread_mutex_lock(&p->glob->eat_max_m);
		p->glob->meals_max_count += 1;
		pthread_mutex_unlock(&p->glob->eat_max_m);
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
