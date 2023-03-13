/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:17:23 by nick              #+#    #+#             */
/*   Updated: 2023/03/13 16:19:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// sets the dead variable to 1 if dead, so other threads can see it
void	set_dead_var(t_philos *ph)
{
	pthread_mutex_lock(&ph->data->m_dead);
	ph->data->stop_dinner = 1;
	pthread_mutex_unlock(&ph->data->m_dead);
}

/* paused the thread for the amount of time specified in the argument. Since usleep is not precise i had to use a while loop to a more precise time.
*/
void	usleep_function(long long target)
{
	long long	start;

	start = get_time();
	while (get_time() < start + target)
		usleep(((start + target - get_time()) * 1000) / 2);
}

/* returns the current time in milliseconds
*/
long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
