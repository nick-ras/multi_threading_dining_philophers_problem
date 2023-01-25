/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 20:43:09 by nickras           #+#    #+#             */
/*   Updated: 2023/01/25 12:27:18 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//My own implementation of the C library function

int	loop_atoi(const char *str, int count, int sign, long int number)
{
	number = 0;
	while (str[count] != '\0' && str[count] <= '9' && str[count] >= '0')
	{
		if (number > 2147483648 && sign == -1)
			return (0);
		if (number > 2147483647 && sign == 1)
			return (-1);
		number = number * 10 + (str[count] - '0');
		count++;
	}
	if (str[count] != 0)
		return (0);
	return (number);
}

int	ft_atoi(const char *str)
{
	int			sign;
	int			count;
	long int	number;

	count = 0;
	sign = 1;
	while (str[count] == 32 || (str[count] <= 13 && str[count] >= 9))
		count++;
	if (str[count] == '-' || str[count] == '+')
	{
		if (str[count] == '-')
				sign = -1;
		count++;
	}
	number = loop_atoi(str, count, sign, number);
	return (sign * number);
}

/* int	main(void)
{


	
	printf("%d", ft_atoi("-5467777777"));
	return (0);
} */
