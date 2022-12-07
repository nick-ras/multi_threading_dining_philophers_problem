#include "../philo.h"

int	free_destroy(t_data *data, t_philos *philo)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		printf("destroying  %d\n", i);
		pthread_mutex_destroy(&data->mutex[i++]);
	}
	free(data->mutex);
	free(philo);
	free(data);
	return (0);
}