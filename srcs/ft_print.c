/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 22:22:05 by judecuyp          #+#    #+#             */
/*   Updated: 2020/11/18 22:22:05 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

//todo
// attention ordre time et mutex 
int		ft_print(t_phil *p, char *msg)
{
	long long unsigned int cur_time;

	if (get_time(&cur_time) < 0)
		return (printerr("Time error", TIMERR));
	pthread_mutex_lock(&p->glob->print_m);
	ft_putnbr_fd(cur_time - p->glob->time_start, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(p->order, 1);
	ft_putstr_fd(msg, 1);
	pthread_mutex_unlock(&p->glob->print_m);
	return (0);
}
