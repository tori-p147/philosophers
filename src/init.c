/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:29 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/10/19 17:29:35 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
detach all created threads when failed create thread
*/
int	try_create_thread(t_all *all, int i, int n)
{
	all->philos[i].start_time = get_millis_time();
	// printf("phil id %d\n", all->philos[i].id);
	if (pthread_create(&all->philos[i].thread, NULL, do_action,
			(void *)(&all->philos[i])) != 0)
	{
		printf("Create thread error");
		printf("n = %d\n", n);
		while (n--)
			pthread_detach(all->philos[n].thread);
		return (0);
	}
	return (1);
}

int	init_thread_pool(t_all *all, int n)
{
	int	i;
	
	i = 0;
	// print_philos(all, n);
	while (i < n)
	{
		if (!try_create_thread(all, i, n))
			return (0);
		i++;
	}
	i = 0;
	while (i < n)
	{
		pthread_join(all->philos[i].thread, NULL);
		i++;
	}
	return (1);
}

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
	return (1);
}

int	init_all(t_all *all, int *args)
{
	int				philos_count;
	t_philo			*ptr;
	pthread_mutex_t	*forks_ptr;
	int				i;

	i = 0;
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
	// print_philos(all, philos_count);
	return (1);
}
