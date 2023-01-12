/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:17:10 by nick              #+#    #+#             */
/*   Updated: 2023/01/12 13:32:19 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//ft_printf("phil %d timeleft %ld\n", ph->id, ph->last_meal - get_time());
int	clock_started(t_philos *ph)
{
	pthread_mutex_lock(&ph->m_last_meal);
	if (ph->last_meal)
	{
		pthread_mutex_unlock(&ph->m_last_meal);
		return (1);
	}
	pthread_mutex_unlock(&ph->m_last_meal);
	return (0);
}

// ft_printf("phil %d clock updated og set %ld\n", ph->id, ph->last_meal);
int	update_last_meal(t_philos *ph)
{
	pthread_mutex_lock(&ph->m_last_meal);
	ph->last_meal = get_time();
	//ft_printf("last meal %ld\n", ph->last_meal);
	pthread_mutex_unlock(&ph->m_last_meal);
	return (0);
}

int	update_eating(t_philos *ph)
{
	ph->eat_count--;
	if (ph->eat_count <= 0)
	{
		pthread_mutex_lock(&ph->data->m_living);
		ph->data->philo_living--;
		pthread_mutex_unlock(&ph->data->m_living);
		return (1);
	}
	return (0);
}

int	time_ran_out(t_philos ph)
{
	pthread_mutex_lock(&ph.m_last_meal);
	//printf("            check_death() results: %lld id %d\n",ph.last_meal - get_time() + ph.data->time_to_die, ph.id);
	if (ph.last_meal - get_time() + ph.data->time_to_die <= 0)
	{
		pthread_mutex_lock(&ph.data->m_dead);
		ph.data->dead = 1;
		pthread_mutex_unlock(&ph.data->m_dead);
		printf("%lld %d died\n", get_time(), ph.id);
		pthread_mutex_unlock(&ph.m_last_meal);
		return (1);
	}
	pthread_mutex_unlock(&ph.m_last_meal);
	return (0);
}
