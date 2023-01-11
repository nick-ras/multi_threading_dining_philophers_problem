/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:16:43 by nick              #+#    #+#             */
/*   Updated: 2023/01/11 16:57:24 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	join_threads(t_data *data, t_philos *philo)
{
	int		i;
	void	*ret;
	void	*ret1;

	i = 0;
	if (pthread_join(data->thread_check, &ret1))
		return (1);
	while (i < data->philo_count)
	{
		if (pthread_join(philo[i].thread, &ret))
			return (1);
		pthread_mutex_destroy(&philo[i].m_dead_clock);
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
