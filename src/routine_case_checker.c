/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_case_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:07:25 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/12 21:47:24 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_can_eat(t_philo *philo)
{
	int			left_neighbor_id;
	int			right_neighbor_id;
	t_ph_state	lstate;
	t_ph_state	rstate;

	lstate = 0;
	rstate = 0;
	left_neighbor_id = philo->id - 1;
	right_neighbor_id = philo->id + 1;
	if (philo->id == philo->all->philos_count)
		right_neighbor_id = 1;
	else if (philo->id == 1)
		left_neighbor_id = philo->all->philos_count;
	pthread_mutex_lock(&philo->all->state_mtx);
	lstate = philo->all->philos[left_neighbor_id - 1].state;
	rstate = philo->all->philos[right_neighbor_id - 1].state;
	pthread_mutex_unlock(&philo->all->state_mtx);
	if (lstate == EATING && rstate == EATING)
		return (0);
	return (1);
}

int	check_is_finish(t_philo *philo)
{
	if (philo->all->meal_stock > 0
		&& philo->all->meal_stock == philo->meal_eaten)
	{
		pthread_mutex_lock(&philo->all->state_mtx);
		philo->state = FINISHED;
		pthread_mutex_unlock(&philo->all->state_mtx);
		return (1);
	}
	return (0);
}

int	check_goal(t_all *all)
{
	size_t	i;
	size_t	finished_ph_counter;

	i = -1;
	finished_ph_counter = 0;
	while (++i < all->philos_count)
	{
		if (!check_is_finish(&all->philos[i]))
			break ;
		finished_ph_counter++;
		if (finished_ph_counter == all->philos_count)
			return (1);
	}
	return (0);
}

int	check_is_die(t_philo *philo)
{
	uint64_t	now;
	uint64_t	time_since_last_meal;

	pthread_mutex_lock(&philo->all->meal_mtx);
	now = get_millis_time();
	while (now < philo->time_last_meal)
		now = get_millis_time();
	time_since_last_meal = now - philo->time_last_meal;
	pthread_mutex_unlock(&philo->all->meal_mtx);
	if (time_since_last_meal > philo->time_to_die)
		return (1);
	return (0);
}

int	check_dead_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->dead_mtx);
	if (philo->all->dead_flag)
	{
		pthread_mutex_unlock(&philo->all->dead_mtx);
		return (1);
	}
	pthread_mutex_unlock(&philo->all->dead_mtx);
	return (0);
}
