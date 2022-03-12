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

int my_usleep(__attribute__((unused)) t_philo *philo, int time)
{
    struct timeval now;
    struct timeval end;
    int i;

    gettimeofday(&now, NULL);
    gettimeofday(&end, NULL);
    i = 0;
    while ((end.tv_sec * 1000 + end.tv_usec / 1000) - (now.tv_sec * 1000 + now.tv_usec / 1000)  < time)
    {
        usleep(100);
        gettimeofday(&end, NULL);
        if ((end.tv_sec * 1000 + end.tv_usec / 1000) - (now.tv_sec * 1000 + now.tv_usec / 1000) - i > 10)
        {
            i += 10;
            //if (any_dead(philo))
            //    return (1);
        }
    }
    //if (any_dead(philo))
    //            return (1);
    return (0);

}

void	think(t_philo *Philo)
{
	gettimeofday(&Philo->time1, NULL);
	printf("%ld %d is thinking\n", ft_millis(Philo), Philo->id);
	if (isodd(Philo->_data->num_philos))
		my_usleep(Philo, Philo->_data->time_eat);
	usleep(1);
}

void	f_sleep(t_philo *Philo)
{
	gettimeofday(&Philo->time1, NULL);
	printf("%ld %d is sleeping\n", ft_millis(Philo), Philo->id);
	my_usleep(Philo, Philo->_data->time_sleep);
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
		ft_check_dead(Philo);/////////////////////////
		printf("%ld %d is eating\n",  ft_millis(Philo), Philo->id);
		Philo->last_eat = ft_time(Philo->time1, Philo);
		my_usleep(Philo, Philo->_data->time_eat);

		
		Philo->_data->fork_in_use[Philo->id] = -1;
		Philo->_data->fork_in_use[right_fork] = -1;
		//ft_etapa(Philo);
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
