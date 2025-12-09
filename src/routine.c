/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:10 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/09 20:32:37 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *str)
{
	if (philo->all->dead_flag)
		return ;
	pthread_mutex_lock(&philo->all->write_mtx);
	printf("%lu %d %s\n", get_elapsed_time(philo->all->start_time), philo->id,
		str);
	pthread_mutex_unlock(&philo->all->write_mtx);
}

void	*do_monitoring(void *arg)
{
	t_all	*all;

	all = (t_all *)arg;
	while (1)
	{
		pthread_mutex_lock(&all->dead_mtx);
		if (all->dead_flag == 1)
		{
			pthread_mutex_unlock(&all->dead_mtx);
			return (NULL);
		}
		pthread_mutex_unlock(&all->dead_mtx);
	}
	return (NULL);
}

int	check_is_die(t_philo *philo)
{
	size_t	now;
	size_t	time_since_last_meal;

	pthread_mutex_lock(&philo->all->meal_mtx);
	now = get_millis_time();
	time_since_last_meal = now - philo->last_meal_time;
	// printf("flag = %d th = %d %zu > %zu\n", philo->all->dead_flag, philo->id,
	// 	time_since_last_meal, philo->die_time);
	pthread_mutex_unlock(&philo->all->meal_mtx);
	if (time_since_last_meal > philo->die_time)
		return (1);
	return (0);
}

void	one_philo_case(t_philo *philo)
{
	print_message(philo, "has taken a fork 1");
	ft_usleep(philo->die_time);
	write_die_time(philo);
}

int check_is_finish(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->goal_mtx);
		if (philo->all->goal_flag == 1)
		{
			pthread_mutex_unlock(&philo->all->goal_mtx);
			return (1);
		}
	pthread_mutex_unlock(&philo->all->goal_mtx);
	return (0);
}

void	*do_action(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->all->philos_count == 1)
	{
		one_philo_case(philo);
		return (NULL);
	}
	while (1 && (philo->all->dead_flag == false
		|| philo->all->goal_flag == false))
	{
		if (check_is_die(philo))
		{
			write_die_time(philo);
			return (NULL);
		}
		if (check_is_finish(philo))
			return (NULL);
		if (check_can_eat(philo))
		{
			if (do_eat(philo))
				return (NULL);
			do_sleep(philo);
		}
		do_think(philo);
	}
	return (NULL);
}
