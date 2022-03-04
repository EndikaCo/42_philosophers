#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <sys/time.h>
#include <pthread.h>
#include <sys/time.h>
#include<stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_general
{
	int				num_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				min_meals_day;
	pthread_t		*_philosophers;
	pthread_mutex_t *_mutx_forks;
	pthread_mutex_t	mutx_id;
	int 			next_id;
	int				*fork_in_use;
	struct timeval	start_time;

}t_data;

typedef struct s_philos
{
	int 	id;
	struct	timeval time1;
	struct	timeval last_eat;
	int		n_meals;
	int		group;	
	t_data	*_data;
		

}t_philo;

//UTILS
int			isodd(int n);
long int	ft_millis(struct timeval time1);
int			ft_atoi(const char *nptr);
void*		routine(void *arg);
void		ft_check_dead(t_philo *Philo);
void		ft_take_fork(t_philo *Philo);
void		eat(t_philo *Philo);
#endif