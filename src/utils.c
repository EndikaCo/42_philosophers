/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:39:25 by ecorreia          #+#    #+#             */
/*   Updated: 2022/03/03 19:39:58 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(const char *nptr)
{
	int	num;
	int	sign;
	int	i;

	num = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\r' || nptr[i] == '\v' || nptr[i] == '\f')
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] != '\0')
	{
		if (nptr[i] < '0' || nptr[i] > '9')
			return (sign * num);
		num = num * 10 + nptr[i++] - '0';
	}
	return (sign * num);
}

long int	ft_millis(struct timeval time1)
{
	return ((time1.tv_sec * 1000) + (time1.tv_usec / 1000));
}

long int	ft_millis(struct timeval time1)
{
	return ((time1.tv_sec * 1000) + (time1.tv_usec / 1000));
}

//od es inpar
int	isodd(int n)
{
	return (n & 1);
}
