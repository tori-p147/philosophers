/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:49:34 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/21 19:04:49 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*alloc_forks(int n)
{
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * n);
	if (!forks)
		return (NULL);
	return (forks);
}

pthread_t	*alloc_threads(int n)
{
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * (n));
	if (!threads)
		return (NULL);
	return (threads);
}

t_philo	*alloc_philos(int n)
{
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * n);
	if (!philos)
		return (NULL);
	return (philos);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (*str == '\f' || *str == '\n' || *str == '\r' || *str == '\t'
		|| *str == '\v' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = ((result * 10) + (*str - '0'));
		str++;
	}
	return (result * sign);
}

int	*parse_nums(int ac, char **av, int *args)
{
	int	size;
	int	i;
	int	*ptr;

	size = ac - 1;
	args = malloc(sizeof(int) * (size + 1));
	if (!args)
		return (NULL);
	ptr = args;
	i = 0;
	while (i < size)
	{
		*args = ft_atoi(av[i + 1]);
		args++;
		i++;
	}
	*args = 0;
	args = ptr;
	return (args);
}
