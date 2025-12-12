/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:35:41 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/12 21:54:18 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	sec_to_millis(uint64_t sec)
{
	return (sec * 1000);
}

uint64_t	micros_to_millis(uint64_t usec)
{
	return (usec / 1000);
}

uint64_t	get_millis_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(uint64_t milliseconds, t_philo *philo)
{
	uint64_t	start;
	bool		is_dead;

	is_dead = false;
	start = get_millis_time();
	while (get_millis_time() - start < milliseconds)
	{
		pthread_mutex_lock(&philo->all->dead_mtx);
		is_dead = philo->all->dead_flag;
		pthread_mutex_unlock(&philo->all->dead_mtx);
		if (is_dead)
			break ;
		usleep(1000);
	}
}

uint64_t	get_elapsed_time(uint64_t start_time)
{
	return (get_millis_time() - start_time);
}
