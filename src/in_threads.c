#include "../philo.h"

int	create_threads(t_data *data, t_philos *philo)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if(pthread_create(&philo[i].thread, NULL, &routine, &philo[i]))
			return (1);
		usleep(1000);
		i++;
	}
	return (0);
}

int eat_sleep_think(void *philo)
{
	unlock_philo(philo);
	print_message(philo, "stopped thinking");
	((t_philos *)philo)->is_eating = 1;
	print_message(philo, "eating");
	usleep(((t_philos *)philo)->data.time_to_eat);
	((t_philos *)philo)->eat_count--;
	((t_philos *)philo)->is_eating = 0;
	print_message(philo, "stopped eating");
	((t_philos *)philo)->death_clock = get_time() + ((t_philos *)philo)->data.time_to_die; // move down?? or what to do?
	lock_philo(philo);
	print_message(philo, "sleeping");
	usleep(((t_philos *)philo)->data.time_to_sleep);
	print_message(philo, "stopped sleeping");
	print_message(philo, "thinking");
	return (0);
}

void	*routine(void *philo)
{
	((t_philos	*)philo)->death_clock = get_time() + ((t_philos	*)philo)->data.time_to_die;
	if(pthread_create(&((t_philos	*)philo)->check_thread, NULL, &check_death, philo))
		return (NULL);
	while (1)
	{
		eat_sleep_think(philo);
		if (((t_philos	*)philo)->dead)
			return (NULL);
	}
	return (NULL);
}

void	*check_death(void *philo)
{
	while (1)
	{
		if (((t_philos	*)philo)->death_clock)
		{
			if (((t_philos	*)philo)->data.dead == 1)
				return (NULL);
			printf("philosopher %d time left in ms %ld \n", ((t_philos	*)philo)->id, ((t_philos	*)philo)->death_clock - get_time());
			if (!((t_philos	*)philo)->is_eating && ((t_philos	*)philo)->death_clock < get_time())
			{
				unlock_philo(philo);
				printf("the mighty philosopher %d has died\n", ((t_philos	*)philo)->id);
				((t_philos *)philo)->data.dead = 1;
				pthread_mutex_lock(((t_philos	*)philo)->lfork);
				pthread_mutex_lock(((t_philos	*)philo)->rfork);
				return (NULL);
			}
		}
		usleep(1000000);
	}
	return (NULL);
}
