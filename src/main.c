/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:13:23 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/19 16:45:14 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	run_threads(t_all *all, int n)
{
	int			i;
	uint64_t create_time;

	i = -1;
	create_time = get_millis_time();
	while (++i < n)
	{
		all->philos[i].time_created = create_time;
		all->philos[i].time_last_meal = create_time;
		pthread_create(&all->philos[i].thread, NULL, do_action,
			&all->philos[i]);
	}
	pthread_create(&all->monitor, NULL, do_monitoring, all);
	i = -1;
	while (++i < n)
		pthread_join(all->philos[i].thread, NULL);
	pthread_join(all->monitor, NULL);
	return (1);
}

int	*prepare_proccess(int ac, char **av, int *args)
{
	if (!validate_input_data(ac, av))
		return (NULL);
	args = parse_nums(ac, av, args);
	if (!args)
		return (NULL);
	return (args);
}

int	main(int ac, char **av)
{
	t_all	all;
	int		*args;

	args = NULL;
	if (ac == 5 || ac == 6)
	{
		args = prepare_proccess(ac, av, args);
		if (!args)
			return (1);
		if (!init_all(&all, args))
			return (free_exit(&all, args, 1));
		if (!run_threads(&all, args[0]))
			return (free_exit(&all, args, 1));
		return (free_exit(&all, args, 0));
	}
	return (1);
}
