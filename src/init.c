/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:29 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/09 20:07:43 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	run_threads(t_all *all, int n)
{
	int	i;
	// int	j;

	i = 0;
	int j = 0;
	// print_philos(all, n);
	uint64_t start_time = get_millis_time();
	all->start_time = start_time;
	while (i < n)
	{
		all->philos[i].last_meal_time = all->start_time;
		if (pthread_create(&all->philos[i].thread, NULL, do_action,
				&all->philos[i]) != 0)
		{
			while (j < i)
			{
				pthread_join(all->philos[j].thread, NULL);
				j++;
			}
			return (0);
		}
		printf("created philo %d tid=%lu\n", i, (unsigned long)all->philos[i].thread);
		i++;
	}
	if (pthread_create(&all->monitor, NULL, do_monitoring,
			all) != 0)
	{
		j = 0;
		while (j < i)
		{
			pthread_join(all->philos[j].thread, NULL);
			j++;
		}
		return (0);
	}
	i = 0;
	while (i < n)
	{
		printf("joining philo %d tid=%lu\n", i, (unsigned long)all->philos[i].thread);
		pthread_join(all->philos[i].thread, NULL);
		i++;
	}
	
	printf("joining monitor tid=%lu\n", (unsigned long)all->monitor);
	pthread_join(all->monitor, NULL);
	printf("threads was finished");
	return (1);
}

int	init_philo(t_philo *philo, t_all *all, int *args)
{
	philo->is_eating = false;
	philo->philos_count = all->philos_count;
	philo->die_time = args[1];
	philo->eat_time = args[2];
	philo->last_meal_time = all->start_time;
	philo->sleep_time = args[3];
	if (!args[4])
		philo->meal_stock = 0;
	else
		philo->meal_stock = args[4];
	// printf("init philo meal_stock %d\n", philo->meal_stock);
	philo->think_time = 0;
	// pthread_mutex_init(&philo->meal_mtx, NULL);
	philo->lfork_mtx = &all->forks[philo->id - 1];
	philo->rfork_mtx = &all->forks[(philo->id) % all->philos_count];
	philo->all = all;
	return (1);
}

int	init_all(t_all *all, int *args)
{
	t_philo			*ptr;
	pthread_mutex_t	*forks_ptr;
	int				i;

	i = 0;
	all->philos_count = args[0];
	all->ph_thread_pool = alloc_threads(all->philos_count);
	if (!all->ph_thread_pool)
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
	all->goal_flag = false;
	all->start_time = 0;
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
