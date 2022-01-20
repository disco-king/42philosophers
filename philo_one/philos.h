/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 15:01:55 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/16 15:01:55 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H

# define PHILOS_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>

# define FORK " has taken a fork"
# define EAT " is eating"
# define SLEEP " is sleeping"
# define THINK " is thinking"
# define DIED " died"

# define MAX_INT 2147483647

typedef unsigned long long	t_long_num;
typedef struct s_philo		t_philo;

typedef struct s_data{
	int				num_of_philos;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				eat_limit;
	int				philos_full;
	t_long_num		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*speech;
	t_philo			*philos;
}	t_data;

typedef struct s_philo{
	int				position;
	int				time_left;
	int				is_eating;
	int				times_eaten;
	int				*full;
	t_long_num		last_eat_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*speech;
	t_data			*data;
}	t_philo;

void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(t_long_num n, int fd);
void		ft_putendl_fd(char *s, int fd);
int			init_all(t_data *data);
int			init_mutexes(t_data *data);
void		give_forks(t_data *data, int i);
int			init_philos(t_data *data);
t_long_num	get_time(void);
int			launch(t_data *data);
void		*routine(void *arg);
void		ft_usleep(t_long_num time);
void		message(t_long_num timestamp, int number, char *state);
int			ft_atoi(const char *str);

#endif