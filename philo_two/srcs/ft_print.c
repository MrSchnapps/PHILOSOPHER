/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 22:22:05 by judecuyp          #+#    #+#             */
/*   Updated: 2021/01/18 20:06:16 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int		print_join(unsigned int time, int order, char *msg,
	char str[255])
{
	int		len_time;
	int		len_order;
	int		i;

	len_time = nb_len(time);
	len_order = nb_len(order);
	utos(time, str, len_time - 1);
	str[len_time] = ' ';
	len_order += len_time;
	utos(order, str, len_order);
	i = 0;
	len_order += 1;
	while (msg[i])
		str[len_order++] = msg[i++];
	str[len_order] = '\0';
	return (len_order);
}

int				ft_print_end(t_phil *p, int code)
{
	long long unsigned int	cur_time;

	if (!p->glob->is_die)
	{
		if (get_time(&cur_time, p->glob) < 0)
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
	}
	return (0);
}

void			ft_print(t_phil *p, char *msg)
{
	long long unsigned int	cur_time;
	char					str[255];
	int						len;

	if (!p->glob->die_tester)
	{
		get_time(&cur_time, p->glob);
		len = print_join((int)cur_time, p->order, msg, str);
		write(1, str, len);
	}

}

void			ft_print_eat(t_phil *p, char *msg)
{
	long long unsigned int	cur_time;
	char					str[255];
	int						len;

	if (!p->glob->die_tester)
	{
		get_time(&cur_time, p->glob);
		p->last_eat = cur_time;
		len = print_join((unsigned int)cur_time, p->order, msg, str);
		write(1, str, len);
	}
}

int				printerr(int ret, t_glob *g)
{
	sem_wait(g->print_sem);
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
	g->is_die = 1;
	return (ret);
}
