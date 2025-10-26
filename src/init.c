/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:29 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/10/26 18:44:35 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
detach all created threads when failed create thread
*/
int	try_create_thread(t_all *all, int i, int n, void *(*routine)(void *))
{
	if (routine == do_action)
		all->philos[i].start_time = get_millis_time();
	if (pthread_create(&all->philos[i].thread, NULL, routine,
			&all->philos[i]) != 0)
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
	// all->start_time = get_millis_time();
	while (i < n)
	{
		if (!try_create_thread(all, i, n, do_action))
			return (0);
		i++;
	}
	if (!try_create_thread(all, i, n, do_monitoring))
		return (0);
	i = 0;
	while (i <= n)
	{
		pthread_join(all->philos[i].thread, NULL);
		i++;
	}
	// pthread_join(all->philos[i].thread, NULL);
	return (1);
}

int	init_philo(t_philo *philo, t_all *all, int *args)
{
	philo->is_eating = false;
	philo->philos_count = all->philos_count;
	philo->die_time = args[1];
	philo->eat_time = args[2];
	philo->last_meal_time = 0;
	philo->sleep_time = args[3];
	if (!args[4])
		philo->meal_stock = 0;
	else
		philo->meal_stock = args[4];
	// printf("init philo meal_stock %d\n", philo->meal_stock);
	philo->think_time = 0;
	philo->lfork_mtx = &all->forks[philo->id - 1];
	philo->rfork_mtx = &all->forks[(philo->id) % all->philos_count];
	philo->all = all;
	philo->start_time = 0;
	return (1);
}

int	init_all(t_all *all, int *args)
{
	t_philo			*ptr;
	pthread_mutex_t	*forks_ptr;
	int				i;

	i = 0;
	all->philos_count = args[0];
	all->thread_pool = alloc_thread_pool(all->philos_count);
	if (!all->thread_pool)
		return (0);
	all->forks = alloc_forks(all->philos_count);
	if (!all->forks)
		return (0);
	forks_ptr = all->forks;
	i = all->philos_count;
	while (i--)
		pthread_mutex_init(all->forks++, NULL);
	all->forks = forks_ptr;
	all->philos = alloc_philos(all->philos_count);
	if (!all->philos)
		return (0);
	pthread_mutex_init(&all->meal_mtx, NULL);
	pthread_mutex_init(&all->dead_mtx, NULL);
	pthread_mutex_init(&all->write_mtx, NULL);
	i = 1;
	ptr = all->philos;
	all->dead_flag = false;
	while (i <= all->philos_count)
	{
		all->philos->id = i;
		init_philo(all->philos, all, args);
		all->philos++;
		i++;
	}
	all->philos = ptr;
	
	// print_philos(all, all->philos_count);
	return (1);
}
