/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_do.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:25:31 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/11 18:56:21 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*do_monitoring(void *arg)
{
	t_all	*all;

	all = (t_all *)arg;
	while (1)
	{
		pthread_mutex_lock(&all->dead_mtx);
		if (all->dead_flag)
		{
			pthread_mutex_unlock(&all->dead_mtx);
			return (NULL);
		}
		pthread_mutex_unlock(&all->dead_mtx);
		if (all->meal_stock > 0 && check_goal(all))
			return (NULL);
	}
	return (NULL);
}

void	*do_action(void *arg)
{
	t_philo	*philo;
	// bool	not_finished;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_is_die(philo))
		{
			write_die_time(philo);
			return (NULL);
		}
		if (check_can_eat(philo) && !check_is_finish(philo))
		{
			if (do_eat(philo))
				return (NULL);
			else
				do_sleep(philo);
			if (check_is_finish(philo))
				return (NULL);
		}
		do_think(philo);
	}
	return (NULL);
}

int	do_eat(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->id % 2 == 0)
	{
		first = philo->lfork_mtx;
		second = philo->rfork_mtx;
	}
	else
	{
		first = philo->rfork_mtx;
		second = philo->lfork_mtx;
	}
	pthread_mutex_lock(first);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(second);
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
	change_state_and_time_last_meal(philo);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
	if (increment_eaten_meal_and_check_finish(philo))
		return (1);
	return (0);
}

void	do_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->state_mtx);
	philo->state = SLEEPING;
	pthread_mutex_unlock(&philo->all->state_mtx);
	print_message(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	do_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->state_mtx);
	if (philo->state != THINKING)
	{
		philo->state = THINKING;
		print_message(philo, "is thinking");
	}
	pthread_mutex_unlock(&philo->all->state_mtx);
}
