/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:33:04 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/11 21:21:03 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_exit(t_all *all, int *args, int exit_status)
{
	free_all(all, *args);
	free(args);
	return (exit_status);
}

int	free_all(t_all *all, int n)
{
	int	i;

	pthread_mutex_destroy(&all->goal_mtx);
	pthread_mutex_destroy(&all->meal_mtx);
	pthread_mutex_destroy(&all->state_mtx);
	pthread_mutex_destroy(&all->dead_mtx);
	pthread_mutex_destroy(&all->write_mtx);
	free(all->ph_thread_pool);
	if (all->forks)
	{
		i = n;
		while (i-- > 0)
			pthread_mutex_destroy(&all->forks[i]);
		free(all->forks);
	}
	free(all->philos);
	return (1);
}
