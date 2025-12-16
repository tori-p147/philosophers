/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:10 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/16 20:02:28 by vmatsuda         ###   ########.fr       */
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

void set_state(t_philo *philo, bool is_eating)
{
	pthread_mutex_lock(&philo->all->state_mtx);
	philo->is_eating = is_eating;
	pthread_mutex_unlock(&philo->all->state_mtx);
}

void	print_die_time(t_philo *philo, uint64_t now)
{
	pthread_mutex_lock(&philo->all->write_mtx);
	printf("%lu %ld died\n", now, philo->id);
	pthread_mutex_unlock(&philo->all->write_mtx);
}

void	print_message(t_philo *philo, uint64_t now, t_ph_action a)
{
	char	*msg;

	msg = "";
	if (exit_dead_flag(philo))
		return ;
	else if (a == FORK)
		msg = "has taken a fork";
	else if (a == EAT)
		msg = "is eating";
	else if (a == SLEEP)
		msg = "is sleeping";
	else if (a == THINK)
		msg = "is thinking";
	pthread_mutex_lock(&philo->all->write_mtx);
	printf("%lu %ld %s\n", now, philo->id, msg);
	pthread_mutex_unlock(&philo->all->write_mtx);
}
