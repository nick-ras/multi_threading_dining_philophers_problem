/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:14:24 by nick              #+#    #+#             */
/*   Updated: 2023/03/13 16:19:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* initiate philosopher threads and calls init_mutex
*/
int	init_mutex_and_philos(t_data *data, t_philos *philo)
{
	int	i;

	i = -1;
	init_mutex(data, philo);
	while (++i < data->philo_count)
	{
		philo[i].id = i;
		philo[i].last_meal = 0;
		philo[i].data = data;
		philo[i].eat_count = data->eat_total;
		philo[i].lfork = &data->m_forks[i];
		philo[i].rfork = &data->m_forks[(i + 1) % data->philo_count];
	}
	return (0);
}

/* initiate mutexes and locks
*/
int	init_mutex(t_data *data, t_philos *ph)
{
	int	i;

	data->m_forks = ft_calloc((data->philo_count + 1), sizeof(pthread_mutex_t));
	if (data->m_forks == NULL)
		return (1);
	i = -1;
	while (++i < data->philo_count)
	{
		pthread_mutex_init(&data->m_forks[i], NULL);
		pthread_mutex_init(&ph[i].m_sleep, NULL);
	}
	pthread_mutex_init(&data->m_dead, NULL);
	pthread_mutex_init(&data->m_check, NULL);
	pthread_mutex_init(&data->m_print, NULL);
	return (0);
}

/* initiate data struct with arguments
*/
int	init_data(t_data *data, char **argv)
{
	data->stop_dinner = 0;
	data->philo_count = ft_atoi(argv[1]);
	if (1 > data->philo_count)
		return (1);
	data->philo_still_eating = data->philo_count;
	data->time_to_die = ft_atoi(argv[2]);
	if (1 > data->time_to_die)
		return (1);
	data->time_to_eat = ft_atoi(argv[3]);
	if (1 > data->time_to_eat)
		return (1);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (1 > data->time_to_sleep)
		return (1);
	if (argv[5])
	{
		data->eat_total = ft_atoi(argv[5]);
		if (1 > data->eat_total)
			return (1);
	}
	else
		data->eat_total = -1;
	return (0);
}

/* initiate threads and joins them. Also calls the routine function for each
 thread
*/
int	create_threads(t_data *data, t_philos *philo)
{
	int	i;

	if (pthread_create(&data->check_philo_dead, NULL, &check_death, philo))
		return (1);
	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]))
			return (1);
		usleep(2000);
	}
	usleep(2000);
	if (pthread_join(data->check_philo_dead, NULL))
		return (1);
	i = -1;
	while (++i < data->philo_count)
		if (pthread_join(philo[i].thread, NULL))
			return (1);
	return (0);
}

/* frees all allocated memory and destroys mutexes
*/
int	free_destroy(t_data *data, t_philos *philo)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->m_dead);
	pthread_mutex_destroy(&data->m_check);
	pthread_mutex_destroy(&data->m_print);
	while (++i < data->philo_count)
		pthread_mutex_destroy(&data->m_forks[i]);
	free(data->m_forks);
	free(philo);
	free(data);
	return (0);
}
