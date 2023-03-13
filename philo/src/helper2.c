/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:17:10 by nick              #+#    #+#             */
/*   Updated: 2023/03/13 16:23:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


/* check when philo ate last time which is stores in last_meal
*/
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

/* updates time since last meal when thread starts or every time philophers starts eating again
*/
int	update_last_meal(t_philos *ph)
{
	pthread_mutex_lock(&ph->data->m_check);
	ph->last_meal = get_time();
	pthread_mutex_unlock(&ph->data->m_check);
	return (0);
}

/* decrements eat_count variable. If philo ate enough, then it decrements philo_still_eating, to keep track of how manye are still eating
*/
int	update_eating(t_philos *ph)
{
	pthread_mutex_lock(&ph->data->m_check);
	ph->eat_count--;
	if (ph->eat_count == 0)
	{
		ph->data->philo_still_eating--;
		pthread_mutex_unlock(&ph->data->m_check);
		while (!check_dead_var(ph))
		{
			update_last_meal(ph);
			usleep(30000);
		}
		return (1);
	}
	pthread_mutex_unlock(&ph->data->m_check);
	return (0);
}

/* checks if philo is dead. If so, it sets the dead variable to 1, and prints the message
*/
int	time_ran_out(t_philos ph)
{
	pthread_mutex_lock(&ph.data->m_check);
	if (ph.last_meal - get_time() + ph.data->time_to_die <= 0)
	{
		set_dead_var(&ph);
		pthread_mutex_lock(&ph.data->m_print);
		ft_printf("%l %d %s\n", get_time() - ph.last_meal, ph.id, "died");
		pthread_mutex_unlock(&ph.data->m_print);
		pthread_mutex_unlock(&ph.data->m_check);
		return (1);
	}
	pthread_mutex_unlock(&ph.data->m_check);
	return (0);
}

/* if all are done eating then it sets dead_var
*/
int	all_done_eating(t_philos ph)
{
	pthread_mutex_lock(&ph.data->m_check);
	if (ph.data->philo_still_eating < 1)
	{
		set_dead_var(&ph);
		pthread_mutex_unlock(&ph.data->m_check);
		return (1);
	}
	pthread_mutex_unlock(&ph.data->m_check);
	return (0);
}
