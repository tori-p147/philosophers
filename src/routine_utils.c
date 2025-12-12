/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:10 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/12 21:51:32 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	increment_eaten_meal_and_check_finish(t_philo *philo)
{
	if (philo->all->meal_stock != 0)
	{
		philo->meal_eaten++;
		if (philo->all->meal_stock == philo->meal_eaten)
		{
			pthread_mutex_lock(&philo->all->state_mtx);
			philo->state = FINISHED;
			pthread_mutex_unlock(&philo->all->state_mtx);
			return (1);
		}
	}
	return (0);
}

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
	pthread_mutex_lock(&philo->all->dead_mtx);
	if (philo->all->dead_flag)
	{
		pthread_mutex_unlock(&philo->all->dead_mtx);
		return ;
	}
	philo->all->dead_flag = 1;
	pthread_mutex_unlock(&philo->all->dead_mtx);
	pthread_mutex_lock(&philo->all->write_mtx);
	printf("%lu %ld died\n", get_elapsed_time(philo->all->time_created),
		philo->id);
	pthread_mutex_unlock(&philo->all->write_mtx);
}

void	print_message(t_philo *philo, char *str)
{
	if (check_dead_flag(philo))
		return ;
	pthread_mutex_lock(&philo->all->write_mtx);
	printf("%lu %ld %s\n", get_elapsed_time(philo->all->time_created),
		philo->id, str);
	pthread_mutex_unlock(&philo->all->write_mtx);
}
