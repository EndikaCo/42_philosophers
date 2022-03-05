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

void	ft_save_general_data(char **argv, t_data *Data, t_philo *Philos)
{
	int	i;

	i = 0;
	Data->num_philos = ft_atoi(argv[1]);
	Data->time_die = ft_atoi(argv[2]);
	Data->time_eat = ft_atoi(argv[3]);
	Data->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		Data->min_meals_day = ft_atoi(argv[5]);
	Data->next_id = 0;
	Data->_philosophers = malloc(sizeof(pthread_t) * Data->num_philos);
	Data->_mutx_forks = malloc(sizeof(pthread_mutex_t) * Data->num_philos);
	Data->fork_in_use = malloc(sizeof(int) * Data->num_philos);
	Data->start = 0;
	while (i < Data->num_philos)
		Data->fork_in_use[i++] = -1;
	Philos->id = 0;
	Philos->_data = Data;
	Philos->n_meals = 0;
	Philos->group = -1;
	i = 0;
	while (i < Data->num_philos)
		pthread_mutex_init(&Philos->_data->_mutx_forks[i++], NULL);
	pthread_mutex_init(&Data->mutx_id, NULL);
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
	printf("%ld\n", (Data.start_time.tv_sec * 1000) + (Data.start_time.tv_usec / 1000));
	
	i = 0;
	while (i < Data.num_philos)
	{
		pthread_create(&Data._philosophers[i++], NULL, &routine, &Philo);//ret
	}
	i = 0;
	while (i < Data.num_philos)
		pthread_join(Data._philosophers[i++], NULL); //controlar return
	i = 0;
	while (i < Data.num_philos)
		pthread_mutex_destroy(&Data._mutx_forks[i++]);
}
