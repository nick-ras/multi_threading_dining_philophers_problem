/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:49:01 by nick              #+#    #+#             */
/*   Updated: 2022/12/04 22:01:03 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
#	include <sys/time.h>
# include "libftprintf/ft_printf.h"


typedef struct s_data
{
	int	curr_nb;
	int	philo_count;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_times_eat;
	pthread_mutex_t *mutex;
}	t_data;

typedef struct s_philos
{
	int							id;
	pthread_t	thread;
	struct timeval	time_since_eat;
	int eat_count;
	//stuff for each philopher
	t_data	*data;
}	t_philos;

#endif