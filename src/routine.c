/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:10 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/10 21:58:46 by vmatsuda         ###   ########.fr       */
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

int	check_goal(t_all *all)
{
	int			i;
	int			finished_ph_counter;

	i = 0;
	finished_ph_counter = 0;
	while (i < all->philos_count)
	{
		pthread_mutex_lock(&all->state_mtx);
		if (all->philos[i].state == FINISHED)
			finished_ph_counter++;
		pthread_mutex_unlock(&all->state_mtx);
		if (finished_ph_counter == all->philos_count)
		{
			printf("goal!! %d = %d\n", all->philos_count, finished_ph_counter);
			return (1);
		}
		i++;
	}
	return (0);
}

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
		
		if (check_goal(all))
			return (NULL);
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
	bool	df;
	bool	gf;

	df = false;
	gf = false;
	philo = (t_philo *)arg;
	if (philo->all->philos_count == 1)
	{
		one_philo_case(philo);
		return (NULL);
	}
	// printf("start ph = %d \n", philo->id);
	while (1)
	{
		pthread_mutex_lock(&philo->all->dead_mtx);
		if (philo->all->dead_flag)
		{
			pthread_mutex_unlock(&philo->all->dead_mtx);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->all->dead_mtx);
		pthread_mutex_lock(&philo->all->goal_mtx);
		if (philo->all->goal_flag)
		{
			pthread_mutex_unlock(&philo->all->goal_mtx);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->all->goal_mtx);
		if (check_is_die(philo))
		{
			write_die_time(philo);
			return (NULL);
		}
		
		if (check_can_eat(philo) && philo->state != FINISHED)
		{
			pthread_mutex_unlock(&philo->all->state_mtx);
			if (do_eat(philo))
			{
				pthread_mutex_unlock(&philo->all->state_mtx);
				return (NULL);
			}
			else
				do_sleep(philo);
		}
		pthread_mutex_unlock(&philo->all->state_mtx);
		do_think(philo);
	}
	return (NULL);
}
