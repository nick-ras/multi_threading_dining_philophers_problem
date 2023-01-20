/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:09:46 by nick              #+#    #+#             */
/*   Updated: 2023/01/20 10:59:45 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	do_routine(t_philos *ph)
{
	print_message(ph, "is eating");
	update_last_meal(ph);
	usleep_function(ph->data->time_to_eat);
	unlock_philo(ph);
	if (ph->data->eat_total > 0)
		if (update_eating(ph))
			return (1);
	print_message(ph, "is sleeping");
	usleep_function(ph->data->time_to_sleep);
	print_message(ph, "is thinking");
	return (0);
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
			lock_philo(philo);
			if (do_routine(ph))
				return (NULL);
		}
	}
	else
	{
		lock_philo(ph);
		while (1)
			if (check_dead_var(ph))
				return (NULL);
	}
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
		{
			if (time_ran_out(ph[i]))
				return (NULL);
			else if (ph->data->eat_total > 0)
				if (all_done_eating(ph[0]))
					return (NULL);
		}
		if (i == ph[0].data->philo_count - 1)
			i = -1;
		usleep(200);
	}
	return (NULL);
}
