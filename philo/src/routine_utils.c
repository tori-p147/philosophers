/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:10 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/18 17:13:24 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	increment_eaten_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->meal_mtx);
	philo->meal_eaten++;
	pthread_mutex_unlock(&philo->all->meal_mtx);
	return (0);
}

void	set_time_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->time_mtx);
	philo->time_last_meal = get_millis_time();
	pthread_mutex_unlock(&philo->all->time_mtx);
}

int	check_eaten_meal(t_philo *philo)
{
	if (check_die(philo))
		return (0);
	pthread_mutex_lock(&philo->all->meal_mtx);
	if (philo->all->meal_stock > 0 && philo->meal_eaten >= philo->all->meal_stock)
	{
		pthread_mutex_unlock(&philo->all->meal_mtx);
		return (1);
	}
	pthread_mutex_unlock(&philo->all->meal_mtx);
	return (0);
}

// void	print_die_time(t_philo *philo, uint64_t now)
// {
// 	pthread_mutex_lock(&philo->all->print_mtx);
// 	philo->all->dead_flag = 1;
// 	printf("%lu %ld died\n", now, philo->id);
// 	pthread_mutex_unlock(&philo->all->print_mtx);
// }

void	print_message(t_philo *philo, uint64_t now, t_ph_action a)
{
	char	*msg;

	msg = "";
	if (a == FORK)
		msg = "has taken a fork";
	else if (a == EAT)
		msg = "is eating";
	else if (a == SLEEP)
		msg = "is sleeping";
	else if (a == THINK)
		msg = "is thinking";
	pthread_mutex_lock(&philo->all->print_mtx);
	if (!philo->all->dead_flag)
		printf("%lu %ld %s\n", now, philo->id, msg);
	pthread_mutex_unlock(&philo->all->print_mtx);
}
