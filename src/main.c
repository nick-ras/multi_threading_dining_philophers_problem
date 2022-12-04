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

	if (!(data->mutex = ft_calloc(data->philo_count + 1, sizeof(pthread_mutex_t))))
		return (1);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->mutex[i], NULL);
		pthread_mutex_lock(&data->mutex[i++]);
	}
	//make philos structs
	i = 0;
	while (i < data->philo_count)
	{
		if (argv[5])
			philo[i].eat_count = *argv[5];
		philo[i].data = data;
		philo[i].id = i;
		//SET ALL PHILO VARS FROM EX ARGV Here
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
	//check if numbers are under requirement
	if (data->philo_count > 100 || data->nb_times_eat > 100 || data->time_to_die > 200 \
	|| data->time_to_eat > 100 || data->time_to_sleep > 100)
	{
		printf("do not meet argv requirements i set up to avoid infinity\n");
		return (1);
	}

	return (0);
}

void	*routine(void *philo)
{
	t_philos *n_philo;
	n_philo = (t_philos *)philo;
	gettimeofday(&n_philo->time_since_eat, NULL);
	printf("in routine. philo id is %d\n", n_philo->id);
	//TAKE FORKS and display message before taking other fork, remember equal is right first
	//HOW TO CHECK WHICH THREAD YOU ARE IN??
	//if equal number check right 
	// while (1)
	// {
	// 	if (data->curr_nb % 2 == 0)
	//			
	// }
	
	sleep(2);
	return (n_philo); //RETURN LOOP
}

int destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
		pthread_mutex_destroy(&data->mutex[i++]);
	return (0);
}

int	free_stuff(t_data *data)
{
	free(data->mutex);
	free(data);
	return (0);
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
	if ((data = ft_calloc(1, sizeof(t_data))) == NULL)
		return (1);
	if (!(philo = ft_calloc(data->philo_count, sizeof(t_philos))))
		return (1);
	if (!init_data(data, argv))
		return (1);
	if (!init_mutex_and_philos(data, philo, argv))
	return (1);
	//RETURN THREAD OR SMTH

	//create thread array
	int	i = 0;

	while (i < data->philo_count)
	{
		pthread_create(&(philo[i].thread), NULL, &routine, &(philo[i]));
		i++;
	}

	//ENDING THREADS
	i = 0;
	while (i < data->philo_count)
		pthread_join(philo[i++].thread, NULL);
	if (destroy_mutexes(data))
		return (1);
	free_stuff(data);
 //how should i manage 
	return (0);
}
