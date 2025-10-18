/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:33:04 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/10/18 18:04:34 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_all(t_all *all, int n)
{
	int	i;

	pthread_mutex_destroy(&all->meal_mtx);
	pthread_mutex_destroy(&all->dead_mtx);
	pthread_mutex_destroy(&all->write_mtx);
	free(all->thread_pool);
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
