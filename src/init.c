/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:29 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/09/17 22:40:47 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mtxs(t_all *all)
{
	all->meal_mtx = malloc(sizeof(pthread_mutex_t));
	all->dead_mtx = malloc(sizeof(pthread_mutex_t));
	all->write_mtx = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(all->meal_mtx, NULL);
	pthread_mutex_init(all->dead_mtx, NULL);
	pthread_mutex_init(all->write_mtx, NULL);
}

void	init_philo(t_philo *philo, pthread_t *threads, int i, int *args)
{
	philo->id = i;
	philo->thread = threads[i];
	philo->philos_count = args[0];
	philo->die_time = args[1];
	philo->eat_time = args[2];
	philo->sleep_time = args[3];
	if (args[4])
		philo->meal_stock = args[4];
	else
		philo->meal_stock = 0;
	philo->think_time = 0;
	philo->start_time = 0;
	philo->lfork_mtx = malloc(sizeof(pthread_mutex_t));
	philo->rfork_mtx = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->lfork_mtx, NULL);
	pthread_mutex_init(philo->rfork_mtx, NULL);
	printf("init philo %d\n", i);
}

int	init_all(t_all *all, pthread_t *threads, int *args)
{
	int		number_of_philos;
	int		i;
	t_philo	*curr;

	number_of_philos = args[0];
	i = 0;
	printf("init all start");
	init_mtxs(all);
	while (i < number_of_philos)
	{
		curr = malloc(sizeof(t_philo));
		if (!curr)
		{
			while (i-- > 0)
				free(all->philos--);
			free(threads);
			free(args);
			return (1);
		}
		all->philos = curr;
		init_philo(curr, threads, i, args);
		curr->dead_mtx = all->dead_mtx;
		curr->meal_mtx = all->meal_mtx;
		curr->write_mtx = all->write_mtx;
		all->philos++;
		i++;
	}
	all->dead_flag = false;
	printf("init all OK");
	print_philos(all, number_of_philos);
	free(args);
	return (0);
}
