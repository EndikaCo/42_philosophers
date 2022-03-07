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

long int	ft_getime(struct timeval time1)
{
	return ((time1.tv_sec * 1000) + (time1.tv_usec / 1000));
}
/*
long int	ft_millis(t_philo *_philo)
{
	return (((_philo->time1.tv_sec * 1000) + (_philo->time1.tv_usec / 1000))
		- ((_philo->_data->start_time.tv_sec * 1000) + (_philo->_data->start_time.tv_usec / 1000)));
}*/

long int	ft_millis(t_philo *_philo)
{
	return (ft_getime(_philo->time1) - ft_getime(_philo->_data->start_time));
}

  
//od es inpar
int	isodd(int n)
{
	return (n & 1);
}

int is_dead(t_philo *philo)
{
    struct timeval time;
    long int period;

    gettimeofday(&time, NULL);
    period = (time.tv_sec * 1000 + time.tv_usec / 1000) - (philo->last_eat.tv_sec * 1000 + philo->last_eat.tv_usec / 1000);
    printf("%ld\n", period);
	if (period > philo->_data->time_die)
        return (1);
    return (0);
}
/*
int ft_check_dead2(t_philo *philo)
{
    pthread_mutex_lock(&philo->_data->mutx_dead);
    if (philo->_data->death)
    {
        pthread_mutex_unlock(&philo->_data->mutx_dead);
		philo->_data->start=0;///////////////////////////////////////
		//printf("%ld %d died\n", ft_millis(philo) , philo->id);
        return(1);
    }


    if (is_dead(philo))
    {
        philo->_data->death = 1;
        pthread_mutex_unlock(&philo->_data->mutx_dead);
        printf("%ld %d died\n", ft_millis(philo) , philo->id);
        return (1);
    }
    pthread_mutex_unlock(&philo->_data->mutx_dead);
    return (0);
}
*/