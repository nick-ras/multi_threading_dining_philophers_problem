/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:09:46 by nick              #+#    #+#             */
/*   Updated: 2023/01/12 11:43:57 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	create_threads(t_data *data, t_philos *philo)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]))
			return (1);
		if (i == 0)
		{
			usleep(10);
			if (pthread_create(&data->check_philo_dead, NULL, &check_death, philo))
				return (1);
			if (data->eat_total > 0)
			{
				if (pthread_create(&data->check_done_eating, NULL, &check_done_eating, philo))
					return (1);
			}
		}
	}
	return (0);
}

void	*routine(void *philo)
{
	t_philos	*ph;

	ph = (t_philos *)philo;
	update_clock(ph);
	while (1)
	{
		if (check_dead_var(philo))
			return (NULL);
		if (lock_philo(philo))
		{
			print_message(philo, "is eating");
			update_clock(ph);
			usleep(ph->data->time_to_eat * 1000);
			unlock_philo(philo);
			if (update_eating(ph))
				return (NULL);
			print_message(philo, "is sleeping");
			usleep(ph->data->time_to_sleep * 1000);
			print_message(philo, "is thinking");
		}
	}
	return (NULL);
}

void	*check_death(void	*philo)
{
	int				i;
	int				max;
	t_philos		*ph;

	ph = (t_philos *)philo;
	max = (ph[0].data->philo_count) - 1;
	i = 0;
	while (1)
	{
		if (time_ran_out(ph[++i]))
			return (NULL);
		if (i >= max)
			i = 0;
		usleep(100);
	}
	return (NULL);
}

void	*check_done_eating(void	*philo)
{
	t_philos		*ph;

	ph = (t_philos *)philo;
	while (1)
	{
		pthread_mutex_lock(&ph->data->m_living);
		if (ph->data->philo_living < 1)
		{
			ft_printf("All done eating\n"); //DELETE
			pthread_mutex_unlock(&ph->data->m_living);
			return (NULL);
		}
		pthread_mutex_unlock(&ph->data->m_living);
		usleep(100);
		if(check_dead_var(philo))
			return (NULL);
	}
	return (NULL);
}

