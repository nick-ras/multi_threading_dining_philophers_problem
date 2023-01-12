/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:16:48 by nick              #+#    #+#             */
/*   Updated: 2023/01/12 11:40:19 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	print_message(t_philos *ph, char *msg)
{
	if (check_dead_var(ph))
		return (1);
		//ph->data->time_to_die - 
	printf("%ld %d %s\n", get_time() - ph->last_meal + ph->data->time_to_die, ph->id, msg); //replace with get_time()
	return (0);
}

int	lock_philo(t_philos *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->lfork);
		print_message(philo, "has taken a fork");
		if (philo->data->philo_count > 1)
		{
			pthread_mutex_lock(philo->rfork);
			print_message(philo, "has taken a fork");
		}
	}
	else if (philo->id % 2 == 1 || philo->data->philo_count > 1)
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
	ft_printf("id %d unlocked\n", philo->id);
	return (0);
}

//printf("id %d dead var = %d\n", philo->id, philo->data->dead);
int	check_dead_var(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->m_dead);
	if (philo->data->dead)
	{
		printf("id %d dead\n", philo->id);
		pthread_mutex_unlock(&philo->data->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->m_dead);
	return (0);
}
