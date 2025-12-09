/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:35:41 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/09 17:10:06 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	sec_to_millis(uint64_t sec)
{
	return (sec * 1000);
}

void	ft_usleep(uint64_t milliseconds)
{
	uint64_t	start;

	start = get_millis_time();
	while (1)
	{
		if ((get_millis_time() - start) < milliseconds)
			usleep(1000);
		else
			break ;
	}
}

uint64_t	micros_to_millis(uint64_t usec)
{
	return (usec / 1000);
}

uint64_t	get_elapsed_time(uint64_t start_time)
{
	return (get_millis_time() - start_time);
}

uint64_t	get_millis_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((sec_to_millis(tv.tv_sec) + micros_to_millis(tv.tv_usec)));
}
