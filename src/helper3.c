/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:17:16 by nick              #+#    #+#             */
/*   Updated: 2023/01/11 12:01:52 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	all_done_eating(t_philos *ph)
{
	pthread_mutex_lock(&ph->data->m_living);
	if (ph->data->philo_living <= 0)
	{
		//printf("IN ALL DONE EATING\n");
		pthread_mutex_unlock(&ph->data->m_living);
		return (1);
	}
	pthread_mutex_unlock(&ph->data->m_living);
	return (0);
}
