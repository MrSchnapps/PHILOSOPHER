/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_states.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 20:08:51 by judecuyp          #+#    #+#             */
/*   Updated: 2021/01/18 20:00:33 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		start_forks(t_phil *p)
{
	pthread_mutex_lock(&p->glob->forks_m[p->r_fork]);
	pthread_mutex_lock(&p->glob->forks_m[p->l_fork]);
	pthread_mutex_lock(&p->glob->print_m);
	ft_print(p, " has taken a fork\n");
	ft_print(p, " has taken a fork\n");
	pthread_mutex_unlock(&p->glob->print_m);
	return (SUCCESS);
}

void	unlock_forks(t_phil *p)
{
	pthread_mutex_unlock(&p->glob->forks_m[p->r_fork]);
	pthread_mutex_unlock(&p->glob->forks_m[p->l_fork]);
}

int		eating(t_phil *p)
{
	pthread_mutex_lock(&p->glob->print_m);
	p->is_eating = 1;
	ft_print_eat(p, " is eating\n");
	pthread_mutex_unlock(&p->glob->print_m);
	usleep(p->glob->tte * 1000);
	unlock_forks(p);
	p->is_eating = 0;
	p->nb_of_eat += 1;
	if (p->nb_of_eat == p->glob->notepme)
	{
		pthread_mutex_lock(&p->glob->eat_max_m);
		p->glob->meals_max_count += 1;
		pthread_mutex_unlock(&p->glob->eat_max_m);
	}
	return (SUCCESS);
}

int		sleeping(t_phil *p)
{
	pthread_mutex_lock(&p->glob->print_m);
	ft_print(p, " is sleeping\n");
	pthread_mutex_unlock(&p->glob->print_m);
	usleep(p->glob->tts * 1000);
	return (SUCCESS);
}

int		thinking(t_phil *p)
{
	pthread_mutex_lock(&p->glob->print_m);
	ft_print(p, " is thinking\n");
	pthread_mutex_unlock(&p->glob->print_m);
	return (SUCCESS);
}
