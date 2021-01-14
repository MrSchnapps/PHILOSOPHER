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

#include "philo_two.h"

static char		*print_join(int time, int order, char *msg)
{
	int		len_time;
	int		len_order;
	char	*str;
	int		i;

	len_time = nb_len(time);
	len_order = nb_len(order);
	if (!(str = (char *)malloc(len_time + len_order + ft_strlen(msg) + 2)))
		return (NULL);
	utos(time, str, len_time - 1);
	str[len_time] = ' ';
	len_order += len_time;
	utos(order, str, len_order);
	i = 0;
	len_order += 1;
	while (msg[i])
		str[len_order++] = msg[i++];
	str[len_order] = '\0';
	return (str);
}

int				ft_print_end(t_phil *p, int code)
{
	long long unsigned int	cur_time;

	if (get_time(&cur_time, p->glob->time_start) < 0)
		return (TIMERR);
	if (code == 1)
	{
		ft_putnbr_fd(cur_time, 1);
		write(1, " ", 1);
		ft_putnbr_fd(p->order, 1);
		write(1, " died\n", 6);
	}
	else if (code == 2)
	{
		ft_putnbr_fd(cur_time, 1);
		write(1, " All the meals has been eaten.\n", 31);
	}
	return (0);
}

int				ft_print(t_phil *p, char *msg)
{
	long long unsigned int	cur_time;
	char					*str;

	if (!p->glob->die_tester)
	{
		if (get_time(&cur_time, p->glob->time_start) < 0)
			return (TIMERR);
		if (!(str = print_join((int)cur_time, p->order, msg)))
			return (printerr(MERR));
		write(1, str, ft_strlen(str));
		free(str);
	}
	return (0);
}

int				ft_print_eat(t_phil *p, char *msg)
{
	long long unsigned int	cur_time;
	char					*str;

	if (!p->glob->die_tester)
	{
		if (get_time(&cur_time, p->glob->time_start) < 0)
			return (TIMERR);
		p->last_eat = cur_time;
		if (!(str = print_join((int)cur_time, p->order, msg)))
			return (printerr(MERR));
		write(1, str, ft_strlen(str));
		free(str);
	}
	return (0);
}

int			printerr(int ret)
{
	if (ret == MERR)
		ft_putendl_fd("Memory error", 2);
	else if (ret == TIMERR)
		ft_putendl_fd("Time error", 2);
	else if (ret == THDERR)
		ft_putendl_fd("Thread error", 2);
	else if (ret == INVNB)
		ft_putendl_fd("Wrong number of arguments", 2);
	else if (ret == INVVAL)
		ft_putendl_fd("Invalid value in arguments", 2);
	return (ret);
}
