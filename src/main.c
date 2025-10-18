/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:23 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/10/18 18:04:45 by vmatsuda         ###   ########.fr       */
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
	t_all			all;
	int				*args;

	args = NULL;
	if (ac == 5 || ac == 6)
	{
		args = prepare_proccess(ac, av, args);
		if (!args)
			return (1);
		printf("before init all\n");
		if (!init_all(&all, args))
		{
			free_all(&all, *args);
			free(args);
			return (1);
		}
		free_all(&all, *args);
		free(args);
		printf("args = %p\n", args);
		return (0);
	}
	return (1);
}
