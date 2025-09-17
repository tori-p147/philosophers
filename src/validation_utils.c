/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:12:59 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/09/17 21:00:15 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(unsigned long c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

long	ft_atoi_long(const char *str, bool *error)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (*str == 32 || (9 <= *str && *str <= 13))
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (ft_isdigit(*str))
			result = result * 10 + (*str - '0');
		else
		{
			*error = true;
			return (0);
		}
		str++;
	}
	return (result * sign);
}

/**
 * validate args is int, philo <=200, args > 0
 */
int	validate_input_data(int ac, char **av)
{
	int		i;
	long	num;
	bool	is_not_integer;

	i = 1;
	while (i < ac)
	{
		is_not_integer = false;
		num = ft_atoi_long(av[i], &is_not_integer);
		if (is_not_integer || INT_MIN > num || num > INT_MAX)
			return (0);
		if (num == 0 && ac == 6 && i < ac - 1)
			return (0);
		if (i == 1 && num > 200)
			return (0);
		i++;
	}
	return (1);
}
