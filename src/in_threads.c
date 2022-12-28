#include "../philo.h"

int	create_threads(t_data *data, t_philos *philo)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]))
			return (1);
		usleep(100);
		i++;
	}
	return (0);
}

void	*routine(void *philo)
{
	t_philos	*ph;

	ph = (t_philos *)philo;
	update_clock(ph);
	while (1)
	{
		if (check_dead_var(philo))
			return (NULL);
		if (lock_philo(philo))
		{
			update_eating(ph, 1);
			print_message(philo, "is eating");
			usleep(ph->data->time_to_eat * 1000);
			update_clock(ph);
			unlock_philo(philo);
			if (update_eating(ph, 0))
				return (NULL);
			print_message(philo, "is sleeping");
			usleep(ph->data->time_to_sleep * 1000);
			print_message(philo, "is thinking");
		}
	}
	return (NULL);
}

int	check_done_eating(t_philos *ph)
{
	if (all_done_eating(ph))
		return (1);
	return (0);
}

void	*check_death(void	*philo)
{
	int				i;
	t_philos		*ph;

	ph = (t_philos *)philo;
	i = 0;
	while (1)
	{
		if (clock_started(&ph[i]))
		{
			if (ph->data->eat_total > 0)
			{
				if (check_done_eating(&ph[i]))
					return (NULL);
			}
			if (time_ran_out(ph[i]))
			{
				pthread_mutex_lock(&ph[0].data->m_dead);
				ph[i].data->dead = 1;
				pthread_mutex_unlock(&ph[0].data->m_dead);
				printf("%ld %d died\n", get_time(), ph[i].id);
				return (NULL);
			}
			if (i >= (ph[0].data->philo_count - 1))
				i = 0;
			else
				i++;
		}
		usleep(1000);
	}
	return (NULL);
}
