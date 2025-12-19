/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_case_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:07:25 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/19 18:54:57 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void check_all_ph_started(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->all->ready_mtx);
// 	philo->all->ready_count++;
// 	pthread_mutex_unlock(&philo->all->ready_mtx);
// }

int	check_die(t_philo *philo)
{
	uint64_t	last_meal;

	pthread_mutex_lock(&philo->all->time_mtx);
	last_meal = philo->time_last_meal;
	pthread_mutex_unlock(&philo->all->time_mtx);
	if (get_millis_time() - last_meal > philo->time_to_die)
	{
		pthread_mutex_lock(&philo->all->print_mtx);
		philo->all->dead_flag = 1;
		printf("%lu %ld died\n", get_elapsed_time(philo->time_created),
			philo->id);
		pthread_mutex_unlock(&philo->all->print_mtx);
		return (1);
	}
	return (0);
}

int	exit_dead_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->print_mtx);
	if (philo->all->dead_flag)
	{
		pthread_mutex_unlock(&philo->all->print_mtx);
		return (1);
	}
	pthread_mutex_unlock(&philo->all->print_mtx);
	return (0);
}
