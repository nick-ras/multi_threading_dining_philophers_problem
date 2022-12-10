// 1. number_of_philosophers 
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

int	main(int argc, char **argv)
{
	t_data *data;
	t_philos *philo;
	pthread_t	thread_check;

	//check args
	if (argc < 5 || 6 < argc)
	{
		printf("argc not correct\n");
		return (1);
	}
	if ((data = ft_calloc(1, sizeof(t_data))) == NULL)
		return (1);
	if ((philo = ft_calloc(data->philo_count + 1, sizeof(t_philos))) == NULL)
		return (1);
	if (init_data(data, argv))
		return (1);
	if (init_mutex_and_philos(data, philo))
		return (1);
	if(pthread_create(&thread_check, NULL, &check_death, &philo))
			return (1);
	if (create_threads(data, philo))
		return(1);
	if (join_threads(data, philo))
		return(1);
	if (free_destroy(data, philo))
		return(1);
	return (0);
}
