/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:07:25 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/09 20:08:13 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_sleep(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo->sleep_time);
}

void	do_think(t_philo *philo)
{
	print_message(philo, "is thinking");
	ft_usleep(10);
}

void	write_die_time(t_philo *philo)
{
	philo->die_time = get_millis_time();
	print_message(philo, "died");
	pthread_mutex_lock(&philo->all->dead_mtx);
	philo->all->dead_flag = 1;
	printf("dead_mutex %d\n", philo->all->dead_flag);
	pthread_mutex_unlock(&philo->all->dead_mtx);
}

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
	if (philo->all->philos[left_neighbor_id + 1].is_eating
		&& philo->all->philos[right_neighbor_id - 1].is_eating)
		return (0);
	return (1);
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
	print_message(philo, "has taken a fork 1");
	pthread_mutex_lock(second);
	print_message(philo, "has taken a fork 2");
	print_message(philo, "is eating");
	pthread_mutex_lock(&philo->all->meal_mtx);
	philo->is_eating = true;
	philo->last_meal_time = get_millis_time();
	pthread_mutex_unlock(&philo->all->meal_mtx);
	ft_usleep(philo->eat_time);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
	if (check_meals_goal(philo))
		return (1);
	pthread_mutex_lock(&philo->all->meal_mtx);
	philo->is_eating = false;
	pthread_mutex_unlock(&philo->all->meal_mtx);
	return (0);
}

int check_meals_goal(t_philo *philo)
{
	if (philo->meal_stock != 0)
	{
		philo->meal_eaten++;
		printf("%d philo meal eaten %d\n", philo->id, philo->meal_eaten);
		if (philo->meal_stock == philo->meal_eaten)
		{
			printf("%d philo eat all %d\n", philo->id, philo->meal_eaten);
			philo->all->goal_flag = true;
			return (1);
		}
	}
	return (0);
}
