/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 14:49:49 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/16 14:57:53 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	ft_putnbr_fd(t_long_num n, int fd)
{
	t_long_num	l;
	char		buff;

	l = n;
	if (l < 0)
	{
		write(fd, "-", 1);
		l *= -1;
	}
	if (l >= 10)
	{
		buff = l % 10 + 48;
		ft_putnbr_fd(l / 10, fd);
		write(fd, &buff, 1);
	}
	else if (l < 10)
	{
		buff = l + 48;
		write(fd, &buff, 1);
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	while (*s)
	{
		write(fd, &(*s), 1);
		s++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

int	ft_atoi(const char *str)
{
	long long	num;
	const char	*ptr;

	ptr = str;
	num = 0;
	while (*str)
	{
		if (*str < 48 || *str > 57)
			return (-1);
		str++;
	}
	while (*ptr)
	{
		if (num > MAX_INT)
			return (-1);
		num = num * 10 + (*ptr - '0');
		ptr++;
	}
	return (num);
}
