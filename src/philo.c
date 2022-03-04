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

void	ft_check_dead(t_philo *Philo)
{
	if (ft_millis(Philo->time1) - ft_millis(Philo->last_eat)
		> Philo->_data->time_die)
	{
		printf("%ld %d is dead\n", ft_millis(Philo->time1), Philo->id);
		exit(0);
	}
}

void	ft_get_next_id(t_philo *Philo)
{
	pthread_mutex_lock(&Philo->_data->mutx_id);
	Philo->id = Philo->_data->next_id++;
	pthread_mutex_unlock(&Philo->_data->mutx_id);
}

void	*routine(void *arg)
{
	t_philo			_philo;
	struct timeval	timer;

	_philo = *(t_philo *)arg;
	ft_get_next_id(&_philo);
	//ft_join_group(&Philo);

	gettimeofday(&timer, NULL);
	
	while ()
	{	
		ft_take_fork(&_philo);
		eat(&_philo);
	}
	free(arg);
	return (NULL);
}
