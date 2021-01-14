/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_forks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 20:08:51 by judecuyp          #+#    #+#             */
/*   Updated: 2021/01/04 20:08:51 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		start_forks(t_phil *p)
{
	sem_wait(p->glob->forks_sem);
	sem_wait(p->glob->forks_sem);
	sem_wait(p->glob->print_sem);
	if (!p->glob->die_tester)
	{
		if (ft_print(p, " has taken a fork\n"))
			return (ERR);
		if (ft_print(p, " has taken a fork\n"))
			return (ERR);
	}
	sem_post(p->glob->print_sem);
	return (SUCCESS);
}

void	unlock_forks(t_phil *p)
{
	if (!p->glob->die_tester)
	{
		sem_post(p->glob->forks_sem);
		sem_post(p->glob->forks_sem);
	}
}

int		eating(t_phil *p)
{
	if (!p->glob->die_tester)
	{
		sem_wait(p->glob->print_sem);
		p->is_eating = 1;
		if (ft_print_eat(p, " is eating\n"))
			return (ERR);
		sem_post(p->glob->print_sem);
		usleep(p->glob->tte * 1000);
		unlock_forks(p);
		p->nb_of_eat += 1;
		p->is_eating = 0;
	}
	return (SUCCESS);
}

int		sleeping(t_phil *p)
{
	if (!p->glob->die_tester)
	{
		sem_wait(p->glob->print_sem);
		if (ft_print(p, " is sleeping\n"))
			return (ERR);
		sem_post(p->glob->print_sem);
		usleep(p->glob->tts * 1000);
	}
	return (SUCCESS);
}

int		thinking(t_phil *p)
{
	if (!p->glob->die_tester)
	{
		sem_wait(p->glob->print_sem);
		if (ft_print(p, " is thinking\n"))
			return (ERR);
		sem_post(p->glob->print_sem);
	}
	return (SUCCESS);
}
