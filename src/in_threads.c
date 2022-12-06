#include "../philo.h"

void	*routine(void *philo)
{
	t_philos n_philo;

	n_philo = *(t_philos *)philo;
		//CHECK IF THREAD IS INITIATED??
		//printf("check_death: id %d i %d\n", (n_philo[2]).id, i);
		
	
	//pthread_create(&thr, NULL, &check_death, n_philo); //IF == NULL
	gettimeofday(&n_philo.time_since_eat, NULL);
	printf("routine: id %d time %ld \n", n_philo.id, n_philo.time_since_eat.tv_sec); //n_philo->time_since_eat.tv_sec); //THIS DOESNT WORK

	while (1)
	{
		//eat, sleep, think
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
	struct timeval	curr;
	int i;

	n_philo = (t_philos*) philo;
	i = 0;
	while (i < 6)
	{
		//CHECK IF THREAD IS INITIATED??
		//printf("check_death: id %d i %d\n", (n_philo[2]).id, i);
		gettimeofday(&curr, NULL);
		printf("curr %ld - since eat %ld time do die %ld\n", curr.tv_sec, n_philo[i].time_since_eat.tv_sec, n_philo[i].data.time_to_die);

		// if (!n_philo->is_eating && (curr.tv_sec - n_philo[i].time_since_eat.tv_sec) > n_philo[i].data.time_to_die)
		// {
		// 	printf("the mighty philosopher %d has died \n", n_philo[i].id);
		// 	pthread_join(n_philo[i].thread, NULL);
		// 	sleep(0.7);
		// 	printf("joining %d thread %ld\n", n_philo[i].id, n_philo[i].thread);
		// }
		// if (i >= (n_philo[i].data.philo_count - 1))
		// 	exit (1); //i = 0
		// else
		i++;
	}
	return (philo);
}