/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:10 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/12 16:10:07 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	change_state_and_time_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->state_mtx);
	philo->state = EATING;
	pthread_mutex_unlock(&philo->all->state_mtx);
	philo->time_last_meal = get_millis_time();
	ft_usleep(philo->time_to_eat, philo);
}

void	write_die_time(t_philo *philo)
{
	printf("%lu %ld died\n", get_elapsed_time(philo->all->time_created),
		philo->id);
	pthread_mutex_lock(&philo->all->dead_mtx);
	philo->all->dead_flag = 1;
	pthread_mutex_unlock(&philo->all->dead_mtx);
}

void	print_message(t_philo *philo, char *str)
{
	if (check_dead_flag(philo))
		return ;
	pthread_mutex_lock(&philo->all->write_mtx);
	printf("%lu %ld %s\n", get_elapsed_time(philo->all->time_created), philo->id,
		str);
	pthread_mutex_unlock(&philo->all->write_mtx);
}
