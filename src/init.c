/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:29 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/10/18 17:15:05 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// pthread_mutex_t	*init_mtxs(pthread_mutex_t *mtxs, t_all *all)
// {
// 	pthread_mutex_t	*ptr;

// 	mtxs = malloc(sizeof(pthread_mutex_t) * 3);
// 	if (!mtxs)
// 		return (NULL);
// 	ptr = mtxs;
// 	all->meal_mtx = mtxs;
// 	mtxs++;
// 	all->dead_mtx = mtxs;
// 	mtxs++;
// 	all->write_mtx = mtxs;
// 	pthread_mutex_init(all->meal_mtx, NULL);
// 	pthread_mutex_init(all->dead_mtx, NULL);
// 	pthread_mutex_init(all->write_mtx, NULL);
// 	mtxs = ptr;
// 	return (mtxs);
// }

int	init_philo(t_philo *philo, t_all *all, int *args)
{
	int	philos_n;

	// philo->thread = pthread_create(&all->thread_pool[philo->id], NULL,
	// 		do_action, NULL);
	philos_n = args[0];
	philo->philos_count = philos_n;
	philo->die_time = args[1];
	philo->eat_time = args[2];
	philo->sleep_time = args[3];
	if (!args[4])
		philo->meal_stock = 0;
	else
		philo->meal_stock = args[4];
	// printf("init philo meal_stock %d\n", philo->meal_stock);
	philo->think_time = 0;
	philo->start_time = 0;
	philo->lfork_mtx = &all->forks[philo->id];
	philo->rfork_mtx = &all->forks[(philo->id + 1) % philos_n];
	philo->dead_mtx = &all->dead_mtx;
	philo->meal_mtx = &all->meal_mtx;
	philo->write_mtx = &all->write_mtx;
	printf("init philo %d\n", philo->id);
	return (1);
}

int	init_all(t_all *all, int *args)
{
	int		philos_count;
	t_philo	*ptr;
	pthread_mutex_t	*forks_ptr;

	int i = 0;
	philos_count = args[0];
	all->thread_pool = alloc_thread_pool(philos_count);
	if (!all->thread_pool)
		return (0);
	all->forks = alloc_forks(philos_count);
	if (!all->forks)
		return (0);
	forks_ptr = all->forks;
	i = philos_count;
	while (i--)
		pthread_mutex_init(all->forks++, NULL);
	all->forks = forks_ptr;
	all->philos = alloc_philos(philos_count);
	if (!all->philos)
		return (0);
	pthread_mutex_init(&all->meal_mtx, NULL);
	pthread_mutex_init(&all->dead_mtx, NULL);
	pthread_mutex_init(&all->write_mtx, NULL);
	i = 0;
	printf("init all->philos start\n");
	ptr = all->philos;
	while (i < philos_count)
	{
		all->philos->id = i;
		init_philo(all->philos, all, args);
		all->philos++;
		i++;
	}
	all->philos = ptr;
	all->dead_flag = false;
	printf("init all OK\n");
	print_philos(all, philos_count);
	return (1);
}
