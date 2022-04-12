/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:39:25 by ecorreia          #+#    #+#             */
/*   Updated: 2022/04/12 20:51:56 by ecorreia         ###   ########.fr       */
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

/**
 * @brief get the actual time in millisecs since process creation
 * @param time1 structure of time
 * @return long int with actual time in milliseconds
 */
long int	ft_getime(struct timeval time1)
{
	return ((time1.tv_sec * 1000) + (time1.tv_usec / 1000));
}

/**
 * @brief get the start time minus the time sent by parameter
 * @param time to compare with
 * @return long int  returns the start time minus the time sent by parameter
 */
long int	ft_time(struct timeval time, t_philo *_philo)
{
	return (ft_getime(time) - ft_getime(_philo->_data->start_time));
}

/**
 * @brief checks if is pair or odd
 * @param n number to check
 * @return int 1 if off, and 0 if is pair
 */
int	ft_isodd(int n)
{
	return (n & 1);
}
