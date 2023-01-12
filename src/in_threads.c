/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:09:46 by nick              #+#    #+#             */
/*   Updated: 2023/01/12 19:55:17 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	create_threads(t_data *data, t_philos *philo)
{
	int	i;

	if (pthread_create(&data->check_philo_dead, NULL, &check_death, philo))
		return (1);
	if (data->eat_total > 0)
		if (pthread_create(&data->check_done_eating, NULL, &check_done_eating, philo))
			return (1);
	i = -1;
	while (++i < data->philo_count)
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]))
			return (1);
	return (0);
}

void	usleep_function(long long target)
{
	long long start;
	long long temp;

	start = get_time();
	while ((temp = get_time()) < start + target)
	{
		//printf("usleep = %lld\n", (start + target - temp) / 2);
		usleep((start + target - temp) / 2);
	}
}

void	*routine(void *philo)
{
	t_philos	*ph;
	ph = (t_philos *)philo;
	update_last_meal(ph);
	if (ph->data->philo_count > 1)
	{
		while (1)
		{
			if (check_dead_var(philo))
				return (NULL);
			if (lock_philo(philo))
			{
				print_message(philo, "is eating");
				update_last_meal(ph);
				usleep_function(ph->data->time_to_eat);
				unlock_philo(philo);
				if (ph->data->eat_total > 0)
					if (update_eating(ph))
						return (NULL);
				print_message(philo, "is sleeping");
				usleep_function(ph->data->time_to_sleep);
				print_message(philo, "is thinking");
			}
		}
	}
	else
		print_message(philo, "has taken a fork");
	return (NULL);
}

void	*check_death(void	*philos)
{
	int				i;
	t_philos		*ph;

	ph = (t_philos *)philos;
	i = -1;
	while (1)
	{
		if (clock_started(&ph[++i]))
			if (time_ran_out(ph[i]))
				return (NULL);
		if (i >= (ph[0].data->philo_count) - 1)
			i = -1;
		usleep(200);
	}
	return (NULL);
}

void	*check_done_eating(void	*philo)
{
	t_philos		*ph;

	ph = (t_philos *)philo;
	while (1)
	{
		if (clock_started(ph))
		{
			while (1)
			{
				if(check_dead_var(philo))
					return (NULL);
				pthread_mutex_lock(&ph->data->m_living);
				if (ph->data->philo_living < 1)
				{
					if(check_dead_var(philo))
					return (NULL);
					ft_printf("All done eating\n"); //DELETE
					pthread_mutex_lock(&ph->data->m_dead);
					ph->data->dead = 1;
					pthread_mutex_unlock(&ph->data->m_dead);
					pthread_mutex_unlock(&ph->data->m_living);
					return (NULL);
				}
				pthread_mutex_unlock(&ph->data->m_living);
				usleep(600);
			}
		}
	}
	return (NULL);
}

