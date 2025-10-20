/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:49:34 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/10/20 21:45:25 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*alloc_forks(int n)
{
	pthread_mutex_t *forks = malloc(sizeof(pthread_mutex_t) * n);
	if (!forks)
		return (NULL);
	return (forks);
}

pthread_t	*alloc_thread_pool(int n)
{
	// pthread_t	*ptr;
	// int			i;
	pthread_t	*thread_pool;

	thread_pool = malloc(sizeof(pthread_t) * (n + 1));
	if (!thread_pool)
		return (NULL);
	// ptr = thread_pool;
	// i = 0;
	// while (i < n)
	// {
	// 	printf("thread %d %p\n", i, thread_pool);
	// 	thread_pool++;
	// 	i++;
	// }
	// thread_pool = ptr;
	// printf("pool = %p\n", thread_pool);
	return (thread_pool);
}

t_philo	*alloc_philos(int n)
{
	t_philo *philos = malloc(sizeof(t_philo) * n);
	if (!philos)
		return (NULL);
	return (philos);
}

void	print_philos(t_all *all, int n)
{
	int	i;

	i = 0;
	t_philo *ptr = all->philos;
	while (i < n)
	{
		printf("id = %d\n", all->philos[i].id);
		printf("lfork = %p\n", all->philos[i].lfork_mtx);
		printf("rfork = %p\n", all->philos[i].rfork_mtx);
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
