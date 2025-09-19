/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:33:04 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/09/19 21:39:35 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_composite(int *args, pthread_t *thread_pool, t_all *all, int n)
{
	(void)n;
	if (thread_pool)
		free(thread_pool);
	if (all->meal_mtx)
		free(all->meal_mtx);
	if (all->dead_mtx)
		free(all->dead_mtx);
	if (all->write_mtx)
		free(all->write_mtx);
	if (all->philos)
	{
		free_philos(all->philos, n);
		free(all->philos);
	}
	if (args)
		free(args);
	return (1);
}

void	free_threads(pthread_t *threads, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		free(threads++);
		i++;
	}
}

void	free_philos(t_philo *philos, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		free(philos->lfork_mtx);
		free(philos->rfork_mtx);
		philos++;
		i++;
	}
}
