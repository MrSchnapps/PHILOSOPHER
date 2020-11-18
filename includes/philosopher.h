/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 21:26:54 by judecuyp          #+#    #+#             */
/*   Updated: 2020/11/18 21:26:54 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <sys/time.h>
# include "../lib/includes/libft.h"

/*
** Errors
*/

# define MERR 3
# define TIMERR -1

/*
** time macros (a virer peut être ?????)
*/

# define START_TIME_CODE 1
# define CURR_TIME_CODE 2
 
/*
** Print code
*/

/*# define EAT_MSG "is eating.\n"
# define SLEEP_MSG "is sleeping.\n"
# define FORK_MSG "take a fork.\n"*/

typedef struct 	s_phil
{
	int				order;
	int				is_eat;
	int				is_sleep;
	struct s_glob	*glob;
	
	//int							cur_phil;
	//int							nop;
	//pthread_t					*tab_th;
	//int							ttd;
	//int							tte;
	//int							tts;
	//int							notepme;
	//long long unsigned int		time_start;
	//long long unsigned int		cur_time;
	pthread_mutex_t				print_m;
}				t_phil;

typedef struct		s_glob
{
	//int							cur_phil;

	int							nop; 		// int number_of_philosopher;
	int							ttd; 		// int time_to_die;
	int							tte; 		// int time_to_eat;
	int							tts; 		// int time_to_sleep;
	int							notepme;	// int number_of_time_each_philosophers_must_eat;
	t_phil						*phil;
	pthread_t					*tab_th;
	pthread_mutex_t				print_m;
	long long unsigned int		time_start;
	long long unsigned int		cur_time;
}					t_glob;

/*
** Time
*/

int		get_time(long long unsigned int *time);

/*
** Errors
*/

int		printerr(char *err, int ret);

/*
** Free
*/

int		free_all(t_glob *g, int err);

/*
** Print
*/

int		ft_print(t_phil *p, char *msg);
#endif