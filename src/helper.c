#include "../philo.h"

unsigned long get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	print_message(t_philos *philo, char *msg)
{
	if (check_dead_var(philo))
		return (1);
	printf("philo %d %s\n", philo->id, msg);
	return (0);
}

int	lock_philo(t_philos *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->lfork);
		print_message(philo, "take_lfork");
		pthread_mutex_lock(philo->rfork);
		print_message(philo, "take_rfork");
	}
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->rfork);
		print_message(philo, "take_rfork");
		pthread_mutex_lock(philo->lfork);
		print_message(philo, "take_lfork");
	}
	return (0);
}

int	unlock_philo(t_philos *philo)
{
	 
	pthread_mutex_unlock(philo->lfork);
	print_message(philo, "drop_lfork");
	pthread_mutex_unlock(philo->rfork);
	print_message(philo, "drop_rfork");
	return (0);
}

int check_dead_var(t_philos *philo)
{
	pthread_mutex_lock(&philo->data.m_dead);
	if (((t_philos *)philo)->data.dead)
	{
		pthread_mutex_unlock(&philo->data.m_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data.m_dead);
	return (0);
}

int	clock_started(t_philos *ph)
{
	pthread_mutex_lock(&ph->m_dead_clock);
	if (ph->death_clock)
	{
		pthread_mutex_unlock(&ph->m_dead_clock);
		return (1);
	}
	pthread_mutex_unlock(&ph->m_dead_clock);
	return (0);
}

int	update_clock(t_philos *ph)
{
	pthread_mutex_lock(&ph->data.m_data);
	ph->death_clock = get_time() + ph->data.time_to_die;
	pthread_mutex_unlock(&ph->data.m_data);
	return (0);
}

int	time_ran_out(t_philos *ph)
{
	pthread_mutex_lock(&ph->m_dead_clock);
	pthread_mutex_lock(&ph->m_philo);
	if (ph->is_eating && (ph->death_clock < get_time()))
	{
		pthread_mutex_unlock(&ph->m_dead_clock);
		pthread_mutex_unlock(&ph->m_philo);
		return (1);
	}
	pthread_mutex_unlock(&ph->m_dead_clock);
	pthread_mutex_unlock(&ph->m_philo);
	return (0);
}
