#include "../philo.h"

int	init_mutex_and_philos(t_data *data, t_philos *philo, char **argv)
{
	int	i;

	//make philos structs
	i = 0;
	while (i < data->philo_count)
	{
		philo[i].id = i;
		printf("id %d\n", philo[i].id);
		philo[i].data = *data;
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

int	create_threads(t_data *data, t_philos *philo)
{
	int	i;
	pthread_t check_thread;

	if(pthread_create(&check_thread, NULL, &check_death, philo))
		return (1);
	i = 0;
	while (i < data->philo_count)
	{
		if(pthread_create(&(philo[i].thread), NULL, &routine, &philo[i]))
			return (1);
		//SEES OUTCOME
		//printf("create threads: id %d thread %ld\n", philo[i].id, philo[i].thread);
		i++;
	}
	return (0);
}
