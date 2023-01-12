/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:14:24 by nick              #+#    #+#             */
/*   Updated: 2023/01/12 13:24:22 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_mutex_and_philos(t_data *data, t_philos *philo)
{
	int	i;

	i = 0;
	init_mutex(data);
	while (i < data->philo_count)
	{
		philo[i].id = i;
		philo[i].last_meal = 0;
		pthread_mutex_init(&philo[i].m_last_meal, NULL);
		philo[i].data = data;
		philo[i].eat_count = data->eat_total;
		philo[i].lfork = &data->m_forks[i];
		philo[i].rfork = &data->m_forks[(i + 1) % data->philo_count];
		i++;
	}
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	data->m_forks = ft_calloc((data->philo_count + 1), sizeof(pthread_mutex_t));
	if (data->m_forks == NULL)
		return (1);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->m_forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->m_dead, NULL);
	pthread_mutex_init(&data->m_living, NULL);
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	data->dead = 0;
	data->philo_count = ft_atoi(argv[1]);
	if (1 > data->philo_count)
		return (1);
	data->philo_living = data->philo_count;
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
// if (data->philo_count  > 100)
// {
// 	ft_printf("too many philosophers");
// 	return (1);
// }
