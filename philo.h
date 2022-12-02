/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:49:01 by nick              #+#    #+#             */
/*   Updated: 2022/12/02 21:58:54 by nick             ###   ########.fr       */
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
# include "libftprintf/ft_printf.h"

typedef struct s_data
{
	pthread_mutex_t *mutex_var;
	pthread_t	*threads;
	int	philo_count;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_times_eat;
}	t_data;

#endif