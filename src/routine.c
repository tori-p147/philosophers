/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:10 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/10 17:26:48 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *str)
{
	if (philo->all->dead_flag)
		return ;
	pthread_mutex_lock(&philo->all->write_mtx);
	printf("%lu %d %s\n", get_elapsed_time(philo->all->time_created), philo->id,
		str);
	pthread_mutex_unlock(&philo->all->write_mtx);
}

void	*do_monitoring(void *arg)
{
	t_all	*all;
	int		finished_ph_counter;
	int		i;

	finished_ph_counter = 0;
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
		i = 0;
		pthread_mutex_lock(&all->meal_mtx);
		while (i < all->meal_stock)
		{
			if (all->philos[i].state == FINISHED)
			{
				finished_ph_counter++;
				i++;
			}
			pthread_mutex_unlock(&all->meal_mtx);
			if (finished_ph_counter == all->philos_count)
			{
				printf("goal!! %d = %d\n", all->philos_count,
					finished_ph_counter);
				return (NULL);
			}
		}
		pthread_mutex_unlock(&all->meal_mtx);
	}
	return (NULL);
}

int	check_is_die(t_philo *philo)
{
	size_t	now;
	size_t	time_since_last_meal;

	pthread_mutex_lock(&philo->all->meal_mtx);
	now = get_millis_time();
	time_since_last_meal = now - philo->time_last_meal;
	// printf("flag = %d th = %d %zu > %zu\n", philo->all->dead_flag, philo->id,
	// 	time_since_last_meal, philo->time_to_die);
	pthread_mutex_unlock(&philo->all->meal_mtx);
	if (time_since_last_meal > philo->time_to_die)
		return (1);
	return (0);
}

void	one_philo_case(t_philo *philo)
{
	print_message(philo, "has taken a fork 1");
	ft_usleep(philo->time_to_die);
	write_die_time(philo);
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
	while (!philo->all->dead_flag && !philo->all->goal_flag)
	{
		if (check_is_die(philo))
		{
			write_die_time(philo);
			return (NULL);
		}
		if (philo->state != FINISHED)
		{
			if (check_can_eat(philo))
			{
				if (do_eat(philo))
					return (NULL);
				else
					do_sleep(philo);
			}
			do_think(philo);
		}
	}
	return (NULL);
}
