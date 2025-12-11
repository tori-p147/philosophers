/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_case_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:07:25 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/11 18:55:06 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_can_eat(t_philo *philo)
{
	int	left_neighbor_id;
	int	right_neighbor_id;

	left_neighbor_id = philo->id - 1;
	right_neighbor_id = philo->id + 1;
	if (philo->id == philo->philos_count)
		right_neighbor_id = 1;
	else if (philo->id == 1)
		left_neighbor_id = philo->philos_count;
	pthread_mutex_lock(&philo->all->state_mtx);
	if (philo->all->philos[left_neighbor_id + 1].state == EATING
		&& philo->all->philos[right_neighbor_id - 1].state == EATING)
	{
		pthread_mutex_unlock(&philo->all->state_mtx);
		return (0);
	}
	pthread_mutex_unlock(&philo->all->state_mtx);
	return (1);
}

int	check_is_finish(t_philo *philo)
{
	if (philo->all->meal_stock > 0 && philo->all->meal_stock == philo->meal_eaten)
	{
		printf("%d philo eat all %d\n", philo->id, philo->meal_eaten);
		pthread_mutex_lock(&philo->all->state_mtx);
		philo->state = FINISHED;
		pthread_mutex_unlock(&philo->all->state_mtx);
		return (1);
	}
	return (0);
}

int	check_goal(t_all *all)
{
	int		i;
	int		finished_ph_counter;
	bool	is_finished;

	is_finished = false;
	i = 0;
	finished_ph_counter = 0;
	while (i < all->philos_count)
	{
		pthread_mutex_lock(&all->state_mtx);
		is_finished = all->philos[i].state == FINISHED;
		pthread_mutex_unlock(&all->state_mtx);
		if (is_finished)
			finished_ph_counter++;
		if (finished_ph_counter == all->philos_count)
		{
			printf("goal!! %d = %d\n", all->philos_count, finished_ph_counter);
			return (1);
		}
		i++;
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

int increment_eaten_meal_and_check_finish(t_philo *philo)
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

// int	check_end_flags(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->all->dead_mtx);
// 	if (philo->all->dead_flag)
// 	{
// 		pthread_mutex_unlock(&philo->all->dead_mtx);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&philo->all->dead_mtx);
// 	pthread_mutex_lock(&philo->all->goal_mtx);
// 	if (philo->all->goal_flag)
// 	{
// 		pthread_mutex_unlock(&philo->all->goal_mtx);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&philo->all->goal_mtx);
// 	return (0);
// }
