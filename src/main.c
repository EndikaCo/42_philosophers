/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:09:30 by ecorreia          #+#    #+#             */
/*   Updated: 2022/03/03 20:00:53 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_save_general_data(char **argv, t_data *_data, t_philo *_philo)
{
	int	i;

	i = 0;
	_data->num_philos = ft_atoi(argv[1]);
	_data->time_die = ft_atoi(argv[2]);
	_data->time_eat = ft_atoi(argv[3]);
	_data->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		_data->min_meals_day = ft_atoi(argv[5]);
	else
		_data->min_meals_day = -1;
	_data->next_id = 0;
	_data->_philosophers = malloc(sizeof(pthread_t) * _data->num_philos);
	_data->mutx_forks = malloc(sizeof(pthread_mutex_t) * _data->num_philos);
	_data->fork_in_use = malloc(sizeof(int) * _data->num_philos);
	_data->start = 0;

	while (i < _data->num_philos)
		_data->fork_in_use[i++] = -1;
	_philo->id = 0;
	_philo->_data = _data;
	_philo->n_meals = 0;
	_philo->group = -1;
	_philo->last_eat = 0;
	
	i = 0;
	while (i < _data->num_philos)
		pthread_mutex_init(&_philo->_data->mutx_forks[i++], NULL);
	pthread_mutex_init(&_data->mutx_id, NULL);
	pthread_mutex_init(&_data->mutx_dead, NULL);

}

void ft_one(t_philo *_philo)
{
	usleep(_philo->_data->time_die);
	printf("1 %d has taken a fork\n", _philo->id);
	printf("%d %d is dead\n", _philo->_data->time_die, _philo->id);
	exit(0);
}

int ft_loop(t_philo *_philo)
{
	int i;
	
	i = 0;
	while (1)
	{	
		if (_philo->_data->num_philos == 1 && _philo->_data->start == 1)
		{
			ft_one(_philo);
			return 0;
		}
		while (_philo->_data->start == 1)
		{	
			if((_philo->group == 1 || _philo->group == 3) && i == 0)
			{
				i = 1;
				usleep(5);
			}
			if( _philo->_data->min_meals_day == _philo->n_meals)//
				exit(0);

			ft_take_fork(_philo);
			eat(_philo);
		}
	}
	return 0;
}

void	*routine(void *arg)
{
	t_philo			_philo;
	
	_philo = *(t_philo *)arg;
	ft_get_next_id(&_philo);
	ft_join_group(&_philo);
	if(_philo.id == _philo._data->num_philos - 1)
		ft_wait_start(&_philo);
	ft_loop(&_philo);
	free(arg);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_data		Data;
	t_philo		Philo;
	int			i;

	if (argc != 5 && argc != 6)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	ft_save_general_data(argv, &Data, &Philo);
	gettimeofday(&Data.start_time, NULL);
	i = 0;
	while (i < Data.num_philos)
		pthread_create(&Data._philosophers[i++], NULL, &routine, &Philo);//ret
	i = 0;
	while (i < Data.num_philos)
		pthread_join(Data._philosophers[i++], NULL); //controlar return
	i = 0;
	while (i < Data.num_philos)
		pthread_mutex_destroy(&Data.mutx_forks[i++]);
}
