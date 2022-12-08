#include "../philo.h"

int	init_mutex_and_philos(t_data *data, t_philos *philo)
{
	int	i;

	printf("%p%p\n", data, philo); //APPARENTLY HAS TO BE THERE!
	//make struct for each philosopher
	i = 0;
	init_mutex(data);
	while (i < data->philo_count)
	{
		philo[i].id = i;
		philo[i].death_clock = 0;
		philo[i].data = *data;
		philo[i].is_eating = 0;
		philo[i].dead = 0;
		if (data->eat_total)
			philo[i].eat_count = data->eat_total;
		philo[i].id = i;
		philo[i].lfork = &data->mutex[i];
		philo[i].rfork = &data->mutex[(i + 1) % data->philo_count];
		i++;
	}
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	if ((data->mutex = ft_calloc((size_t)(data->philo_count + 1), sizeof(pthread_mutex_t))) == NULL)
		return (1);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->mutex[i], NULL);
		pthread_mutex_lock(&data->mutex[i]);
		i++;
	}
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	data->dead = 0;
	if (1 > (data->philo_count = ft_atoi(argv[1])))
		return (1);
	if (1 > (data->time_to_die = ft_atoi(argv[2])))
		return (1);
	if (1 > (data->time_to_eat= ft_atoi(argv[3]) * 1000))
		return (1);
	if (1 > (data->time_to_sleep = ft_atoi(argv[4]) * 1000))
		return (1);
	if (argv[5])
	{
		if (1 > (data->eat_total = ft_atoi(argv[5]) * 1000))
			return (1);
	}
	if (data->philo_count  > 100)
	{
		printf("too many philosophers");
		return (1);
	}
	return (0);
}