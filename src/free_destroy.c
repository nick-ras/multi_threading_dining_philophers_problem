#include "../philo.h"

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