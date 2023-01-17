/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:16:48 by nick              #+#    #+#             */
/*   Updated: 2023/01/17 15:26:32 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

//ph->last_meal - get_time() + ph->data->time_to_die
int	print_message(t_philos *ph, char *msg)
{
	if (check_dead_var(ph))
		return (1);
	pthread_mutex_lock(&ph->data->m_check);
	ft_printf("%l %d %s\n", get_time() - ph->last_meal, ph->id, msg);
	pthread_mutex_unlock(&ph->data->m_check);
	return (0);
}

int	lock_philo(t_philos *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->lfork);
		print_message(philo, "has taken a fork");
		if (philo->data->philo_count > 1)
		{
			pthread_mutex_lock(philo->rfork);
			print_message(philo, "has taken a fork");
		}
	}
	else if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->rfork);
		print_message(philo, "has taken a fork");
		if (philo->data->philo_count > 1)
		{
			pthread_mutex_lock(philo->lfork);
			print_message(philo, "has taken a fork");
		}
	}
	return (1);
}

int	unlock_philo(t_philos *philo)
{
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	return (0);
}

//printf("id %d dead var = %d\n", philo->id, philo->data->dead);
int	check_dead_var(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->m_dead);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->m_dead);
	return (0);
}
