/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:10 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/11 22:13:38 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	change_state_and_time_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->state_mtx);
	philo->state = EATING;
	pthread_mutex_unlock(&philo->all->state_mtx);
	philo->time_last_meal = get_millis_time();
	ft_usleep(philo->time_to_eat);
}

void	write_die_time(t_philo *philo)
{
	print_message(philo, "died");
	pthread_mutex_lock(&philo->all->dead_mtx);
	philo->all->dead_flag = 1;
	pthread_mutex_unlock(&philo->all->dead_mtx);
}

void	print_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->all->write_mtx);
	pthread_mutex_lock(&philo->all->dead_mtx);
	if (philo->all->dead_flag)
	{
		pthread_mutex_unlock(&philo->all->dead_mtx);
		pthread_mutex_unlock(&philo->all->write_mtx);
		return ;
	}
	pthread_mutex_unlock(&philo->all->dead_mtx);
	printf("%lu %d %s\n", get_elapsed_time(philo->all->time_created), philo->id,
		str);
	pthread_mutex_unlock(&philo->all->write_mtx);
}
