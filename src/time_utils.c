/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:35:41 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/16 18:57:49 by vmatsuda         ###   ########.fr       */
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
	start = get_millis_time();
	while (get_millis_time() - start < milliseconds)
	{
		if (exit_dead_flag(philo))
			break ;
		usleep(1000);
	}
}

uint64_t	get_elapsed_time(uint64_t start_time)
{
	uint64_t now = get_millis_time();
	if (now < start_time)
        return (0);
	return (get_millis_time() - start_time);
}
