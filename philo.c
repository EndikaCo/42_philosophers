
/*
./philo 6 200 200 200

arguments:
number_of_philosophers
time_to_die
time_to_eat
time_to_sleep
[number_of_times_each_philosopher_must_eat]
*/

#include <unistd.h>
#include <stdio.h>
#include "philo.h"
#include <pthread.h>
#include <sys/time.h>
#include<stdlib.h>

int	ft_atoi(const char *nptr)
{
	int	num;
	int	sign;
	int	i;

	num = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\r' || nptr[i] == '\v' || nptr[i] == '\f')
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] != '\0')
	{
		if (nptr[i] < '0' || nptr[i] > '9')
			return (sign * num);
		num = num * 10 + nptr[i++] - '0';
	}
	return (sign * num);
}

void ft_save_general_data(char **argv, t_data *Data, t_philo *Philos)
{
    int i = 0;

    Data->num_philos = ft_atoi(argv[1]);
    Data->time_die = ft_atoi(argv[2]);
    Data->time_eat = ft_atoi(argv[3]);
    Data->time_sleep = ft_atoi(argv[4]);

   	if (argv[5])
    	Data->min_meals_day = ft_atoi(argv[5]);
   
	Data->next_id = 0;

    Data->Philosophers = malloc(sizeof(pthread_t) * Data->num_philos);
    Data->mutx_forks = malloc(sizeof(pthread_mutex_t) * Data->num_philos);
	Data->fork_in_use = malloc(sizeof(int) * Data->num_philos);

	while(i < Data->num_philos)
		Data->fork_in_use[i++] = -1;

    Philos->id = 0;
    Philos->Data = Data;
	Philos->n_meals = 0;

	i = 0;
    while (i < Data->num_philos)
		pthread_mutex_init(&Philos->Data->mutx_forks[i++], NULL);

	pthread_mutex_init(&Data->mutx_id, NULL);
}

long int ft_millis(struct timeval time1)
{
	return (time1.tv_sec * 1000) + (time1.tv_usec / 1000);
}

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
	//printf("time1     = %ld\n", ft_millis(Philo->time1));
	//printf("last eat     = %ld\n", ft_millis(Philo->last_eat));

	//printf("%d %ld - lst %ld = %ld\n",Philo->id, ft_millis(Philo->time1), ft_millis(Philo->last_eat), ft_millis(Philo->time1) - ft_millis(Philo->last_eat));

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

/*
void take_fork(t_philo Philo)
{	
	if(Philo.id == 0)
		pthread_mutex_lock(&Philo.Data->mutx_forks[Philo.Data->num_philos]);//right
	else
		pthread_mutex_lock(&Philo.Data->mutx_forks[Philo.id - 1]);//right


	pthread_mutex_lock(&Philo.Data->mutx_forks[Philo.id]);//left
	gettimeofday(&Philo.time1, NULL);
    printf("%ld %d has taken a fork\n", ft_millis(Philo.time1), Philo.id);

	gettimeofday(&Philo.time1, NULL);
    printf("%ld %d has taken a fork\n", ft_millis(Philo.time1), Philo.id);
	eat(Philo);
	if(Philo.id == 0)
		pthread_mutex_unlock(&Philo.Data->mutx_forks[Philo.Data->num_philos]);//right
	else
		pthread_mutex_unlock(&Philo.Data->mutx_forks[Philo.id - 1]);//right

	pthread_mutex_unlock(&Philo.Data->mutx_forks[Philo.id]);//left
	printf("%ld %d has left a fork\n", ft_millis(Philo.time1), Philo.id);
}
*/

void ft_take_fork(t_philo *Philo)
{	
	int right_fork;  
	if(Philo->id == 0)
		right_fork = Philo->Data->num_philos -1;
	else 
		right_fork = Philo->id - 1;

	ft_check_dead(Philo);

	pthread_mutex_lock(&Philo->Data->mutx_forks[0]);
	if(Philo->Data->fork_in_use[Philo->id] == -1 && Philo->Data->fork_in_use[right_fork] == -1)
	{
		Philo->Data->fork_in_use[Philo->id] = Philo->id;
		gettimeofday(&Philo->time1, NULL);
		
    	printf("%ld %d has taken a fork\n", ft_millis(Philo->time1), Philo->id);

		Philo->Data->fork_in_use[right_fork] = Philo->id;
		gettimeofday(&Philo->time1, NULL);
    	printf("%ld %d has taken a fork\n", ft_millis(Philo->time1), Philo->id);
	}
	pthread_mutex_unlock(&Philo->Data->mutx_forks[0]);

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

int main(int argc, char *argv[])
{
	t_data		Data;
	t_philo	    Philo;

	if(argc != 5 && argc != 6)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	ft_save_general_data(argv, &Data, &Philo);


	int i = 0;
	while(i < Data.num_philos)
	{
		pthread_create(&Data.Philosophers[i++], NULL, &routine, &Philo);// falta controlar return
	}

	i = 0;
	while(i < Data.num_philos)
		pthread_join(Data.Philosophers[i++],NULL); //falta controlar return

    //destroy
   i = 0;
	while(i < Data.num_philos)
	    pthread_mutex_destroy(&Data.mutx_forks[i++]);

}