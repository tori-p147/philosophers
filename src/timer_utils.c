/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:35:41 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/10/19 16:42:05 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usleep_sec(int sec)
{
	usleep(sec_to_millis(sec) * 1000);
}

size_t	sec_to_millis(int sec)
{
	return (sec * 1000);
}

size_t	micros_to_millis(int usec)
{
	return (usec / 1000);
}

size_t	get_elapsed_time(int start_time)
{
	return (get_millis_time() - start_time);
}

size_t	get_millis_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((sec_to_millis(tv.tv_sec) + micros_to_millis(tv.tv_usec)));
}
