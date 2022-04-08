/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:30:10 by ecorreia          #+#    #+#             */
/*   Updated: 2022/04/08 19:42:14 by ecorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>

typedef struct s_general
{
	int				num_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				min_meals_day;
	int				next_id;
	int				*fork_in_use;
	int				start;
	struct timeval	start_time;
	pthread_t		*_philosophers;
	pthread_mutex_t	*mutx_forks;
	pthread_mutex_t	mutx_id;
	pthread_mutex_t	mutx_dead;

}t_data;

typedef struct s_philos
{
	int				id;
	long int		last_eat;
	int				n_meals;
	int				group;
	struct timeval	time1;
	t_data			*_data;

}t_philo;

//PHILO
void		ft_join_group(t_philo *Philo);
void		ft_get_next_id(t_philo *Philo);
void		ft_one(t_philo *_philo);
void		ft_print(t_philo *Philo, char *str, int dead);
void		ft_check_dead(t_philo *Philo);

//UTILS
int			ft_atoi(const char *nptr);
long int	ft_getime(struct timeval time1);
long int	ft_time(struct timeval time, t_philo *_philo);
int			ft_isodd(int n);

//ACTIONS
void		ft_udelay(t_philo *_philo, int delay);
void		ft_think(t_philo *Philo);
void		ft_sleep(t_philo *Philo);
void		ft_eat(t_philo *Philo);
void		ft_take_fork(t_philo *Philo);

//MAIN
void		ft_init_data(char **argv, t_data *_data);
void		ft_init_philo(t_data *_data, t_philo *_philo);
int			ft_loop(t_philo *_philo);
void		*routine(void *arg);

#endif