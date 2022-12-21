/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:49:01 by nick              #+#    #+#             */
/*   Updated: 2022/12/21 13:14:51 by nick             ###   ########.fr       */
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
	int	philo_living;
	unsigned long	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_total;
	int dead;
	pthread_mutex_t *m_forks;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_living;
	pthread_t	thread_check;
}	t_data;

typedef struct s_philos
{
	int							id;
	pthread_t	thread;
	pthread_t	thread_check;
	unsigned long	death_clock;
	int eat_count;
	int is_eating;
	int	dead;
	pthread_mutex_t	m_dead_clock;
	pthread_mutex_t	m_eating;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	t_data *data;
}	t_philos;

//init
int	init_mutex_and_philos(t_data *data, t_philos *philo);
int	init_mutex(t_data *data);

//free_destroy
int	free_destroy(t_data *data, t_philos *philo);

//checks
int	init_data(t_data *data, char **argv);

//helper
unsigned long get_time(void);
int	print_message(t_philos *philo, char *msg);
int	lock_philo(t_philos *philo);
int	unlock_philo(t_philos *philo);
int check_dead_var(t_philos *philo);
int	clock_started(t_philos *ph);
int	update_clock(t_philos *ph);
int	update_eating(t_philos *ph, int eat);
int	time_ran_out(t_philos ph);
int	check_eat(t_philos ph);
int	stdout_clock(t_philos ph);

//in_threads
void	*routine(void *philo);
void	*check_death(void	*philo);
int	create_threads(t_data *data, t_philos *philo);
int	join_threads(t_data *data, t_philos *philo);

#endif