/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:10 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/10/19 17:56:52 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *str)
{
	printf("%lu %d %s\n", get_elapsed_time(philo->start_time), philo->id, str);
}

int	check_can_eat(t_philo *philo)
{
	int	is_llocked;
	int	is_rlocked;

	is_llocked = 0;
	is_rlocked = 0;
	is_llocked = pthread_mutex_lock(philo->lfork_mtx);
	is_rlocked = pthread_mutex_lock(philo->rfork_mtx);
	if (is_llocked || is_llocked)
		return (0);
	return (1);
}

int	check_can_think(t_philo *philo)
{
	int	is_eating;

	is_eating = 0;
	is_eating = pthread_mutex_lock(philo->meal_mtx);
	if (is_eating)
		return (0);
	return (1);
}

void	*do_action(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_can_eat(philo))
		{
			pthread_mutex_lock(philo->meal_mtx);
			print_message(philo, "has taken a fork");
			print_message(philo, "is eating");
			usleep(philo->sleep_time * 1000);
			pthread_mutex_unlock(philo->meal_mtx);
		}
		// printf("job thread is %ld \n", philo->thread);
		// if (philo->dead_mtx)
		// {
		// 	printf("%lu %d is dead\n", philo->die_time, philo->id);
		// 	return (0);
		// }
		if (check_can_think(philo))
			print_message(philo, "is thinking");
		usleep_sec(1);
		if (get_elapsed_time(philo->start_time) > 5000)
		{
			return (0);
		}
	}
	return (0);
}
