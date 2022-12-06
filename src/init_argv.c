#include "../philo.h"

int	init_data2(t_data *data, char **argv)
{
	if (!ft_strncmp(argv[3], "0", ft_strlen(argv[3])) && ft_strlen(argv[3]) == 1)
		data->time_to_eat = 0;
	else
	{
		if (!(data->time_to_eat= ft_atoi(argv[3])))
			return (1);
	}
	if (!ft_strncmp(argv[4], "0", ft_strlen(argv[4])) && ft_strlen(argv[4]) == 1)
		data->time_to_sleep = 0;
	else
	{
		if (!(data->time_to_sleep = ft_atoi(argv[4])))
			return (1);
	}
	if (argv[5])
	{
		if (!ft_strncmp(argv[5], "0", ft_strlen(argv[5])) && ft_strlen(argv[5]) == 1)
			data->nb_times_eat = 0;
		else
		{
			if (!(data->nb_times_eat = ft_atoi(argv[5])))
				return (1);
		}
	}
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	if (!ft_strncmp(argv[1], "0", ft_strlen(argv[1])) && ft_strlen(argv[1]) == 1)
		data->philo_count = 0;
	else
	{
		if (!(data->philo_count = ft_atoi(argv[1])))
			return (1);
	}
	if (!ft_strncmp(argv[2], "0", ft_strlen(argv[2])) && ft_strlen(argv[2]) == 1)
		data->time_to_die = 0;
	else
	{
		if (!(data->time_to_die = ft_atoi(argv[2])))
			return (1);
	}
	init_data2(data, argv);
	//check if numbers are under requirement
	if (data->philo_count > 100 || data->nb_times_eat > 100 || data->time_to_die > 20000000 \
	|| data->time_to_eat > 100 || data->time_to_sleep > 100)
	{
		printf("do not meet argv requirements i set up to avoid infinity\n");
		return (1);
	}
	printf("philocount from init %d\n", data->philo_count);
	return (init_mutex(data));
}