/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:23 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/09/17 22:36:00 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int *prepare_proccess(int ac, char **av, int *args)
{
	if (!validate_input_data(ac, av))
		return (NULL);
	args = parse_nums(ac, av, args);
	printf("%p\n", args);
	if (!args)
		return (NULL);
	return (args);
}

int	main(int ac, char **av)
{
	t_all		all;
	int			*args;
	pthread_t	*thread_pool;

	args = NULL;
	thread_pool = NULL;
	if (ac == 5 || ac == 6)
	{
		args = prepare_proccess(ac, av, args);
		if (!args)
			return (1);
		thread_pool = alloc_thread_pool(thread_pool, *args);
		if (!thread_pool)
		{
			free(args);
			return (1);
		}
		printf("args = %p\n", args);
		if (!init_all(&all, thread_pool, args))
			return (1);
		// free_philos(all.philos, *args);
		// free(thread_pool);
		// free(args);
		return (0);
	}
	return (1);
}
