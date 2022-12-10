#include "../philo.h"

unsigned long get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_message(t_philos *philo, char *msg)
{
	if (philo->data.dead)
	{
			return ;
	}
	printf("philo %d %s\n", philo->id, msg);
}

int	lock_philo(t_philos *philo)
{
	if (philo->id % 2 == 0 && !((t_philos	*)philo)->dead)
	{
		pthread_mutex_lock(philo->lfork);
		print_message(philo, "take_lfork");
		pthread_mutex_lock(philo->rfork);
		print_message(philo, "take_rfork");
	}
	if (philo->id % 2 == 1  && !((t_philos	*)philo)->dead)
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
