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

//verif retour du gettime pour msg error
int		get_time(long long unsigned int *time)
{
	struct					timeval t;
	struct					timezone tz;

	if (gettimeofday(&t, &tz) < 0)
		return (printerr("Time error", TIMERR)); //attention retourner errno ou jsp quoi
	*time = (long long unsigned int)((t.tv_sec * 1000) + (t.tv_usec / 1000)); 
	return (0);
}