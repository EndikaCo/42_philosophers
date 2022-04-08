/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:32:03 by ecorreia          #+#    #+#             */
/*   Updated: 2022/04/08 19:05:43 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief puts the philosopher in a group depending on whether 
 * it is even or uneven
 */
void	ft_join_group(t_philo *_philo)
{
	if (!ft_isodd(_philo->_data->num_philos))
	{
		if (ft_isodd(_philo->id))
			_philo->group = 1;
		else
			_philo->group = 2;
	}
	if (ft_isodd(_philo->_data->num_philos))
	{
		if (!ft_isodd(_philo->id) && _philo->id
			!= _philo->_data->num_philos - 1)
			_philo->group = 1;
		else if (ft_isodd(_philo->id))
			_philo->group = 2;
		if (!ft_isodd(_philo->id) && _philo->id != 0)
			_philo->group = 3;
	}
}

/**
 * @brief get next id available protected with mutex to avoid duplicates
 */
void	ft_get_next_id(t_philo *_philo)
{
	pthread_mutex_lock(&_philo->_data->mutx_id);
	_philo->id = _philo->_data->next_id++;
	pthread_mutex_unlock(&_philo->_data->mutx_id);
}

/**
 * @brief what to do in case of one unique philosopher
 */
void	ft_one(t_philo *_philo)
{	
	printf("1 %d has taken a fork\n", _philo->id);
	usleep(_philo->_data->time_die);
	printf("%d %d is dead\n", _philo->_data->time_die, _philo->id);
	exit(0);
}

/**
 * @brief prints the status of the philosopher protected with mutex
 * @param str estate of the philosopher to print
 * @param dead return 0 if alive, else declares dead
 */
void	ft_print(t_philo *_philo, char *str, int dead)
{
	struct timeval	actual_time;

	pthread_mutex_lock(&_philo->_data->mutx_dead);
	if (_philo->_data->start)
	{
		gettimeofday(&actual_time, NULL);
		if (dead == 1)
			_philo->_data->start = 0;
		printf("%ld %d %s\n", ft_time(actual_time, _philo),
			_philo->id, str);
		pthread_mutex_unlock(&_philo->_data->mutx_dead);
	}
	else
		exit(0);
}

/**
 * @brief check if the philosopher is dead or not
 * to print the state
 */
void	ft_check_dead(t_philo *_philo)
{	
	struct timeval	actual_time;

	gettimeofday(&actual_time, NULL);
	if (ft_time(actual_time, _philo) - _philo->last_eat
		> _philo->_data->time_die)
		ft_print(_philo, "is dead", 1);
}
