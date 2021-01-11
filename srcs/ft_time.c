/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 21:31:14 by judecuyp          #+#    #+#             */
/*   Updated: 2020/11/18 21:31:14 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
** I use an adress for the time because 
** I need to return a negative number
*/

int		get_time(long long unsigned int *time, long long unsigned int t_start)
{
	struct					timeval t;

	if (gettimeofday(&t, NULL) < 0)
		return (printerr(TIMERR));
	*time = (long long unsigned int)((t.tv_sec * 1000) + (t.tv_usec / 1000));
	*time = *time - t_start;
	return (0);
}

int		get_start_time(long long unsigned int *time)
{
	struct					timeval t;

	if (gettimeofday(&t, NULL) < 0)
		return (printerr(TIMERR));
	*time = (long long unsigned int)((t.tv_sec * 1000) + (t.tv_usec / 1000)); 
	return (0);
}
