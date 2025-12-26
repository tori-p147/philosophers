/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_do.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:25:31 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/26 13:58:21 by vmatsuda         ###   ########.fr       */
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
			if (check_is_finished(&all->philos[i]))
				all->ph_finished++;
			else if (check_die(&all->philos[i]))
				return (NULL);
		}
		if (all->ph_finished == all->philos_count)
		{
			pthread_mutex_lock(&all->state_mtx);
			// printf("goal!!!\n");
			all->is_simulation_end = 1;
			pthread_mutex_unlock(&all->state_mtx);
			return (NULL);
		}
	}
	usleep(1000);
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
		if (check_exit_flags(philo))
			return (NULL);
		do_eat(philo);
		if (check_exit_flags(philo))
			return (NULL);
		do_sleep(philo);
		if (check_exit_flags(philo))
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
		if (check_exit_flags(philo))
		{
			pthread_mutex_unlock(philo->lfork_mtx);
			return ;
		}
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
	check_eaten_meals(philo);
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
