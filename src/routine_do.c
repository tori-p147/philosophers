/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_do.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:25:31 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/21 21:55:16 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*do_monitoring(void *arg)
{
	t_all	*all;
	size_t	i;

	all = (t_all *)arg;
	while (1)
	{
		i = -1;
		all->ph_finished = 0;
		while (++i < all->philos_count)
		{
			if (check_die(&all->philos[i]))
				return (NULL);
			if (check_eaten_meal(&all->philos[i]))
				all->ph_finished++;
		}
		if (all->ph_finished == all->philos_count)
			return (NULL);
	}
	return (NULL);
}

void	*do_action(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->all->philos_count == 1)
	{
		print_message(philo, FORK);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat / 2, philo);
	while (1)
	{
		if (exit_dead_flag(philo))
			return (NULL);
		if (check_eaten_meal(philo))
			return (NULL);
		do_eat(philo);
		if (exit_dead_flag(philo))
			return (NULL);
		do_sleep(philo);
		if (exit_dead_flag(philo))
			return (NULL);
		do_think(philo);
	}
	return (NULL);
}

void	do_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->lfork_mtx);
		print_message(philo, FORK);
		pthread_mutex_lock(philo->rfork_mtx);
		print_message(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->rfork_mtx);
		print_message(philo, FORK);
		pthread_mutex_lock(philo->lfork_mtx);
		print_message(philo, FORK);
	}
	set_time_last_meal(philo);
	print_message(philo, EAT);
	ft_usleep(philo->time_to_eat, philo);
	increment_eaten_meal(philo);
	pthread_mutex_unlock(philo->lfork_mtx);
	pthread_mutex_unlock(philo->rfork_mtx);
}

void	do_sleep(t_philo *philo)
{
	print_message(philo, SLEEP);
	ft_usleep(philo->time_to_sleep, philo);
}

void	do_think(t_philo *philo)
{
	print_message(philo, THINK);
}
