#include "../philo.h"

int	join_threads(t_data *data, t_philos *philo)
{
	int		i;
	void	*ret;
	void	*ret1;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_join(philo[i].thread, &ret))
			return (1);
		i++;
	}
	if (pthread_join(data->thread_check, &ret1))
		return (1);
	return (0);
}

int	free_destroy(t_data *data, t_philos *philo)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->m_forks[i++]);
	}
	free(data->m_forks);
	free(philo);
	free(data);
	return (0);
}
