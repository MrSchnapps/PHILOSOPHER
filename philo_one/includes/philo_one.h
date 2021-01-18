/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:32:30 by judecuyp          #+#    #+#             */
/*   Updated: 2021/01/18 19:59:49 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>

# define SUCCESS	0
# define ERR		1
# define MERR		3
# define TIMERR		-1
# define THDERR		4
# define INVNB		5
# define INVVAL		6

typedef struct	s_phil
{
	int						order;
	int						is_eating;
	int						nb_of_eat;
	int						is_sleeping;
	int						l_fork;
	int						r_fork;
	int						max_time;
	long long unsigned int	last_eat;
	struct s_glob			*glob;
}				t_phil;

typedef struct	s_glob
{
	int						nop;
	long long unsigned int	ttd;
	int						tte;
	int						tts;
	int						notepme;
	int						is_die;
	int						die_tester;
	int						meals_max_count;
	t_phil					*phil;
	pthread_t				*tab_th;
	pthread_mutex_t			*forks_m;
	pthread_mutex_t			print_m;
	pthread_mutex_t			eat_max_m;
	long long unsigned int	time_start;
}				t_glob;

int				get_time(long long unsigned int *time, t_glob *g);
int				get_start_time(long long unsigned int *time, t_glob *g);
int				free_all(t_glob *g, int err);
int				nb_len(int nb);
void			utos(unsigned int nb, char *str, int i);
int				ft_atoi(const char *nptr);
int				ft_strlen(char const *str);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_print(t_phil *p, char *msg);
int				ft_print_end(t_phil *p, int code);
void			ft_print_eat(t_phil *p, char *msg);
int				printerr(int ret, t_glob *g);
int				ft_init(t_glob *g);
int				parse_args(int argc, char **argv, t_glob *g);
int				start_forks(t_phil *p);
void			unlock_forks(t_phil *p);
int				eating(t_phil *p);
int				sleeping(t_phil *p);
int				thinking(t_phil *p);
#endif
