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

void	ft_join_group(t_philo *Philo)
{
	if (!isodd(Philo->_data->num_philos))
	{
		if (isodd(Philo->id))
			Philo->group = 1;
		else
			Philo->group = 2;
	}
	if (isodd(Philo->_data->num_philos))
	{
		if (!isodd(Philo->id) && Philo->id != Philo->_data->num_philos - 1)
			Philo->group = 1;
		else if (isodd(Philo->id))
			Philo->group = 2;
		if (!isodd(Philo->id) && Philo->id != 0)
			Philo->group = 3;
	}
	printf("%d is group %d\n", Philo->id, Philo->group);
}


void	ft_get_next_id(t_philo *Philo)
{
	pthread_mutex_lock(&Philo->_data->mutx_id);
	Philo->id = Philo->_data->next_id++;
	pthread_mutex_unlock(&Philo->_data->mutx_id);
}

void ft_wait_start(t_philo *_philo)
{
	struct timeval	timer;

	gettimeofday(&timer, NULL);

	//while(_philo->_data->next_id != _philo->_data->num_philos)
	usleep(5);
	
	while(ft_getime(timer) - ft_getime(_philo->_data->start_time) < 10 * _philo->_data->num_philos)
		gettimeofday(&timer, NULL);
	printf("timer now-->%ld\n", ft_getime(timer));
	gettimeofday(&_philo->_data->start_time, NULL);
	_philo->_data->start = 1;
}

void	ft_check_dead(t_philo *Philo)//////////////////////////
{	
	struct timeval	actual_time;
	gettimeofday(&actual_time, NULL);
	
	if (ft_getime(actual_time) - ft_getime(Philo->last_eat) > Philo->_data->time_die)
	{
		printf("%ld %d is dead\n", ft_millis(Philo), Philo->id);
		exit(0);
	}
}

void twogroup(t_philo *_philo)
{
	int i = 0;


	if(_philo->group == 1 && i == 0)
	{
		i = 1;
		usleep(5);
	}

	ft_take_fork(_philo);
	eat(_philo);
}

void trigroup(t_philo *_philo)
{
	int i = 0;

	if((_philo->group == 1 || _philo->group == 3) && i == 0)
	{
		i = 1;
		usleep(5);
	}
	ft_take_fork(_philo);
	eat(_philo);
}

void	*routine(void *arg)
{
	t_philo			_philo;
	
	_philo = *(t_philo *)arg;
	
	ft_get_next_id(&_philo);
	ft_join_group(&_philo);
	if(_philo.id == _philo._data->num_philos - 1)
		ft_wait_start(&_philo);

	while (1)
	{	
		_philo.last_eat = _philo._data->start_time;
		while (_philo._data->start == 1)
		{	
			if (_philo._data->num_philos == 1)
			{
				usleep(_philo._data->time_die);
				printf("%d %d is dead\n", _philo._data->time_die, _philo.id);
				exit(0);
			}
				
			if (!isodd(_philo._data->num_philos))
				twogroup(&_philo);
			if (isodd(_philo._data->num_philos))
				trigroup(&_philo);
		}
	}
	free(arg);
	return (NULL);
}
