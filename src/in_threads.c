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
	t_philos n_philo;

	n_philo = *(t_philos *)philo;
	n_philo.death_clock = get_time() + n_philo.data.time_to_die * 1000;
	if(pthread_create(&n_philo.check_thread, NULL, &check_death, philo))
		return (philo);
	while (1)
	{
		lock_philo(&n_philo);
		//make eat func with nedenstående
		n_philo.is_eating = 1;
		n_philo.eat_count--;
		usleep(n_philo.data.time_to_eat * 1000);
		//eat, sleep, think
		n_philo.is_eating = 0;
		if (n_philo.dead)
			return (philo);
		unlock_philo(&n_philo);
	}
	//TAKE FORKS and display message before taking other fork, remember equal is right first
	//HOW TO CHECK WHICH THREAD YOU ARE IN??
	//if equal number check right 
	// while (1)
	// {
	// 	if (data->curr_nb % 2 == 0)
	//			
	// }
	return (philo); //RETURN WHAT????
}

void	*check_death(void *philo)
{
	t_philos	*n_philo;
	int i;

	n_philo = (t_philos*) philo;
	i = 0;
		//CHECK IF THREAD IS INITIATED??
		//SET INIT PARAMETER WHEN INIT THREAT`?
	while (1)
	{
		if (n_philo[i].death_clock)
		{
			sleep(1);
			printf("philosopher %d time left in ms %ld\n", i, n_philo[i].death_clock - get_time());
			if (!n_philo->is_eating && (n_philo[i].death_clock) < get_time())
			{
				printf("the mighty philosopher %d has died \n", n_philo[i].id);
				i = 0;
				n_philo[i].data.dead = 1;
				return (philo);
			}
			usleep(1000);
			if (n_philo->data.dead == 1)
				return (philo);
		}
	}
	return (philo);
}

int join_threads(t_philos *philo)
{
	int i;

	i = 0;
	while (i < philo[0].data.philo_count)
	{
		printf("joining routine %d\n", i);
		if (!pthread_join(philo[i].check_thread, NULL))
			return (1);
		if (!pthread_join(philo[i].thread, NULL))
			return (1);
		i++;
	}
	return (0);
}