/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 14:49:31 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/16 14:51:03 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	init_data(int argc, const char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		return (1);
	data->num_of_philos = ft_atoi(argv[1]);
	data->to_die = ft_atoi(argv[2]);
	data->to_eat = ft_atoi(argv[3]);
	data->to_sleep = ft_atoi(argv[4]);
	if (data->num_of_philos <= 0 || data->to_die <= 0
		|| data->to_eat <= 0 || data->to_sleep <= 0)
		return (1);
	if (argc == 6)
	{
		data->eat_limit = ft_atoi(argv[5]);
		if (data->eat_limit <= 0)
			return (1);
	}
	else
		data->eat_limit = 0;
	return (0);
}

int	main(int argc, char const *argv[])
{
	t_data	data;

	if (init_data(argc, argv, &data))
	{
		ft_putendl_fd("wrong args", 2);
		return (1);
	}
	if (init_all(&data))
	{
		ft_putendl_fd("initialization failed", 2);
		return (1);
	}
	launch(&data);
	free(data.speech);
	free(data.forks);
	free(data.philos);
	return (0);
}
