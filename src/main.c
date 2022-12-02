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
#include "../philo.h"

// int	main(int argc, char **argv);

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	if (!(data->mutex_var = calloc(data->philo_count, sizeof(pthread_mutex_t))))
		return (1);
	while (i < data->philo_count)
		pthread_mutex_init(&data->mutex_var[i++], NULL);
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

	return (init_mutex(data));
}

void	*routine(void *data)
{
	t_data *new_data;
	new_data = (t_data *)data;
	pthread_mutex_lock(&new_data->mutex_var[0]);
	printf("in routine\n");
	sleep(1);
	pthread_mutex_unlock(&new_data->mutex_var[0]);
	return (data);
}

int destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
		pthread_mutex_destroy(&data->mutex_var[i++]);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data *data;

	//check args
	if (argc < 5 || 6 < argc)
	{
		printf("argc not correct");
		return (1);
	}
	if ((data = ft_calloc(1, sizeof(t_data))) == NULL)
		return (1);
	if (init_data(data, argv))
		return (1);
	//creating threads;
	if ((data->threads = ft_calloc(data->philo_count, sizeof(pthread_t))) == NULL)
		return (1);
	int i = 0;
	while (i < data->philo_count)
		pthread_create(&(data->threads[i++]), NULL, &routine, data);
	i = 0;
	//ENDING THREADS
	while (i < data->philo_count)
		pthread_join(data->threads[i++], NULL);
	if (destroy_mutexes(data))
		return (1);

 //how should i manage 
	return (0);
}
