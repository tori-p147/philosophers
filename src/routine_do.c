/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_do.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:25:31 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/16 18:55:59 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*do_monitoring(void *arg)
{
	t_all	*all;
	size_t	i;
	size_t	finished_ph_counter;
	size_t	eaten;

	all = (t_all *)arg;
	while (1)
	{
		finished_ph_counter = 0;
		i = -1;
		while (++i < all->philos_count)
		{
			pthread_mutex_lock(&all->meal_mtx);
			eaten = all->philos[i].meal_eaten;
			pthread_mutex_unlock(&all->meal_mtx);
			if (all->meal_stock > 0 && eaten >= all->meal_stock)
			{
				finished_ph_counter++;
				continue ;
			}
			if (check_die(&all->philos[i]))
			{
				set_dead_flag(&all->philos[i]);
				print_die_time(&all->philos[i],
					get_elapsed_time(all->philos[i].time_created));
				return (NULL);
			}
		}
		if (finished_ph_counter >= all->philos_count)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

void	*do_action(void *arg)
{
	t_philo	*philo;
	size_t	eaten;

	philo = (t_philo *)arg;
	if (philo->all->philos_count == 1)
	{
		print_message(philo, get_elapsed_time(philo->time_created), FORK);
		return (NULL);
	}
	while (1)
	{
		if (exit_dead_flag(philo))
			return (NULL);
		if (!check_can_eat(philo))
			continue ;
		do_eat(philo);
		pthread_mutex_lock(&philo->all->meal_mtx);
		eaten = philo->meal_eaten;
		pthread_mutex_unlock(&philo->all->meal_mtx);
		if (philo->all->meal_stock > 0 && eaten >= philo->all->meal_stock)
			return (NULL);
		do_sleep(philo);
		do_think(philo);
	}
	return (NULL);
}

void	do_eat(t_philo *philo)
{
set_state(philo, 1);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->lfork_mtx);
		pthread_mutex_lock(philo->rfork_mtx);
	}
	else
	{
		pthread_mutex_lock(philo->rfork_mtx);
		pthread_mutex_lock(philo->lfork_mtx);
	}
	
	print_message(philo, get_elapsed_time(philo->time_created), FORK);
	print_message(philo, get_elapsed_time(philo->time_created), FORK);
	print_message(philo, get_elapsed_time(philo->time_created), EAT);
	set_time_last_meal(philo);
	ft_usleep(philo->time_to_eat, philo);
	increment_eaten_meal(philo);
	set_state(philo, 0);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->rfork_mtx);
		pthread_mutex_unlock(philo->lfork_mtx);
	}
	else
	{
		pthread_mutex_unlock(philo->lfork_mtx);
		pthread_mutex_unlock(philo->rfork_mtx);
	}
}

void	do_sleep(t_philo *philo)
{
	print_message(philo, get_elapsed_time(philo->time_created), SLEEP);
	ft_usleep(philo->time_to_sleep, philo);
}

void	do_think(t_philo *philo)
{
	print_message(philo, get_elapsed_time(philo->time_created), THINK);
}
