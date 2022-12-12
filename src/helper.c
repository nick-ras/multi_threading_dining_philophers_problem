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
	printf("dead var = %d\n", philo->data.dead);
	if (philo->data.dead)
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
	printf("clock %ld\n", ph->death_clock);
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
	pthread_mutex_lock(&ph->m_dead_clock);
	ph->death_clock = get_time() + ph->data.time_to_die;
	// printf("phil %d clock updated og set %ld\n", ph->id, ph->death_clock);
	pthread_mutex_unlock(&ph->m_dead_clock);
	return (0);
}

int	stdout_clock(t_philos ph)
{
	unsigned long time = get_time();
	pthread_mutex_lock(&ph.m_dead_clock);
	printf("ph %d count down %ld \n", ph.id, (ph.death_clock - time));
	pthread_mutex_unlock(&ph.m_dead_clock);
	return (0);
}

int	update_eating(t_philos *ph, int eat)
{
	pthread_mutex_lock(&ph->m_eating);
	if (eat)
		ph->is_eating = eat;
	else
	{
		ph->eat_count--;
		ph->is_eating = eat;
	}
	pthread_mutex_unlock(&ph->m_eating);
	return (0);
}

int	check_eat(t_philos	*ph)
{
	pthread_mutex_lock(&ph->m_eating);
	if (ph->eat_count <= 0)
	{
		pthread_mutex_unlock(&ph->m_eating);
		return (1);
	}
	pthread_mutex_unlock(&ph->m_eating);
	return (0);
}

int	time_ran_out(t_philos ph)
{
	pthread_mutex_lock(&ph.m_dead_clock);
	pthread_mutex_lock(&ph.m_eating);
	if (!ph.is_eating && (ph.death_clock < get_time()))
	{
		pthread_mutex_unlock(&ph.m_dead_clock);
		pthread_mutex_unlock(&ph.m_eating);
		return (1);
	}
	pthread_mutex_unlock(&ph.m_dead_clock);
	pthread_mutex_unlock(&ph.m_eating);
	return (0);
}
