/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:29 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/18 15:30:41 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_philo *philo, t_all *all, int *args)
{
	philo->meal_eaten = 0;
	philo->is_eating = false;
	philo->time_to_die = args[1];
	philo->time_to_eat = args[2];
	philo->time_created = get_millis_time();
	philo->time_last_meal = philo->time_created;
	philo->time_to_sleep = args[3];
	philo->lfork_mtx = &all->forks[philo->id - 1];
	philo->rfork_mtx = &all->forks[(philo->id) % all->philos_count];
	philo->all = all;
	return (1);
}

int	alloc_all(t_all *all)
{
	pthread_mutex_t	*forks_ptr;
	int				i;

	i = 0;
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
	return (1);
}

void	init_mtx(t_all *all)
{

	pthread_mutex_init(&all->time_mtx, NULL);
	pthread_mutex_init(&all->meal_mtx, NULL);
	// pthread_mutex_init(&all->eat_limit, NULL);
	pthread_mutex_init(&all->print_mtx, NULL);
}

int	init_all(t_all *all, int *args)
{
	t_philo	*ptr;
	size_t	i;

	all->philos_count = args[0];
	alloc_all(all);
	init_mtx(all);
	ptr = all->philos;
	all->dead_flag = false;
	all->ph_finished = 0;
	if (!args[4])
		all->meal_stock = 0;
	else
		all->meal_stock = args[4];
	i = -1;
	while (++i < all->philos_count)
	{
		all->philos->id = i + 1;
		init_philo(all->philos, all, args);
		all->philos++;
	}
	all->philos = ptr;
	return (1);
}
