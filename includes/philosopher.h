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

# define SUCCESS 0
# define ERR 1
# define MERR 3
# define TIMERR -1
# define THDERR 4
# define INVNB 5
# define INVVAL 6

/*
** time macros (a virer peut être ?????)
*/

# define START_TIME_CODE 1
# define CURR_TIME_CODE 2
# define DIE_CODE 1
# define MAX_EAT_CODE 1
# define ROUTINE_CODE 0

/*
** Print code
*/

/*# define EAT_MSG "is eating.\n"
# define SLEEP_MSG "is sleeping.\n"
# define FORK_MSG "take a fork.\n"*/

typedef struct 	s_phil
{
	int							order;
	int							is_eating;
	int							nb_of_eat;
	int							is_sleeping;
	int							l_fork;
	int							r_fork;
	int							max_time;
	long long unsigned int		last_eat;
	struct s_glob				*glob;
}				t_phil;

typedef struct		s_glob
{
	int							nop; 		// int number_of_philosopher;
	long long unsigned int		ttd; 		// int time_to_die;
	int							tte; 		// int time_to_eat;
	int							tts; 		// int time_to_sleep;
	int							notepme;	// int number_of_time_each_philosophers_must_eat;
	int							is_die;
	int							meals_max_count;
	t_phil						*phil;
	pthread_t					*tab_th; 	// tab of threads
	pthread_mutex_t				*forks_m;
	pthread_mutex_t				print_m;
	pthread_mutex_t				eat_max_m;
	long long unsigned int		time_start;
}					t_glob;

/*
** Time
*/

int		get_time(long long unsigned int *time, long long unsigned int t_start);
int		get_start_time(long long unsigned int *time);

/*
** Utils
*/

int		free_all(t_glob *g, int err);
int		nb_len(int nb);
void	utos(int nb, char *str, int i);

/*
** Print
*/

int		ft_print(t_phil *p, char *msg);
int		ft_print_all_meals(t_glob *g);
int		ft_print_eat(t_phil *p, char *msg);
int		printerr(int ret);

/*
** Init
*/

int		ft_init(t_glob *g);

/*
** States
*/

int		start_forks(t_phil *p);
void	unlock_forks(t_phil *p);
int		eating(t_phil *p);
int		sleeping(t_phil *p);
int		thinking(t_phil *p);

/*
** Routines
*/

void	*states_max_eat(void *arg);
void	*states(void *arg);
void	*checker_death(void *arg);
#endif