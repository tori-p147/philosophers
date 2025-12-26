/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:10 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/26 13:39:27 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_eaten_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->meal_mtx);
	if (philo->all->meal_stock > 0
		&& philo->meal_eaten >= philo->all->meal_stock)
		philo->is_finished = 1;
	pthread_mutex_unlock(&philo->all->meal_mtx);
}

int	check_is_finished(t_philo *philo)
{
	int	finished;

	pthread_mutex_lock(&philo->all->meal_mtx);
	finished = philo->is_finished;
	pthread_mutex_unlock(&philo->all->meal_mtx);
	return (finished);
}

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
	// philo->is_try_eating = 0;
	philo->time_last_meal = get_millis_time();
	pthread_mutex_unlock(&philo->all->meal_mtx);
}

int	check_eaten_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->meal_mtx);
	if (philo->all->meal_stock > 0
		&& philo->meal_eaten >= philo->all->meal_stock)
	{
		philo->is_finished = 1;
		pthread_mutex_lock(&philo->all->print_mtx);
		printf("philo %ld eaten ALL %ld end exit\n", philo->id,
			philo->meal_eaten);
		pthread_mutex_unlock(&philo->all->print_mtx);
		pthread_mutex_unlock(&philo->all->meal_mtx);
		return (1);
	}
	pthread_mutex_unlock(&philo->all->meal_mtx);
	return (0);
}

void	print_message(t_philo *philo, t_ph_action a)
{
	char	*msg;
	bool	df = philo->all->dead_flag;

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
	pthread_mutex_lock(&philo->all->print_mtx);
	if (!df)
		printf("%lu %ld %s\n", get_elapsed_time(philo->time_created), philo->id,
			msg);
	pthread_mutex_unlock(&philo->all->print_mtx);
}
