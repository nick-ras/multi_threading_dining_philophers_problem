#include "../philo.h"

int	all_done_eating(t_philos *ph)
{
	pthread_mutex_lock(&ph->data->m_living);
	if (ph->data->philo_living <= 0)
	{
		printf("IN ALL DONE EATING\n");
		pthread_mutex_unlock(&ph->data->m_living);
		return (1);
	}
	pthread_mutex_unlock(&ph->data->m_living);
	return (0);
}