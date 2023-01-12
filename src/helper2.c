/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:17:10 by nick              #+#    #+#             */
/*   Updated: 2023/01/12 11:37:11 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//ft_printf("phil %d timeleft %ld\n", ph->id, ph->last_meal - get_time());
int	clock_started(t_philos *ph)
{
	pthread_mutex_lock(&ph->m_dead_clock);
	if (ph->last_meal)
	{
		pthread_mutex_unlock(&ph->m_dead_clock);
		return (1);
	}
	pthread_mutex_unlock(&ph->m_dead_clock);
	return (0);
}

// ft_printf("phil %d clock updated og set %ld\n", ph->id, ph->last_meal);
int	update_clock(t_philos *ph)
{
	pthread_mutex_lock(&ph->m_dead_clock);
	ph->last_meal = get_time();
	pthread_mutex_unlock(&ph->m_dead_clock);
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
	pthread_mutex_lock(&ph.m_dead_clock);
	//printf("check_death() %ld %d\n",get_time() - ph.last_meal + ph.data->time_to_die, ph.id);
	if (get_time() - ph.last_meal + ph.data->time_to_die <= 0)
	{
		pthread_mutex_lock(&ph.data->m_dead);
		ph.data->dead = 1;
		pthread_mutex_unlock(&ph.data->m_dead);
		printf("%ld %d died\n", get_time(), ph.id);
		pthread_mutex_unlock(&ph.m_dead_clock);
		return (1);
	}
	pthread_mutex_unlock(&ph.m_dead_clock);
	return (0);
}
