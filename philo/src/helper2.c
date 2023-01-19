/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:17:10 by nick              #+#    #+#             */
/*   Updated: 2023/01/19 22:53:25 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//ft_printf("phil %d timeleft %ld\n", ph->id, ph->last_meal - get_time());
int	clock_started(t_philos *ph)
{
	pthread_mutex_lock(&ph->data->m_check);
	if (ph->last_meal)
	{
		pthread_mutex_unlock(&ph->data->m_check);
		return (1);
	}
	pthread_mutex_unlock(&ph->data->m_check);
	return (0);
}

// ft_printf("phil %d clock updated og set %ld\n", ph->id, ph->last_meal);
int	update_last_meal(t_philos *ph)
{
	pthread_mutex_lock(&ph->data->m_check);
	ph->last_meal = get_time();
	pthread_mutex_unlock(&ph->data->m_check);
	return (0);
}

int	update_eating(t_philos *ph)
{
	pthread_mutex_lock(&ph->data->m_check);
	ph->eat_count--;
	if (ph->eat_count <= 0)
	{
		ph->data->philo_living--;
		pthread_mutex_unlock(&ph->data->m_check);
		return (1);
	}
	pthread_mutex_unlock(&ph->data->m_check);
	return (0);
}

//printf("            check_death() results: %lld id %d\n",ph.last_meal 
//- get_time() + ph.data->time_to_die, ph.id);
int	time_ran_out(t_philos ph)
{
	pthread_mutex_lock(&ph.data->m_check);
	if (ph.last_meal - get_time() + ph.data->time_to_die <= 0)
	{
		if (check_dead_var(&ph))
			return (1);
		pthread_mutex_lock(&ph.data->m_print);
		ft_printf("%l %d %s\n", get_time() - ph.last_meal, ph.id, "died");
		return (1);
	}
	pthread_mutex_unlock(&ph.data->m_check);
	return (0);
}

int	all_done_eating(t_philos ph)
{
	pthread_mutex_lock(&ph.data->m_check);
	if (ph.data->philo_living < 1)
	{
		set_dead_var(&ph);
		return (1);
	}
	pthread_mutex_unlock(&ph.data->m_check);
	return (0);
}