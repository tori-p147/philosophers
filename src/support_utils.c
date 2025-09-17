/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:49:34 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/09/17 22:44:18 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_t	*alloc_thread_pool(pthread_t *thread_pool, int n)
{
	pthread_t	*ptr;
	int			i;

	printf("n = %d\n", n);
	thread_pool = malloc(sizeof(pthread_t) * n);
	if (!thread_pool)
		return (NULL);
	ptr = thread_pool;
	i = 0;
	while (i < n)
	{
		printf("%p\n", thread_pool);
		thread_pool++;
		i++;
	}
	thread_pool = ptr;
	printf("pool = %p\n", thread_pool);
	return (thread_pool);
}

void	print_philos(t_all *all, int n)
{
	t_philo	*ptr;
	int		i;

	ptr = all->philos;
	all->philos = ptr;
	i = 0;
	while (i < n)
	{
		printf("%p\n", all->philos);
		printf("%lu\n", all->philos[i].thread);
		all->philos++;
		i++;
	}
	all->philos = ptr;
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
	args = malloc(sizeof(int) * size);
	if (!args)
		return (NULL);
	ptr = args;
	i = 0;
	while (i < size)
	{
		printf("%s\n", av[i + 1]);
		*args = ft_atoi(av[i + 1]);
		printf("%d\n", *args);
		args++;
		i++;
	}
	args = ptr;
	return (args);
}

int	now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
