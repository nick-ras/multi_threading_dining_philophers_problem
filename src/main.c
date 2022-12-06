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

__uint64_t	get_time_death( t_philos *philo)
{
	struct timeval after;

	gettimeofday(&after, NULL);
	printf("start %ld now %ld\n", philo->time_since_eat.tv_sec, after.tv_sec);

  return(after.tv_sec - philo->time_since_eat.tv_sec);
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
	if ((philo = ft_calloc(data->philo_count + 1, sizeof(t_philos))) == NULL)
		return (1);
	if (init_data(data, argv))
		return (1);
	if (init_mutex_and_philos(data, philo, argv))
		return (1);
	sleep(1);
	if (create_threads(data, philo))
		return(1);
	//ENDING THREADS
	// i = 0;
	// while (i < data->philo_count)
	// {
	// 	printf("joining %d\n", i);
	// 	if (pthread_join(philo[i++].thread, NULL) != NULL)
	// 		retutn (1);
	// }
	sleep(4);
	// if (destroy_mutexes(data))
	// 	return (1);
	free_stuff(data, philo);
 //how should i manage 
	return (0);
}
