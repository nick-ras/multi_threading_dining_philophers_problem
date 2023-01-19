/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:17:23 by nick              #+#    #+#             */
/*   Updated: 2023/01/17 16:32:06 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	set_dead_var(t_philos *ph)
{
	pthread_mutex_lock(&ph->data->m_dead);
	ph->data->dead = 1;
	pthread_mutex_unlock(&ph->data->m_dead);
}

//printf("usleep = %lld\n", (start + target - temp) / 2);
void	usleep_function(long long target)
{
	long long	start;

	start = get_time();
	while (get_time() < start + target)
		usleep((start + target - get_time()) / 2);
}
