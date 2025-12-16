/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_case_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:07:25 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/16 18:56:26 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_can_eat(t_philo *philo)
{
	int		left_neighbor_id;
	int		right_neighbor_id;
	bool	lstate;
	bool	rstate;

	lstate = 0;
	rstate = 0;
	left_neighbor_id = philo->id - 1;
	right_neighbor_id = philo->id + 1;
	if (philo->id == philo->all->philos_count)
		right_neighbor_id = 1;
	else if (philo->id == 1)
		left_neighbor_id = philo->all->philos_count;
	pthread_mutex_lock(&philo->all->state_mtx);
	lstate = philo->all->philos[left_neighbor_id - 1].is_eating;
	rstate = philo->all->philos[right_neighbor_id - 1].is_eating;
	pthread_mutex_unlock(&philo->all->state_mtx);
	if (lstate == 1 && rstate == 1)
		return (0);
	return (1);
}

int	check_eaten_meal(t_philo *philo)
{
	size_t	meal_eaten;

	pthread_mutex_lock(&philo->all->meal_mtx);
	meal_eaten = philo->meal_eaten;
	pthread_mutex_unlock(&philo->all->meal_mtx);
	if (philo->all->meal_stock >= meal_eaten)
		return (1);
	return (0);
}

void	set_dead_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->dead_mtx);
	philo->all->dead_flag = 1;
	pthread_mutex_unlock(&philo->all->dead_mtx);
}

int	check_die(t_philo *philo)
{
	uint64_t	now;
	uint64_t	last_meal;
	size_t		eaten;
	bool		is_eating;

	is_eating = false;
	pthread_mutex_lock(&philo->all->state_mtx);
	is_eating = philo->is_eating;
	pthread_mutex_unlock(&philo->all->state_mtx);
	if (is_eating)
		return (0);
	pthread_mutex_lock(&philo->all->meal_mtx);
	eaten = philo->meal_eaten;
	pthread_mutex_unlock(&philo->all->meal_mtx);
	pthread_mutex_lock(&philo->all->time_mtx);
	last_meal = philo->time_last_meal;
	pthread_mutex_unlock(&philo->all->time_mtx);
	if (philo->all->meal_stock > 0 && eaten >= philo->all->meal_stock)
		return (0);
	now = get_millis_time();
	if (now - last_meal > philo->time_to_die)
		return (1);
	return (0);
}

int	exit_dead_flag(t_philo *philo)
{
	bool	is_dead;

	is_dead = false;
	pthread_mutex_lock(&philo->all->dead_mtx);
	is_dead = philo->all->dead_flag;
	pthread_mutex_unlock(&philo->all->dead_mtx);
	if (is_dead)
		return (1);
	return (0);
}
