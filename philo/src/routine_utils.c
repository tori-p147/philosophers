/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:10 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/27 13:51:44 by vmatsuda         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->all->meal_mtx);
	philo->time_last_meal = get_millis_time();
	pthread_mutex_unlock(&philo->all->meal_mtx);
}

void	print_message(t_philo *philo, t_ph_action a)
{
	char	*msg;
	bool	df;

	msg = "";
	if (a == FORK)
		msg = "has taken a fork";
	else if (a == EAT)
		msg = "is eating";
	else if (a == SLEEP)
		msg = "is sleeping";
	else if (a == THINK)
		msg = "is thinking";
	pthread_mutex_lock(&philo->all->state_mtx);
	df = philo->all->dead_flag;
	pthread_mutex_unlock(&philo->all->state_mtx);
	if (!df)
	{
		pthread_mutex_lock(&philo->all->print_mtx);
		printf("%lu %ld %s\n", get_elapsed_time(philo->time_created), philo->id,
			msg);
		pthread_mutex_unlock(&philo->all->print_mtx);
	}
}
