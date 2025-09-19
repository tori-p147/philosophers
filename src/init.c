/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:29 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/09/19 21:57:30 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*init_mtxs(pthread_mutex_t *mtxs, t_all *all)
{
	pthread_mutex_t	*ptr;

	mtxs = malloc(sizeof(pthread_mutex_t) * 3);
	if (!mtxs)
		return (NULL);
	ptr = mtxs;
	all->meal_mtx = mtxs;
	all->dead_mtx = mtxs++;
	all->write_mtx = mtxs;
	mtxs = ptr;
	pthread_mutex_init(all->meal_mtx, NULL);
	pthread_mutex_init(all->dead_mtx, NULL);
	pthread_mutex_init(all->write_mtx, NULL);
	int i = 0;
	while(i < 3)
	{
		printf("mtx = %p\n", mtxs);
		mtxs++;
		i++;
	}
	mtxs = ptr;
	return (mtxs);
}

int	init_philo(t_philo *philo, pthread_t *threads, int i, int *args)
{
	philo->id = i;
	philo->thread = threads[i];
	philo->philos_count = args[0];
	philo->die_time = args[1];
	philo->eat_time = args[2];
	philo->sleep_time = args[3];
	if (args[4])
		philo->meal_stock = args[4];
	else
		philo->meal_stock = 0;
	philo->think_time = 0;
	philo->start_time = 0;
	philo->lfork_mtx = malloc(sizeof(pthread_mutex_t));
	if (!philo->lfork_mtx)
		return (0);
	philo->rfork_mtx = malloc(sizeof(pthread_mutex_t));
	if (!philo->rfork_mtx)
		return (0);
	pthread_mutex_init(philo->lfork_mtx, NULL);
	pthread_mutex_init(philo->rfork_mtx, NULL);
	printf("init philo %d\n", i);
	return (1);
}

int	init_all(t_all *all, pthread_t *threads, int *args)
{
	int		number_of_philos;
	int		i;
	t_philo	*curr;
	t_philo	*ptr;

	curr = alloc_philos(all->philos, *args);
	if (!curr)
		return (free_composite(args, threads, NULL, *args));
	pthread_mutex_t	*mtxs = NULL;
	number_of_philos = args[0];
	i = 0;
	printf("init all start\n");
	mtxs = init_mtxs(mtxs, all);
	if (!mtxs)
	{
		free_composite(args, threads, all, number_of_philos);
		return (0);
	}
	ptr = curr;
	while (i < number_of_philos)
	{
		if (!init_philo(curr, threads, i, args))
		{
			free_composite(args, threads, all, number_of_philos);
			return (0);
		}
		curr->dead_mtx = all->dead_mtx;
		curr->meal_mtx = all->meal_mtx;
		curr->write_mtx = all->write_mtx;
		curr++;
		i++;
	}
	all->philos = ptr;
	all->dead_flag = false;
	printf("init all OK\n");
	print_philos(all, number_of_philos);
	return (1);
}
