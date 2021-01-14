/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:31:14 by judecuyp          #+#    #+#             */
/*   Updated: 2021/01/14 16:18:30 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

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
# define FORKERR 7

/*
** Exit code
*/

# define DIED_EXIT 19
# define ALL_MEAT_EXIT 20

typedef struct	s_phil
{
	int							order;
	int							is_eating;
	int							nb_of_eat;
	int							is_sleeping;
	int							max_time;
	long long unsigned int		last_eat;
	struct s_glob				*glob;
}				t_phil;

typedef struct	s_glob
{
	int							nop;
	long long unsigned int		ttd;
	int							tte;
	int							tts;
	int							notepme;
	int							is_die;
	int							die_tester;
	int							meals_max_count;
	t_phil						*phil;
	pid_t						*tab_pid;
	sem_t						*forks_sem;
	sem_t						*print_sem;
	long long unsigned int		time_start;
}				t_glob;

/*
** Utils
*/

int				get_time(long long unsigned int *time,
		long long unsigned int t_start);
int				get_start_time(long long unsigned int *time);
int				free_all(t_glob *g, int err);
int				nb_len(int nb);
void			utos(int nb, char *str, int i);

/*
** Lib
*/

int				ft_atoi(const char *nptr);
int				ft_strlen(char const *str);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

/*
** Print
*/

int				ft_print(t_phil *p, char *msg);
int				ft_print_end(t_phil *p, int code);
int				ft_print_eat(t_phil *p, char *msg);
int				printerr(int ret);

/*
** Init
*/

int				ft_init(t_glob *g);
int				parse_args(int argc, char **argv, t_glob *g);

/*
** States
*/

int				start_forks(t_phil *p);
void			unlock_forks(t_phil *p);
int				eating(t_phil *p);
int				sleeping(t_phil *p);
int				thinking(t_phil *p);
#endif
