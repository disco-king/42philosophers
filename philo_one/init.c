/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 14:49:43 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/16 14:53:56 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->num_of_philos);
	if (data->philos == NULL)
		return (1);
	while (i < data->num_of_philos)
	{
		data->philos[i].position = i;
		data->philos[i].data = data;
		data->philos[i].times_eaten = 0;
		data->philos[i].full = &(data->philos_full);
		i++;
	}
	return (0);
}

void	give_forks(t_data *data, int i)
{
	int	right;

	right = (i + 1) % data->num_of_philos;
	data->philos[i].left_fork = &(data->forks[i]);
	data->philos[i].right_fork = &(data->forks[right]);
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->num_of_philos);
	if (data->forks == NULL)
		return (1);
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
		{
			free(data->forks);
			return (1);
		}
		i++;
	}
	data->speech = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (data->speech == NULL || pthread_mutex_init(data->speech, NULL))
	{
		ft_putendl_fd("speech init failed", 2);
		return (1);
	}
	return (0);
}

int	init_all(t_data *data)
{
	int	i;

	if (init_philos(data))
	{
		return (1);
	}
	if (init_mutexes(data))
	{
		free(data->speech);
		free(data->forks);
		free(data->philos);
		return (1);
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i].speech = data->speech;
		give_forks(data, i);
		i++;
	}
	return (0);
}
