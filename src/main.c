//1. number_of_philosophers 
// 2. time_to_die 
// 3. time_to_eat
// 4. time_to_sleep 
// 5. [number_of_times_each_philosopher_must_eat]
// External functs. memset, printf, malloc, free, write,
// usleep, gettimeofday, pthread_create,
// pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, p
//gcc -pthread main.c
// int	main(int argc, char **argv);
#include "../philo.h"

int	init_mutex_and_philos(t_data *data, t_philos *philo, char **argv)
{
	int	i;

	//make philos structs
	i = 0;
	while (i < data->philo_count)
	{
		philo[i].id = i;
		philo[i].data = data;
		philo[i].is_eating = 0;
		if (argv[5])
			philo[i].eat_count = *argv[5];
		//SET ALL PHILO VARS FROM EX ARGV Here
		i++;
	}
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	if ((data->mutex = ft_calloc((size_t)(data->philo_count + 1), sizeof(pthread_mutex_t))) == NULL)
		return (1);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->mutex[i], NULL);
		pthread_mutex_lock(&data->mutex[i]);
		i++;
	}
	return (0);
}

int	init_data(t_data *data, char **argv)
{

	//check is nb == 0
	if (ft_strncmp(argv[1], "0", 1) == 0 && ft_strlen(argv[1]) == 1)
		data->philo_count = 0;
	else
	{
		if (ft_atoi(argv[1]) == 0)
			return (1);
		else
			data->philo_count = ft_atoi(argv[1]);
	}
	data->time_to_die = 200000; //set * 1000
	//check if numbers are under requirement
	if (data->philo_count > 100 || data->nb_times_eat > 100 || data->time_to_die > 20000000 \
	|| data->time_to_eat > 100 || data->time_to_sleep > 100)
	{
		printf("do not meet argv requirements i set up to avoid infinity\n");
		return (1);
	}
	return (init_mutex(data));
}

__uint64_t	get_time_death( t_philos *philo)
{
	struct timeval after;

	gettimeofday(&after, NULL);
	printf("start %ld now %ld\n", philo->time_since_eat.tv_sec, after.tv_sec);

  return(after.tv_sec - philo->time_since_eat.tv_sec);
}


void	*routine(void *philo)
{
	t_philos *n_philo;
	n_philo = (t_philos *)philo;
	
	//pthread_create(&thr, NULL, &check_death, n_philo); //IF == NULL
	gettimeofday(&n_philo->time_since_eat, NULL);
	printf("routine: philo id  %d time %ld \n", n_philo->id, n_philo->time_since_eat.tv_sec); //THIS DOESNT WORK

	while (1)
	{
		//eat, sleep, think
	}
	//TAKE FORKS and display message before taking other fork, remember equal is right first
	//HOW TO CHECK WHICH THREAD YOU ARE IN??
	//if equal number check right 
	// while (1)
	// {
	// 	if (data->curr_nb % 2 == 0)
	//			
	// }
	return (philo); //RETURN WHAT????
}

int destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		printf("destroying  %d\n", i);
		pthread_mutex_destroy(&data->mutex[i++]);
		free(data->mutex);
	}
	return (0);
}

int	free_stuff(t_data *data, t_philos *philo)
{
	free(philo);
	free(data);
	return (0);
}

void	*check_death(void *philo)
{
	t_philos	*n_philo;
	struct timeval	curr;
	int i;

	n_philo = (t_philos*) philo;

	i = 0;
	while (1)
	{
		//CHECK IF THREAD IS INITIATED
		
		printf("philo id %d i %d phill count %d\n", n_philo[i].id, i, n_philo[i].data->philo_count);
		gettimeofday(&curr, NULL);
		if (!n_philo->is_eating && (curr.tv_sec - n_philo->time_since_eat.tv_sec) > n_philo->data->time_to_die)
		{
			printf("the mighty philosopher %d has died \n", n_philo->id);
			printf("joining %d\n", n_philo->id);
			pthread_join(n_philo->thread, NULL);
		}
		if (i >= (n_philo[i].data->philo_count - 1))
			i = 0;
		else
			i++;
	}
	return (philo);
}

int	main(int argc, char **argv)
{
	t_data *data;
	t_philos *philo;

	//check args
	if (argc < 5 || 6 < argc)
	{
		printf("argc not correct");
		return (1);
	}
	if ((data = ft_calloc((size_t)1, sizeof(t_data))) == NULL)
		return (1);
	if ((philo = ft_calloc((size_t)data->philo_count + 1, sizeof(t_philos))) == NULL)
		return (1);
	if (init_data(data, argv))
		return (1);
	if (init_mutex_and_philos(data, philo, argv))
		return (1);
	

	//make check of death
	pthread_t check_thread;
	pthread_create(&check_thread, NULL, &check_death, &(philo));
	//create thread array
	int	i = 0;
	while (i < data->philo_count)
	{
		pthread_create(&(philo[i].thread), NULL, &routine, &(philo[i]));
		//SEES OUTCOME
		printf("thread %ld\n", philo[i].thread);
		i++;
	}
	//ENDING THREADS
	i = 0;
	while (i < data->philo_count)
	{
		printf("joining %d\n", i);
		pthread_join(philo[i++].thread, NULL);
	}
	sleep(4);
	if (destroy_mutexes(data))
		return (1);
	free_stuff(data, philo);
 //how should i manage 
	return (0);
}
