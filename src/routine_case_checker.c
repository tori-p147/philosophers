/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_case_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:07:25 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/26 13:50:06 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_die(t_philo *philo)
{
	uint64_t	last_meal;

	pthread_mutex_lock(&philo->all->meal_mtx);
	if (philo->is_finished)
	{
		pthread_mutex_unlock(&philo->all->meal_mtx);
		return (0);
	}
	last_meal = philo->time_last_meal;
	pthread_mutex_unlock(&philo->all->meal_mtx);
	if (get_millis_time() - last_meal > philo->time_to_die)
	{
		pthread_mutex_lock(&philo->all->state_mtx);
		philo->all->dead_flag = 1;
		pthread_mutex_unlock(&philo->all->state_mtx);
		pthread_mutex_lock(&philo->all->print_mtx);
		printf("%lu %ld died\n", get_elapsed_time(philo->time_created),
			philo->id);
		pthread_mutex_unlock(&philo->all->print_mtx);
		return (1);
	}
	return (0);
}

int	check_exit_flags(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->meal_mtx);
	if (philo->is_finished)
		return (1);
	pthread_mutex_unlock(&philo->all->meal_mtx);
	pthread_mutex_lock(&philo->all->state_mtx);
	if (philo->all->dead_flag || philo->all->is_simulation_end)
	{
		pthread_mutex_unlock(&philo->all->state_mtx);
		return (1);
	}
	pthread_mutex_unlock(&philo->all->state_mtx);
	return (0);
}
