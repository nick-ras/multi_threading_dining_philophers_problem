#include "../philo.h"

int	create_threads(t_data *data, t_philos *philo)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if(pthread_create(&philo[i].thread, NULL, &routine, &philo[i]))
			return (1);
		usleep(10000);
		i++;
	}
	return (0);
}

void	*routine(void *philo)
{
	t_philos *ph;

	ph = (t_philos *)philo;
	update_clock(ph);
	while (1)
	{
		lock_philo(philo);
		print_message(philo, "stopped thinking");
		print_message(philo, "eating");
		update_eating(ph, 1);
		usleep(ph->data->time_to_eat * 1000);
		unlock_philo(philo);
		print_message(philo, "stopped eating");
		if (update_eating(ph, 0))
			return (NULL);
		update_clock(ph);
		print_message(philo, "sleeping");
		usleep(ph->data->time_to_sleep * 1000);
		print_message(philo, "stopped sleeping");
		print_message(philo, "thinking");
		if (check_dead_var(philo))
			return (NULL);
	}
	return (NULL);
}

void	*check_death(void	*philo)
{
	int i;
	t_philos *ph;

	ph = (t_philos *)philo;
	i = 0;
	while (1)
	{
		if (clock_started(&ph[i]))
		{
			if (time_ran_out(ph[i]) || check_dead_var(&ph[i]))
			{
				printf("PHILOSOPHER %d DIED\n", ph[i].id);
				pthread_mutex_lock(&ph[0].data->m_dead);
				ph[i].data->dead = 1;
				pthread_mutex_unlock(&ph[0].data->m_dead);
				return (0);
			}
			if (i >= ph[0].data->philo_count - 1)
				i = 0;
			else
				i++;
		}
		usleep(1000);
	}
	return (NULL);
}
