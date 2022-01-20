/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 14:50:12 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/20 14:14:07 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_t *first = philo->left_fork;
	pthread_mutex_t *second = philo->right_fork;
	if(philo->position + 1 == philo->data->num_of_philos)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(first);
	pthread_mutex_lock(philo->speech);
	ft_putnbr_fd(get_time() - philo->data->start_time, 1);
	ft_putstr_fd("\t", 1);
	ft_putnbr_fd(philo->position + 1, 1);
	ft_putendl_fd(FORK, 1);
	pthread_mutex_unlock(philo->speech);
	pthread_mutex_lock(second);
	pthread_mutex_lock(philo->speech);
	ft_putnbr_fd(get_time() - philo->data->start_time, 1);
	ft_putstr_fd("\t", 1);
	ft_putnbr_fd(philo->position + 1, 1);
	ft_putendl_fd(FORK, 1);
	pthread_mutex_unlock(philo->speech);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->speech);
	ft_putnbr_fd(get_time() - philo->data->start_time, 1);
	ft_putstr_fd("\t", 1);
	ft_putnbr_fd(philo->position + 1, 1);
	ft_putendl_fd(SLEEP, 1);
	pthread_mutex_unlock(philo->speech);
	ft_usleep(philo->data->to_sleep);
}

void	ft_eat(t_philo *philo)
{
	philo->last_eat_time = get_time();
	pthread_mutex_lock(philo->speech);
	ft_putnbr_fd(get_time() - philo->data->start_time, 1);
	ft_putstr_fd("\t", 1);
	ft_putnbr_fd(philo->position + 1, 1);
	ft_putendl_fd(EAT, 1);
	pthread_mutex_unlock(philo->speech);
	ft_usleep(philo->data->to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->times_eaten++;
}

void	ft_think(t_philo *philo)
{
	pthread_mutex_lock(philo->speech);
	ft_putnbr_fd(get_time() - philo->data->start_time, 1);
	ft_putstr_fd("\t", 1);
	ft_putnbr_fd(philo->position + 1, 1);
	ft_putendl_fd(THINK, 1);
	pthread_mutex_unlock(philo->speech);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		limit;

	philo = (t_philo *)arg;
	limit = philo->data->eat_limit;
	while (1)
	{
		take_forks(philo);
		ft_eat(philo);
		if (limit && philo->times_eaten == philo->data->eat_limit)
		{
			*(philo->full) += 1;
		}
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}
