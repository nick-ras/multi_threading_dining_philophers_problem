/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:16:43 by nick              #+#    #+#             */
/*   Updated: 2023/01/12 13:24:22 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	join_threads(t_data *data, t_philos *philo)
{
	int		i;

	i = 0;
	if (pthread_join(data->check_philo_dead, NULL))
		return (1);
	if (data->eat_total > 0)
	{
		if (pthread_join(data->check_done_eating, NULL))
			return (1);
	}
	while (i < data->philo_count)
	{
		if (pthread_join(philo[i].thread, NULL))
			return (1);
		pthread_mutex_destroy(&philo[i].m_last_meal);
		i++;
	}
	return (0);
}

int	free_destroy(t_data *data, t_philos *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->m_dead);
	pthread_mutex_destroy(&data->m_living);
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->m_forks[i]);
		i++;
	}
	free(data->m_forks);
	free(philo);
	free(data);
	return (0);
}
