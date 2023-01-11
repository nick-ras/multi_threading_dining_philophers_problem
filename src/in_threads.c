/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:09:46 by nick              #+#    #+#             */
/*   Updated: 2023/01/11 16:59:08 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	create_threads(t_data *data, t_philos *philo)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]))
			return (1);
		usleep(100);
		i++;
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

int	check_done_eating(t_philos *ph)
{
	if (all_done_eating(ph))
		return (1);
	return (0);
}

void	*check_death(void	*philo)
{
	int				i;
	t_philos		*ph;

	ph = (t_philos *)philo;
	i = 0;
	while (1)
	{
		if (clock_started(&ph[i]))
		{
			if (ph->data->eat_total > 0)
			{
				if (check_done_eating(&ph[i]))
					return (NULL);
			}
			if (time_ran_out(ph[i]))
				return (NULL);
			if (i >= (ph[0].data->philo_count - 1))
				i = 0;
			else
				i++;
		}
		usleep(1000);
	}
	return (NULL);
}
