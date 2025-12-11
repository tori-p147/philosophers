/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:29 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/11 21:50:36 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo_case(t_philo *philo)
{
	print_message(philo, "has taken a fork 1");
	ft_usleep(philo->time_to_die);
	write_die_time(philo);
	return (1);
}

int	init_philo(t_philo *philo, t_all *all, int *args)
{
	philo->state = CREATED;
	philo->meal_eaten = 0;
	philo->time_to_die = args[1];
	philo->time_to_eat = args[2];
	philo->time_last_meal = all->time_created;
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
	pthread_mutex_init(&all->state_mtx, NULL);
	pthread_mutex_init(&all->goal_mtx, NULL);
	pthread_mutex_init(&all->meal_mtx, NULL);
	pthread_mutex_init(&all->dead_mtx, NULL);
	pthread_mutex_init(&all->write_mtx, NULL);
}

int	init_all(t_all *all, int *args)
{
	t_philo	*ptr;
	int		i;

	all->philos_count = args[0];
	alloc_all(all);
	init_mtx(all);
	ptr = all->philos;
	all->dead_flag = false;
	all->goal_flag = false;
	if (!args[4])
		all->meal_stock = 0;
	else
		all->meal_stock = args[4];
	all->time_created = 0;
	i = 0;
	while (i < all->philos_count)
	{
		all->philos->id = i + 1;
		init_philo(all->philos, all, args);
		all->philos++;
		i++;
	}
	all->philos = ptr;
	return (1);
}
