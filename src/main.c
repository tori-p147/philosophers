/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:23 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/09/19 21:54:26 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	*prepare_proccess(int ac, char **av, int *args)
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
	// t_philo		*philos;

	// philos = NULL;
	args = NULL;
	thread_pool = NULL;
	if (ac == 5 || ac == 6)
	{
		args = prepare_proccess(ac, av, args);
		if (!args)
			return (1);
		thread_pool = alloc_thread_pool(thread_pool, *args);
		if (!thread_pool)
			return (free_composite(args, NULL, NULL, 0));
		// philos = alloc_philos(philos, *args);
		// if (!philos)
		// 	return (free_composite(args, thread_pool, NULL, *args));
		printf("args = %p\n", args);
		if (!init_all(&all, thread_pool, args))
			return (1);
		printf("args = %p\n", args);
		// free_composite(args, thread_pool, &all, *args);
		return (0);
	}
	return (1);
}
