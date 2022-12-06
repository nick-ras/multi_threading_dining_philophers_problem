/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:49:01 by nick              #+#    #+#             */
/*   Updated: 2022/12/06 15:05:46 by nick             ###   ########.fr       */
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
	int	philo_count;
	time_t	time_to_die;
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
	int is_eating;
	t_data data;
}	t_philos;

//init
int	init_mutex_and_philos(t_data *data, t_philos *philo, char **argv);
int	init_mutex(t_data *data);

//free_destroy
int destroy_mutexes(t_data *data);
int	free_stuff(t_data *data, t_philos *philo);

//checks
int	init_data2(t_data *data, char **argv);
int	init_data(t_data *data, char **argv);

//in_threads
void	*routine(void *philo);
void	*check_death(void *philo);
int	create_threads(t_data *data, t_philos *philo);

#endif