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

int check_dead_var(t_philos *philo)
{
	pthread_mutex_lock(&philo->data.m_check);
	if (((t_philos *)philo)->data.dead)
		return (1);
	pthread_mutex_unlock(&philo->data.m_check);
	return (0);
}

int	check_clock(t_philos *philo)
{
	pthread_mutex_lock(&philo->data.m_check);
	if (((t_philos *)philo)->data.dead)
	{
		pthread_mutex_unlock(&philo->data.m_check);
		return (1);
	}
	pthread_mutex_unlock(&philo->data.m_check);
	return (0);
}

int	update_clock(t_philos *philo)
{
	pthread_mutex_lock(&philo->data.m_check);
	((t_philos	*)philo)->death_clock = get_time() + ((t_philos	*)philo)->data.time_to_die;
	pthread_mutex_unlock(&philo->data.m_check);
	return (0);
}

void	*routine(void *philo)
{
	t_philos *ph;
	int nb;

	ph = (t_philos *)philo;
	update_clock(philo);
	while (1)
	{
		lock_philo(philo);
		if (check_dead_var(philo))
			return (NULL);
		print_message(philo, "stopped thinking");
		ph->id = 1;
		print_message(philo, "eating");
		usleep(ph->data.time_to_eat);
		if (check_dead_var(philo))
			return (NULL);
		ph->eat_count--;
		ph->is_eating = 0;
		print_message(philo, "stopped eating");
		ph->death_clock = get_time() + ph->data.time_to_die; // move down?? or what to do?
		print_message(philo, "sleeping");
		nb = ph->data.time_to_sleep;
		unlock_philo(philo);
		usleep(nb);
		lock_philo(philo);
		if (check_dead_var(philo))
			return (NULL);
		print_message(philo, "stopped sleeping");
		print_message(philo, "thinking");
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
		pthread_mutex_lock(&ph[0].data.m_check);
		printf("ph %d count down %ld \n", ph[i].id, (ph[i].death_clock - get_time()));
		if (ph[i].death_clock)
		{
			if (ph[i].data.dead == 1)
				return (NULL);
			//printf("philosopher %d time left in ms %ld \n", ((t_philos	*)philo)[i].id, ph[i].death_clock - get_time());
			if (!ph[i].is_eating && (ph[i].death_clock < get_time()))
			{
				printf("the mighty philosopher %d has died\n", ph[i].id);
				ph[0].data.dead = 1;
				return (0);
			}
		}
		usleep(1000);	                                                                                                                                                                                                                                                        
		if (i >= ph[1].data.philo_count - 1)
			i = 0;
		else
			i++;
		pthread_mutex_unlock(&ph[0].data.m_check);
	}
	return (0);
}
