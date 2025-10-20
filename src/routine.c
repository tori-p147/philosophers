/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:10 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/10/20 23:18:22 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *str)
{
	printf("%lu %d %s\n", get_elapsed_time(philo->start_time), philo->id, str);
}

int	do_eat(t_philo *philo)
{
	int left = philo->id - 1;
    int right = (philo->id) % philo->philos_count;
	
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->all->forks[left]);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(&philo->all->forks[right]);
		print_message(philo, "is eating");
	}
	else
	{
		pthread_mutex_lock(&philo->all->forks[right]);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(&philo->all->forks[left]);
		print_message(philo, "is eating");
	}
	// philo->meal_eaten++;
	// philo->meal_stock--;
	printf("%zu eating\n", philo->eat_time);
	usleep(philo->eat_time * 1000);
	pthread_mutex_lock(philo->meal_mtx);
	printf("%d: locked meal_mtx\n", philo->id);
	philo->last_meal_time = get_elapsed_time(philo->start_time);
	pthread_mutex_unlock(philo->meal_mtx);
	printf("%d: unlocked meal_mtx\n", philo->id);
	return (1);
}

void	*do_monitoring(void *arg)
{
	t_all	*all;
	// pthread_t	*ptr;
	// int			i;

	all = (t_all *)arg;
	int n = all->philos_count + 1; //FIXME obj fields
	// ptr = all->thread_pool;
	// i = 0;
	// while (i < n)
	// {
	// 	printf("thread %d %p\n", i, all->thread_pool);
	// 	all->thread_pool++;
	// 	i++;
	// }
	// all->thread_pool = ptr;
	while (1)
	{
		// printf("dead flag %d\n", all->dead_flag);
		if (all->dead_flag)
		{
			while (n--)
				pthread_detach(all->philos[n].thread);
			return (NULL);
		}
	}
	return (NULL);
}

int	check_is_die(t_philo *philo)
{
	size_t	time_since_last_meal;

	if (philo->last_meal_time != 0)
	{
		time_since_last_meal = get_elapsed_time(philo->last_meal_time);
		// printf("%zu: time_since_last_meal %d: philo id\n",
		// 	philo->last_meal_time, philo->id);
	}
	else
	{
		time_since_last_meal = get_elapsed_time(philo->start_time);
		// printf("%zu: time_since_last_meal not eat %d: philo id\n",
			//philo->start_time, philo->id);
	}
	if (philo->die_time > time_since_last_meal)
		return (0);
	// printf("time now %zu time last %zu \n",
		//get_elapsed_time(philo->start_time),
	// time_since_last_meal);
	return (1);
}

void	*do_action(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->all->dead_flag)
	{
		if (check_is_die(philo))
		{
			pthread_mutex_lock(philo->dead_mtx);
			philo->die_time = get_elapsed_time(philo->start_time);
			print_message(philo, "died");
			philo->all->dead_flag = 1;
			break;
		}
		
		do_eat(philo);
		print_message(philo, "is thinking");
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
