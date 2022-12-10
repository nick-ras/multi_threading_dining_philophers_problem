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

void	*routine(void *philo)
{
	t_philos *ph;
	int nb;

	ph = (t_philos *)philo;
	update_clock(ph);
	while (1)
	{
		lock_philo(philo);
		print_message(philo, "stopped thinking");
		ph->id = 1;
		print_message(philo, "eating");
		usleep(ph->data.time_to_eat);
		if (check_dead_var(philo))
			return (NULL);
		ph->eat_count--;
		ph->is_eating = 0;
		print_message(philo, "stopped eating");
		update_clock(ph);
		print_message(philo, "sleeping");
		nb = ph->data.time_to_sleep;
		unlock_philo(philo);
		usleep(nb);
		lock_philo(philo);
		print_message(philo, "stopped sleeping");
		print_message(philo, "thinking");
		if (check_dead_var(philo))
			return (NULL);
		unlock_philo(philo);
	}
	return (NULL);
}

void	*check_death(void	*philo)
{
	int i;
	t_philos *ph;

	ph = *(t_philos **)philo;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&ph[0].data.m_philo[i]);
		if (clock_started(ph))
		{
			//printf("ph %d count down %ld \n", ph[i].id, (ph[i].death_clock - get_time()));
			if (check_dead_var(ph));
				return (NULL);
			if (time_ran_out(ph))
			{
				printf("the mighty philosopher %d has died\n", ph[i].id);
				ph[0].data.dead = 1;
				return (0);
			}
		}
		if (i >= ph[0].data.philo_count - 1)
			i = 0;
		else
			i++;
		//pthread_mutex_lock(&ph[0].data.m_data);
		pthread_mutex_unlock(&ph[0].data.m_philo[i]);
		usleep(1000);
	}
	return (0);
}
