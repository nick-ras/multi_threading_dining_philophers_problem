#include "../philo.h"

int	join_threads(t_data *data, t_philos *philo)
{
	int i;

	i = 0;
	void *ret;
	// void *ret1;

	// if (pthread_join(thread_check, &ret1) != 0)
	// 		return (1);
	while (i < data->philo_count)
	{
		if (!pthread_join(philo[i].thread, &ret) != 0)
			return (1);
		i++;
	}
	return (0);
}
int	free_destroy(t_data *data, t_philos *philo)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		printf("destroying  %d\n", i);
		pthread_mutex_destroy(&data->m_forks[i++]);
		pthread_mutex_destroy(&data->m_philo[i++]);
	}
	free(data->m_forks);
		free(data->m_philo);
	free(philo);
	free(data);
	return (0);
}