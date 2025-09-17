/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:33:04 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/09/16 22:20:56 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_threads(pthread_t *threads, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		free(threads--);
		i++;
	}
}

void	free_philos(t_philo *philos, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		free(philos--);
		i++;
	}
}
