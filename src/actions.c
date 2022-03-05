/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:57:18 by ecorreia          #+#    #+#             */
/*   Updated: 2022/03/03 19:59:44 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	think(t_philo *Philo)
{
	gettimeofday(&Philo->time1, NULL);
	printf("%ld %d is thinking\n", ft_millis(Philo), Philo->id);
}

void	f_sleep(t_philo *Philo)
{
	gettimeofday(&Philo->time1, NULL);
	printf("%ld %d is sleeping\n", ft_millis(Philo), Philo->id);
	usleep(Philo->_data->time_sleep * 1000);
	think(Philo);
}

void	eat(t_philo *Philo)
{
	int	right_fork;

	if (Philo->id == 0)
		right_fork = Philo->_data->num_philos -1;
	else
		right_fork = Philo->id - 1;
	if (Philo->_data->fork_in_use[Philo->id] == Philo->id
		&& Philo->_data->fork_in_use[right_fork] == Philo->id)
	{
		Philo->n_meals++;
		gettimeofday(&Philo->time1, NULL);
		//ft_check_dead(Philo);
		printf("%ld %d is eating\n",  ft_millis(Philo), Philo->id);
		gettimeofday(&Philo->last_eat, NULL);
		usleep(Philo->_data->time_eat * 1000);
		Philo->_data->fork_in_use[Philo->id] = -1;
		Philo->_data->fork_in_use[right_fork] = -1;
		f_sleep(Philo);
	}
}

void	ft_take_fork(t_philo *Philo)
{	
	int	right_fork;

	if (Philo->id == 0)
		right_fork = Philo->_data->num_philos -1;
	else
		right_fork = Philo->id - 1;
	pthread_mutex_lock(&Philo->_data->_mutx_forks[Philo->id]);//left
	pthread_mutex_lock(&Philo->_data->_mutx_forks[right_fork]);//right
	//ft_check_dead(Philo);
	if (Philo->_data->fork_in_use[Philo->id] == -1
		&& Philo->_data->fork_in_use[right_fork] == -1)
	{
		Philo->_data->fork_in_use[Philo->id] = Philo->id;
		gettimeofday(&Philo->time1, NULL);
		printf("%ld %d has taken a fork\n",  ft_millis(Philo), Philo->id);
		Philo->_data->fork_in_use[right_fork] = Philo->id;
		gettimeofday(&Philo->time1, NULL);
		printf("%ld %d has taken a fork\n",  ft_millis(Philo), Philo->id);
	}
	pthread_mutex_unlock(&Philo->_data->_mutx_forks[Philo->id]);//left
	pthread_mutex_unlock(&Philo->_data->_mutx_forks[right_fork]);//left
}
