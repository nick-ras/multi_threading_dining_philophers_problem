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
int	initialize_data(t_data *data, char **argv)
{
	//check is nb == 0
	if (ft_strncmp(argv[1], "0", 1) == 0 && ft_strlen(argv[1]) == 1)
		data->philo_count = 0;
	else
	{
		if (ft_atoi(argv[1]) == 0)
			return (0);
		else
			data->philo_count = ft_atoi(argv[1]);
	}
	//check if numbers are under requirement
	if (data->philo_count > 100 || data->nb_times_eat > 100 || data->time_to_die > 200 \
	|| data->time_to_eat > 100 || data->time_to_sleep > 100)
	{
		printf("do not meet argv requirements i set up to avoid infinity\n");
		return (0);
	}
	return 1;
}

void	*routine(void *data)
{
	t_data *new_data;
	new_data = (t_data *)data;
	pthread_mutex_lock(&new_data->mutex_var);
	printf("in routine\n");
	sleep(1);
	pthread_mutex_unlock(&new_data->mutex_var);
	return (data);
}

int	main(int argc, char **argv)
{
	pthread_t	thread1;
	pthread_t	thread2;
	t_data *data;

	//check args
	if (argc < 5 || 6 < argc)
	{
		printf("argc not correct");
		return (1);
	}
	if ((data = calloc(1, sizeof(t_data))) == NULL)
		return (1);
	if (initialize_data(data, argv) == 0)
		return (1);
	pthread_mutex_init(&data->mutex_var, NULL);
	pthread_create(&thread1, NULL, &routine, data);
	pthread_create(&thread2, NULL, &routine, data);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	pthread_mutex_destroy(&data->mutex_var);
	return (0);
}
