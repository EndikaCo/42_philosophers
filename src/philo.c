/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:32:03 by ecorreia          #+#    #+#             */
/*   Updated: 2022/03/03 19:59:52 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
		if (!ft_isodd(_philo->id) && _philo->id != _philo->_data->num_philos - 1)
			_philo->group = 1;
		else if (ft_isodd(_philo->id))
			_philo->group = 2;
		if (!ft_isodd(_philo->id) && _philo->id != 0)
			_philo->group = 3;
	}
}

void	ft_get_next_id(t_philo *_philo)
{
	pthread_mutex_lock(&_philo->_data->mutx_id);
	_philo->id = _philo->_data->next_id++;
	pthread_mutex_unlock(&_philo->_data->mutx_id);
}

void	ft_wait_start(t_philo *_philo)
{
	struct timeval	timer;

	gettimeofday(&timer, NULL);
	while(ft_getime(timer) - ft_getime(_philo->_data->start_time) < 10 * _philo->_data->num_philos)
		gettimeofday(&timer, NULL);
	usleep(10);
	gettimeofday(&_philo->_data->start_time, NULL);
	_philo->_data->start = 1;
	
}

void	ft_print(t_philo *_philo, char *str, int dead)
{
	struct timeval	actual_time;
	
	pthread_mutex_lock(&_philo->_data->mutx_dead);
	if(_philo->_data->start)
	{
		gettimeofday(&actual_time, NULL);
		if(dead == 1)
		{
			_philo->_data->start = 0;
		}
		printf("%ld %d %s\n",  ft_time(actual_time, _philo), _philo->id, str);
	
		pthread_mutex_unlock(&_philo->_data->mutx_dead);
	}
	else
		exit(0);
}

void	ft_check_dead(t_philo *_philo)
{	
	struct timeval	actual_time;
	gettimeofday(&actual_time, NULL);
	
	if (ft_time(actual_time, _philo) - _philo->last_eat > _philo->_data->time_die)
		ft_print(_philo, "is dead", 1);
}

