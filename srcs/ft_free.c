/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 21:44:43 by judecuyp          #+#    #+#             */
/*   Updated: 2020/11/18 21:44:43 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int		free_all(t_glob *g, int err)
{
	if (g->tab_th)
		free(g->tab_th);
	if (g->phil)
		free(g->phil);
	return (err);
}