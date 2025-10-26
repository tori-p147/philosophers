/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:23 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/10/26 17:03:27 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	*prepare_proccess(int ac, char **av, int *args)
{
	if (!validate_input_data(ac, av))
		return (NULL);
	args = parse_nums(ac, av, args);
	if (!args)
		return (NULL);
	return (args);
}

int main_process(t_all *all, int n)
{
	if (!init_thread_pool(all, n))
		return (1);
	return (0);
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
		if (!init_all(&all, args))
		{
			free_all(&all, *args);
			free(args);
			return (1);
		}
		if (!main_process(&all, args[0]))
		{
			free_all(&all, *args);
			free(args);
			return (1);
		}
		free_all(&all, *args);
		free(args);
		return (0);
	}
	return (1);
}
