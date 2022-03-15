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

void ft_sleep(t_philo *_philo, int delay)
{
    struct timeval start;
    struct timeval end;
    int time;

    time = 0;
    gettimeofday(&start, NULL);
    gettimeofday(&end, NULL);
    while (ft_getime(end) - ft_getime(start) < delay)
    {
        usleep(100);
        gettimeofday(&end, NULL);
        if (ft_getime(end) - ft_getime(start) - time > 10)
            time += 10;	
		ft_check_dead(_philo);
    }
}

void	think(t_philo *Philo)
{
	ft_check_dead(Philo);
	ft_print_action(Philo, "is thinking", 0);
	if (isodd(Philo->_data->num_philos))
		ft_sleep(Philo, Philo->_data->time_eat);
	usleep(1);
}

void	f_sleep(t_philo *Philo)
{
	ft_check_dead(Philo);
	ft_print_action(Philo, "is sleeping", 0);
	ft_sleep(Philo, Philo->_data->time_sleep);
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
		ft_check_dead(Philo);
		Philo->n_meals++;
		ft_print_action(Philo, "is eating", 0);
		gettimeofday(&Philo->time1, NULL);
		Philo->last_eat = ft_time(Philo->time1, Philo);
		ft_sleep(Philo, Philo->_data->time_eat);

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
	pthread_mutex_lock(&Philo->_data->mutx_forks[Philo->id]);//left
	pthread_mutex_lock(&Philo->_data->mutx_forks[right_fork]);//right

	ft_check_dead(Philo);
	if (Philo->_data->fork_in_use[Philo->id] == -1
		&& Philo->_data->fork_in_use[right_fork] == -1)
	{
		Philo->_data->fork_in_use[Philo->id] = Philo->id;
		ft_print_action(Philo, "has taken a fork", 0);
		Philo->_data->fork_in_use[right_fork] = Philo->id;
		ft_print_action(Philo, "has taken a fork", 0);
	}
	pthread_mutex_unlock(&Philo->_data->mutx_forks[Philo->id]);//left
	pthread_mutex_unlock(&Philo->_data->mutx_forks[right_fork]);//left
}
