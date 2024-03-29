/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:14:36 by nick              #+#    #+#             */
/*   Updated: 2023/03/13 16:21:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 1. number_of_philosophers 
// 2. time_to_die 
// 3. time_to_eat
// 4. time_to_sleep 
// 5. [number_of_times_each_philosopher_must_eat]
// External functs. memset, printf, malloc, free, write,
// usleep, gettimeofday, pthread_create,
// pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, p
//gcc -pthread main.c
// int	main(int argc, char **argv);
// clear && make re && valgrind -v --leak-check=yes ./philo 2 1000 50 50
#include "../philo.h"

/* check if the number of arguments is correct
*/
int	check_argc(int argc)
{
	if (argc < 5 || 6 < argc)
	{
		ft_printf("argc not correct\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		*data;
	t_philos	*philo;

	if (check_argc(argc))
		return (1);
	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		return (1);
	if (init_data(data, argv))
	{
		free(data);
		return (1);
	}
	philo = ft_calloc((data->philo_count + 1), sizeof(t_philos));
	if (philo == NULL)
		return (1);
	if (init_mutex_and_philos(data, philo))
		return (1);
	if (create_threads(data, philo))
		return (1);
	if (free_destroy(data, philo))
		return (1);
	return (0);
}
