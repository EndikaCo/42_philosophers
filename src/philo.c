
#include "../inc/philo.h"


void think(t_philo *Philo)
{
    gettimeofday(&Philo->time1, NULL);
	printf("%ld %d is thinking\n", ft_millis(Philo->time1), Philo->id);
	//printf("-----------------------\n");
}

void f_sleep(t_philo *Philo)
{
    gettimeofday(&Philo->time1, NULL);
    printf("%ld %d is sleeping\n",  ft_millis(Philo->time1), Philo->id);
    usleep(Philo->Data->time_sleep * 1000);
	think(Philo);
}

void ft_check_dead(t_philo *Philo)
{
	if(ft_millis(Philo->time1) - ft_millis(Philo->last_eat) > Philo->Data->time_die)
	{
			printf("%ld %d is dead\n", ft_millis(Philo->time1), Philo->id);
			exit(0);
	} 
}

void eat(t_philo *Philo)
{
	
	int right_fork;
	if(Philo->id == 0)
		right_fork = Philo->Data->num_philos -1;
	else 
		right_fork = Philo->id - 1;

	if(Philo->Data->fork_in_use[Philo->id] == Philo->id && Philo->Data->fork_in_use[right_fork] == Philo->id)
	{
		
		Philo->n_meals++;
		gettimeofday(&Philo->time1, NULL);
		ft_check_dead(Philo);
		printf("%ld %d is eating\n", ft_millis(Philo->time1), Philo->id);

		gettimeofday(&Philo->last_eat, NULL);

		usleep(Philo->Data->time_eat * 1000); // convertir a milisegundos
		Philo->Data->fork_in_use[Philo->id] = -1;
		Philo->Data->fork_in_use[right_fork] = -1;

		f_sleep(Philo);
	}

}

void ft_take_fork(t_philo *Philo)
{	
	int right_fork;  
	if(Philo->id == 0)
		right_fork = Philo->Data->num_philos -1;
	else 
		right_fork = Philo->id - 1;

	pthread_mutex_lock(&Philo->Data->mutx_forks[Philo->id]);//left
	pthread_mutex_lock(&Philo->Data->mutx_forks[right_fork]);//right
	ft_check_dead(Philo);

	if(Philo->Data->fork_in_use[Philo->id] == -1 
	&& Philo->Data->fork_in_use[right_fork] == -1)
	{
		Philo->Data->fork_in_use[Philo->id] = Philo->id;
		gettimeofday(&Philo->time1, NULL);
		
    	printf("%ld %d has taken a fork\n", ft_millis(Philo->time1), Philo->id);

		Philo->Data->fork_in_use[right_fork] = Philo->id;
		gettimeofday(&Philo->time1, NULL);
    	printf("%ld %d has taken a fork\n", ft_millis(Philo->time1), Philo->id);
	}

	pthread_mutex_unlock(&Philo->Data->mutx_forks[Philo->id]);//left
	pthread_mutex_unlock(&Philo->Data->mutx_forks[right_fork]);//left
}

void ft_join_group(t_philo *Philo)
{
	if(!isOdd(Philo->Data->num_philos))
	{
		if(isOdd(Philo->id))
			Philo->group = 1;
		else
			Philo->group = 2;	
	}
	if(isOdd(Philo->Data->num_philos))
	{
		if(!isOdd(Philo->id) && Philo->id != Philo->Data->num_philos - 1)
			Philo->group = 1;
		else if(isOdd(Philo->id))
			Philo->group = 2;	
		if(!isOdd(Philo->id) && Philo->id != 0)	
			Philo->group = 3;	
	}
	printf("%d is group %d\n", Philo->id, Philo->group);
}

void ft_get_next_id(t_philo *Philo)
{
	pthread_mutex_lock(&Philo->Data->mutx_id);
	Philo->id = Philo->Data->next_id++;
	pthread_mutex_unlock(&Philo->Data->mutx_id);
}

void* routine(void *arg)
{
	t_philo Philo;
	Philo = *(t_philo*)arg;

	struct	timeval timer;

	ft_get_next_id(&Philo);
	ft_join_group(&Philo);
	//gettimeofday(&Philo.last_eat, NULL);///////////////////////////////////////////start eat time
	//gettimeofday(&Philo.time1, NULL);
	//printf("current thread id:%u\n", (unsigned int)pthread_self());
	//printf("%ld Philo id:%d created\n", ft_millis(Philo.time1),  Philo.id);///////////////////////////////////
	
	while(1)
	{
		if(Philo.Data->next_id == Philo.Data->num_philos)
		{
			gettimeofday(&timer, NULL);
			usleep(50);
			break;
		}
	}

	while(1)
	{	
			ft_take_fork(&Philo);
			eat(&Philo);
	}

	free(arg);
	return (NULL);
}
