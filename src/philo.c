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
	//printf("timer now-->%ld\n", ft_getime(timer));

	usleep(10);

	gettimeofday(&_philo->_data->start_time, NULL);
	_philo->_data->start = 1;
	
}

void ft_print_action(t_philo *Philo, char *str, int dead)
{
	struct timeval	actual_time;
	
	pthread_mutex_lock(&Philo->_data->mutx_dead);
	if(Philo->_data->start)
	{
		gettimeofday(&actual_time, NULL);
		if(dead == 1)
		{
			Philo->_data->start = 0;
		}
		printf("%ld %d %s\n",  ft_time(actual_time, Philo), Philo->id, str);
	
		pthread_mutex_unlock(&Philo->_data->mutx_dead);
	}
	else
		exit(0);
}

void	ft_check_dead(t_philo *Philo)//////////////////////////
{	
	struct timeval	actual_time;
	gettimeofday(&actual_time, NULL);
	
	if (ft_time(actual_time, Philo) - Philo->last_eat > Philo->_data->time_die)
		ft_print_action(Philo, "is dead", 1);
}

