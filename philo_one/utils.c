/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 14:50:18 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/16 15:03:46 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

t_long_num	get_time(void)
{
	struct timeval			time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * (t_long_num)1000 + time.tv_usec / 1000);
}

void	ft_usleep(t_long_num time)
{
	t_long_num	start;
	t_long_num	stop;

	start = get_time();
	stop = get_time() + time;
	while (start < stop)
	{
		usleep(100);
		start = get_time();
	}
}

void	message(t_long_num timestamp, int number, char *state)
{
	ft_putnbr_fd(timestamp, 1);
	ft_putstr_fd("\t", 1);
	ft_putnbr_fd(number, 1);
	ft_putendl_fd(state, 1);
}
