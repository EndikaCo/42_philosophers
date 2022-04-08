/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:57:18 by ecorreia          #+#    #+#             */
/*   Updated: 2022/04/08 17:40:59 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_think(t_philo *_philo)
{
	ft_check_dead(_philo);
	ft_print(_philo, "is thinking", 0);
	if (ft_isodd(_philo->_data->num_philos))
		ft_udelay(_philo, _philo->_data->time_eat);
	usleep(1);
}

void	ft_sleep(t_philo *_philo)
{
	ft_check_dead(_philo);
	ft_print(_philo, "is sleeping", 0);
	ft_udelay(_philo, _philo->_data->time_sleep);
	ft_think(_philo);
}

void	ft_eat(t_philo *_philo)
{
	int	right_fork;

	if (_philo->id == 0)
		right_fork = _philo->_data->num_philos -1;
	else
		right_fork = _philo->id - 1;
	usleep(100);
	if (_philo->_data->fork_in_use[_philo->id] == _philo->id
		&& _philo->_data->fork_in_use[right_fork] == _philo->id)
	{
		ft_check_dead(_philo);
		_philo->n_meals++;
		ft_print(_philo, "is eating", 0);
		gettimeofday(&_philo->time1, NULL);
		_philo->last_eat = ft_time(_philo->time1, _philo);
		ft_udelay(_philo, _philo->_data->time_eat);
		_philo->_data->fork_in_use[_philo->id] = -1;
		_philo->_data->fork_in_use[right_fork] = -1;
		ft_sleep(_philo);
	}
}

void	ft_take_fork(t_philo *_philo)
{	
	int	right_fork;

	if (_philo->id == 0)
		right_fork = _philo->_data->num_philos -1;
	else
		right_fork = _philo->id - 1;
	pthread_mutex_lock(&_philo->_data->mutx_forks[_philo->id]);
	pthread_mutex_lock(&_philo->_data->mutx_forks[right_fork]);
	ft_check_dead(_philo);
	if (_philo->_data->fork_in_use[_philo->id] == -1
		&& _philo->_data->fork_in_use[right_fork] == -1)
	{
		_philo->_data->fork_in_use[_philo->id] = _philo->id;
		ft_print(_philo, "has taken a fork", 0);
		_philo->_data->fork_in_use[right_fork] = _philo->id;
		ft_print(_philo, "has taken a fork", 0);
	}
	pthread_mutex_unlock(&_philo->_data->mutx_forks[_philo->id]);
	pthread_mutex_unlock(&_philo->_data->mutx_forks[right_fork]);
}

/**
 * @brief waits time defined by delay variable
 * @param delay this is the time to wait (in milliseconds)
 */
void	ft_udelay(t_philo *_philo, int delay)
{
	struct timeval	start;
	struct timeval	end;
	int				time;

	time = 0;
	gettimeofday(&start, NULL);
	gettimeofday(&end, NULL);
	while (ft_getime(end) - ft_getime(start) < delay)
	{	
		gettimeofday(&end, NULL);
		if (ft_getime(end) - ft_getime(start) - time > 10)
			time += 10;
		ft_check_dead(_philo);
		usleep(100);
	}
}
