/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 14:49:37 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/16 15:53:59 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	check_death(t_data *data, int i)
{
	pthread_mutex_lock(data->speech);
	if (get_time() - data->philos[i].last_eat_time > (t_long_num)data->to_die)
	{
		message(get_time() - data->start_time, i + 1, DIED);
		return (1);
	}
	pthread_mutex_unlock(data->speech);
	return (0);
}

int	launch_half(t_data *data, int half)
{
	int			i;
	pthread_t	thread;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (i % 2 == half)
		{
			data->philos[i].last_eat_time = data->start_time;
			if (pthread_create(&thread, NULL, routine, &data->philos[i]))
			{
				pthread_mutex_lock(data->speech);
				return (1);
			}
			pthread_detach(thread);
		}
		i++;
	}
	return (0);
}

void	*monitoring(void *data_v)
{
	int		i;
	t_data	*data;

	data = (t_data *)data_v;
	while (1)
	{
		if (data->philos_full >= data->num_of_philos)
		{
			pthread_mutex_lock(data->speech);
			ft_putendl_fd("eat limit reached", 2);
			break ;
		}
		i = 0;
		while (i < data->num_of_philos)
		{
			if (check_death(data, i))
			{
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

int	launch(t_data *data)
{
	pthread_t	thread;

	data->philos_full = 0;
	data->start_time = get_time();
	if (launch_half(data, 0))
		return (1);
	usleep(10000);
	if (launch_half(data, 1))
		return (1);
	if (pthread_create(&thread, NULL, monitoring, data))
	{
		pthread_mutex_lock(data->speech);
		return (1);
	}
	pthread_join(thread, NULL);
	return (0);
}
