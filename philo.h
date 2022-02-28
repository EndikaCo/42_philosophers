#ifndef PHILO_H
#define PHILO_H
//
#include <pthread.h>
#include <sys/time.h>

typedef struct s_general
{
	int				num_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				min_meals_day;

	pthread_t		*Philosophers;
	pthread_mutex_t *mutx_forks;
	pthread_mutex_t	mutx_id;
	int 			next_id;

	int				*fork_in_use;

}t_data;

typedef struct s_philos
{
	int 	id;
	struct	timeval time1;
	struct	timeval last_eat;

	int		n_meals;

	t_data	*Data;

}t_philo;

#endif