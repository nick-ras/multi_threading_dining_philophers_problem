/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:16:48 by nick              #+#    #+#             */
/*   Updated: 2023/03/13 16:25:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* handles all printing and makes program safe to use with -helgrind flag of valgrind
*/
int	print_message(t_philos *ph, char *msg)
{
	if (check_dead_var(ph))
		return (1);
	pthread_mutex_lock(&ph->data->m_print);
	ft_printf("%l %d %s\n", get_time() - ph->last_meal, ph->id, msg);
	pthread_mutex_unlock(&ph->data->m_print);
	return (0);
}

/* special algoritms when only 3 philos are present
*/
void	three_philos(t_philos *philo)
{
	if (philo->id == 0)
	{
		pthread_mutex_lock(philo->lfork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->rfork);
		print_message(philo, "has taken a fork");
	}
}

/* locks the forks
*/
int	lock_philo(t_philos *philo)
{
	if (philo->data->philo_count == 3)
		three_philos(philo);
	else if (philo->data->philo_count == 1)
	{
		pthread_mutex_lock(philo->rfork);
		print_message(philo, "has taken a fork");
		pthread_mutex_unlock(philo->rfork);
	}
	else if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->lfork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->rfork);
		print_message(philo, "has taken a fork");
	}
	else if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->rfork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->lfork);
		print_message(philo, "has taken a fork");
	}
	return (0);
}

/* unlocks the forks
*/
*/
int	unlock_philo(t_philos *philo)
{
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	return (0);
}

/* checks if the dinner is over either because all philos ate or one died
*/
int	check_dead_var(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->m_dead);
	if (philo->data->stop_dinner)
	{
		pthread_mutex_unlock(&philo->data->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->m_dead);
	return (0);
}
