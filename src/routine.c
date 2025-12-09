/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:10 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/09 17:28:23 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *str)
{
	if (philo->all->dead_flag)
		return;
	pthread_mutex_lock(&philo->all->write_mtx);
	printf("%lu %d %s\n", get_elapsed_time(philo->all->start_time), philo->id, str);
	pthread_mutex_unlock(&philo->all->write_mtx);
}

int	try_take_fork(pthread_mutex_t *fork)
{
	int	res;

	res = pthread_mutex_lock(fork);
	return (res);
}

void	do_eat(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->id % 2 == 0)
	{
		first = philo->lfork_mtx;
		second = philo->rfork_mtx;
		pthread_mutex_lock(first);
		print_message(philo, "has taken a fork 1");
		pthread_mutex_lock(second);
		print_message(philo, "has taken a fork 2");
		print_message(philo, "is eating");
	}
	else
	{
		first = philo->rfork_mtx;
		second = philo->lfork_mtx;
		pthread_mutex_lock(first);
		print_message(philo, "has taken a fork 1");
		pthread_mutex_lock(second);
		print_message(philo, "has taken a fork 2");
		print_message(philo, "is eating");
	}
	pthread_mutex_lock(&philo->all->meal_mtx);
	philo->is_eating = true;
	philo->last_meal_time = get_millis_time();
	pthread_mutex_unlock(&philo->all->meal_mtx);
	ft_usleep(philo->eat_time);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
	pthread_mutex_lock(&philo->all->meal_mtx);
	philo->is_eating = false;
	pthread_mutex_unlock(&philo->all->meal_mtx);
	print_message(philo, "is sleeping");
	ft_usleep(philo->sleep_time);
}

void	*do_monitoring(void *arg)
{
	t_all	*all;

	// pthread_t	*ptr;
	// int			i;
	all = (t_all *)arg;
	while (1)
	{
		pthread_mutex_lock(&all->dead_mtx);
		if (all->dead_flag >= 1)
		{
			pthread_mutex_unlock(&all->dead_mtx);
			return (NULL);
		}
		// return (NULL);
		pthread_mutex_unlock(&all->dead_mtx);
	}
	pthread_mutex_unlock(&all->dead_mtx);
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

void	*do_action(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1 && philo->all->dead_flag == false)
	{
		pthread_mutex_lock(&philo->all->dead_mtx);
		if (philo->all->dead_flag == 1)
		{
			pthread_mutex_unlock(&philo->all->dead_mtx);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->all->dead_mtx);
		if (check_is_die(philo))
		{
			write_die_time(philo);
			return (NULL);
		}
		if (check_can_eat(philo))
			do_eat(philo);
		print_message(philo, "is thinking");
		ft_usleep(10);
		// printf("job thread is %ld \n", philo->thread);
		// if (philo->dead_mtx)
		// {
		// 	printf("%lu %d is dead\n", philo->die_time, philo->id);
		// 	return (0);
		// }
		// usleep_sec(1);
	}
	return (NULL);
}
